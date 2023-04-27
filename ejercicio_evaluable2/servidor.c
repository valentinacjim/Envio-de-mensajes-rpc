//#include "estructuras.h"
#include "sll.h"
#include "lines.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> //for close
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#define NUM_MENSAJES 10


pthread_mutex_t mutex_mensaje;
int mensaje_no_copiado = true;
pthread_cond_t cond_mensaje;
pthread_mutex_t mutex_lista;
int acceso_lista = false;
pthread_cond_t cond_lista;

struct List *lista;
int lista_creada = 0;

int tratar_mensaje(int *socket){

    int sc_client; //información del resultado de la operación

    pthread_mutex_lock(&mutex_mensaje);

	sc_client = *socket;
	
	/* ya se puede despertar al servidor*/
	mensaje_no_copiado = false;
	pthread_cond_signal(&cond_mensaje);
	pthread_mutex_unlock(&mutex_mensaje);

	struct mensaje peticion;
	struct mensaje respuesta;

	if (recvStruct(sc_client, &peticion) < 0){
		//intentamos comunicar el error al cliente
		respuesta.op = -1;
		sendStruct(sc_client, &respuesta);
		close(sc_client);
		perror("Error al recibir el mensaje");
	}

	pthread_mutex_init(&mutex_lista, NULL);
	pthread_cond_init(&cond_lista, NULL);

	//espera al mutex de la lista
	pthread_mutex_lock(&mutex_lista);
	while (acceso_lista)
		pthread_cond_wait(&cond_lista, &mutex_lista);
	acceso_lista = true;
	
	//accede a la lista
	struct elemento new;
	switch (peticion.op)
	{
	case 0:
		//init
		if (lista_creada){
			freeList(lista);
		}
		lista = newList();
		lista_creada = 1;
		respuesta.op = 0;
		break;

	case 1:
		//set_value
		if (lista_creada == 0){
			respuesta.op = -1;
			break;
		}
		new.clave = peticion.clave;
		strncpy(new.val1, peticion.val1, 256);
		new.val2 = peticion.val2;
		new.val3 = peticion.val3;
		if(search(lista, new.clave) == NULL){
			add(lista, new);
			respuesta.op = 0;
		}
		else{
			respuesta.op = -1;
		}
		break;

	case 2:
		//get_value
		if (lista_creada == 0){
			respuesta.op = -1;
			break;
		}
		if (search(lista, peticion.clave) != NULL){
			struct Node *e = search(lista, peticion.clave);
			respuesta.op = 0;
			respuesta.clave = e->data.clave;
			strncpy(respuesta.val1, e->data.val1, 256);
			respuesta.val2 = e->data.val2;
			respuesta.val3 = e->data.val3;
		}
		else{
			respuesta.op = -1;
		}
		break;

	case 3:
		//modify_value
		if (lista_creada == 0){
			respuesta.op = -1;
			break;
		}
		if (search(lista, peticion.clave) == NULL){
			respuesta.op = -1;
			break;
		}
		struct Node *e = search(lista, peticion.clave);
		strncpy(e->data.val1, peticion.val1, 256);
		e->data.val2 = peticion.val2;
		e->data.val3 = peticion.val3;

		respuesta.op = 0;
		break;

	case 4:
		//delete_key
		if (lista_creada == 0){
			respuesta.op = -1;
			break;
		}
		if (search(lista, peticion.clave) == NULL){
			respuesta.op = -1;
			break;
		}
		removeNode(lista, peticion.clave);
		respuesta.op = 0;
		break;

	case 5:
		//exist
		if (lista_creada == 0){
			respuesta.op = -1;
			break;
		}
		if (search(lista, peticion.clave) == NULL){
			respuesta.op = 0;
			break;	
		}
		respuesta.op = 1;
		
		break;

	case 6:
		//copy
		if (lista_creada == 0){		
			respuesta.op = -1;
			break;
		}
		struct Node *e1 = search(lista, peticion.clave);
		if (e1 == NULL){
			respuesta.op = -1;
			break;
		}
		
		struct Node *e2 = search(lista, peticion.clave2);

		if (e2 != NULL){
			strncpy(e2->data.val1, e1->data.val1, 256);
			e2->data.val2 = e1->data.val2;
			e2->data.val3 = e1->data.val3;
			respuesta.op = 0;
			break;
		}
		
		new.clave = peticion.clave2;
		strncpy(new.val1, e1->data.val1, 256);
		new.val2 = e1->data.val2;
		new.val3 = e1->data.val3;
		add(lista, new);
		respuesta.op = 0;
		break;
	
	default:
		respuesta.op = -1;
		break;
	}
	
	//envia la respuesta
	if (sendStruct(sc_client, &respuesta) < 0){
		close(sc_client);
		perror("Error al enviar la respuesta");
	}

	acceso_lista = false;
	pthread_cond_signal(&cond_lista);
	pthread_mutex_unlock(&mutex_lista);
	
	if (close(sc_client) == -1){
		perror("Error al cerrar el socket");
	}
	return 0;
}

int main(int argc, char *argv[]){
	//check if the number of arguments is correct
	if (argc != 2){
		perror("Error: el número de argumentos es incorrecto \n");
	}
	//get the first argument and check if it is a number
	int port = atoi(argv[1]);
	if (port == 0){
		perror("Error: el primer argumento debe ser un número \n");
	}

    struct mensaje mess;
	struct sockaddr_in server_addr, client_addr;
	int sc_server, sc_client;
	socklen_t size;

	if ((sc_server = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Error al crear el socket del servidor");
	}
	setsockopt(sc_server, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
	// preparación del struct address
	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port); 
	server_addr.sin_addr.s_addr = INADDR_ANY; //luego la pasaremos por variable de entorno

	/*bind socket del servidor*/
	if(bind(sc_server,(struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		close(sc_server);
		perror("Error al bindear el socket del servidor");
	}

	listen(sc_server, SOMAXCONN);

	pthread_attr_t t_attr;		// atributos de los threads 
   	pthread_t thid;

	pthread_mutex_init(&mutex_mensaje, NULL);
	pthread_cond_init(&cond_mensaje, NULL);
	pthread_attr_init(&t_attr);
	// atributos de los threads, threads independientes
	pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);

	for(;;) {
		sc_client = accept(sc_server,(struct sockaddr *)&client_addr, &size);
		if (sc_client < 0){
			close(sc_client);
			perror("Error al aceptar el socket del cliente");
			break;
		}
		if (pthread_create(&thid, &t_attr, (void *)tratar_mensaje, (void *)&sc_client)== 0) {
				// se espera a que el thread copie el mensaje 
				pthread_mutex_lock(&mutex_mensaje);
				while (mensaje_no_copiado)
					pthread_cond_wait(&cond_mensaje, &mutex_mensaje);
				mensaje_no_copiado = true;
				pthread_mutex_unlock(&mutex_mensaje);
	 	}
	} 		
	if (close(sc_server) == -1){
		perror("Error al cerrar el socket del servidor");
	}
	return 0;
}
	