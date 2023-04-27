//#include "estructuras.h"
#include "claves.h"
#include "lines.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MENSAJES 10
#define MAXSIZE 256
//funciones auxiliares
int connectToServer(){
    char *aux = getenv("PORT_TUPLAS");
    int puerto = atoi(aux); 

    char *aux2 = getenv("IP_TUPLAS");
    
    struct sockaddr_in server_addr;
    struct hostent *hp;
    
    int sc_server;

    sc_server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sc_server, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    if (sc_server < 0){
        perror("Error al crear el socket");
        
    }
    bzero((char *) &server_addr, sizeof(server_addr));
    hp = gethostbyname(aux2);
    if (hp == 0){
        perror("Error al obtener el host");
        
    }
    memcpy(&(server_addr.sin_addr), hp->h_addr_list[0], hp->h_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(puerto);
    //conectamos con el servidor
    if (connect(sc_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        perror("Error al conectar con el servidor");
        
    }

    return sc_server;
    
}
//comprobar un string de 256 caracteres sin incluir el \0
int copy(char *src, char *dst){
    int i = 0;
    while(src[i] != '\0' && i < 255){
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return 0;
}


//funciones de la librería
int init(){
    
    int sc_server = connectToServer();
    if (sc_server == -1){
        return -1;
    }
    
    struct mensaje mess;
    mess.op = 0;
    sendStruct(sc_server, &mess);
    
    struct mensaje res;
    recvStruct(sc_server, &res);
    if (mess.op == -1){
        return -1;
    }
    if (close(sc_server) == -1){
		perror("Error al cerrar el socket");
	}
    return 0;
}

int set_value(int clave, char *val1, int val2, double val3){
    int sc_server = connectToServer();
    if (sc_server == -1){
        return -1;
    }
    
    struct mensaje mess;
    mess.op = 1;
    mess.clave = clave;
    copy(val1, mess.val1);
    mess.val2 = val2;
    mess.val3 = val3;
    sendStruct(sc_server, &mess);

    struct mensaje res;
    recvStruct(sc_server, &res);
    if (close(sc_server) == -1){
		perror("Error al cerrar el socket");
	}
    return res.op;
}

int get_value(int clave, char *val1, int *val2, double *val3){
    int sc_server = connectToServer();
    if (sc_server == -1){
        return -1;
    }
    
    struct mensaje mess;
    mess.op = 2;
    mess.clave = clave;
    sendStruct(sc_server, &mess);

    struct mensaje res;
    recvStruct(sc_server, &res);

    copy(res.val1, val1);
    *val2 = res.val2;
    *val3 = res.val3;
    if (close(sc_server) == -1){
		perror("Error al cerrar el socket");
	}
    return res.op;

}

int modify_value(int clave, char *value1, int value2, double value3){
    int sc_server = connectToServer();
    if (sc_server == -1){
        return -1;
    }
    
    struct mensaje mess;
    mess.op = 3;
    mess.clave = clave;
    copy(value1, mess.val1);
    mess.val2 = value2;
    mess.val3 = value3;
    sendStruct(sc_server, &mess);

    struct mensaje res;
    recvStruct(sc_server, &res);
    if (close(sc_server) == -1){
		perror("Error al cerrar el socket");
	}
    return res.op;
}

int delete_key(int key){
    int sc_server = connectToServer();
    if (sc_server == -1){
        return -1;
    }
    
    struct mensaje mess;
    mess.op = 4;
    mess.clave = key;
    sendStruct(sc_server, &mess);

    struct mensaje res;
    recvStruct(sc_server, &res);
    if (close(sc_server) == -1){
		perror("Error al cerrar el socket");
	}
    return res.op;
}

int exist(int key){
    int sc_server = connectToServer();
    if (sc_server == -1){
        return -1;
    }
    
    struct mensaje mess;
    mess.op = 5;
    mess.clave = key;
    sendStruct(sc_server, &mess);

    struct mensaje res;
    recvStruct(sc_server, &res);
    if (close(sc_server) == -1){
		perror("Error al cerrar el socket");
	}
    return res.op;
}

int copy_key(int key1, int key2){
    int sc_server = connectToServer();
    if (sc_server == -1){
        return -1;
    }
    
    struct mensaje mess;
    mess.op = 6;
    mess.clave = key1;
    mess.clave2 = key2;
    sendStruct(sc_server, &mess);

    struct mensaje res;
    recvStruct(sc_server, &res);
    if (close(sc_server) == -1){
		perror("Error al cerrar el socket");
	}
    return res.op;
}