#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "claves_fun.h"
#include "claves.h"

// #include <rpc/rpc.h>


int init_client(){
    CLIENT *clnt;
	enum clnt_stat retval;
	int result;
	clnt = clnt_create ("localhost", CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
    retval = server_init_1(&result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    if (result == 0){
        printf("Lista inicializada \n");
    }
    else{
        printf("No se pudo inicializar la lista \n");
    }
    return 0;
};

int set_value_client(int key, char *value1, int value2, double value3){
    CLIENT *clnt;
	enum clnt_stat retval;
	int result;
    clnt = clnt_create ("localhost", CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
    retval = server_set_value_1(key, value1, value2, value3, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

    if (result == 0){
        printf("Valor agregado \n");
    }
    else{
        printf("No se pudo agregar el valor \n");
    }
    return result;
};

respuesta get_value_client(int key){
    CLIENT *clnt;
	enum clnt_stat retval;
	respuesta result;
    clnt = clnt_create ("localhost", CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
    result.value1 = malloc(256);

    
    retval = server_get_value_1(key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    if (result.result == 0){
        printf("Valor obtenido \n");
        printf("Valor 1: %s \n", result.value1);
        printf("Valor 2: %d \n", result.value2);
        printf("Valor 3: %f \n", result.value3);
    }
    else{
        printf("No se pudo obtener el valor \n");
    }
    return result;
};

int modify_value_client(int key, char *value1, int value2, double value3){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
    clnt = clnt_create ("localhost", CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
   
    retval = server_modify_value_1(key, value1, value2, value3, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};

int delete_key_client(int key){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
    clnt = clnt_create ("localhost", CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
    retval = server_delete_key_1(key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};

int exist_client(int key){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
    clnt = clnt_create ("localhost", CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
    retval = server_exist_1(key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};

int copy_key_client(int key, int new_key){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
    clnt = clnt_create ("localhost", CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
    
    retval = server_copy_key_1(key, new_key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};
