#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../claves.h"
#include "claves.h"



int init_client(){
    CLIENT *clnt;
	enum clnt_stat retval;
	int result;
    char *host = getenv("IP_TUPLAS");
	clnt = clnt_create (host, CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
    retval = server_init_1(&result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    
    return result;
};

int set_value_client(int key, char *value1, int value2, double value3){
    CLIENT *clnt;
	enum clnt_stat retval;
	int result;
    char *host = getenv("IP_TUPLAS");
	clnt = clnt_create (host, CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
    retval = server_set_value_1(key, value1, value2, value3, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

    return result;
};

int get_value_client(int key, char *value1, int *value2, double *value3){
    CLIENT *clnt;
	enum clnt_stat retval;
	respuesta result;
    char *host = getenv("IP_TUPLAS");
	clnt = clnt_create (host, CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }

    result.value1 = malloc(256);
    
    retval = server_get_value_1(key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    if (result.result == 0){
        strcpy(value1, result.value1);
        *value2 = result.value2;
        *value3 = result.value3;
    }
    
    return result.result;
};

int modify_value_client(int key, char *value1, int value2, double value3){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
    char *host = getenv("IP_TUPLAS");
	clnt = clnt_create (host, CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
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
    char *host = getenv("IP_TUPLAS");
	clnt = clnt_create (host, CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
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
    char *host = getenv("IP_TUPLAS");
	clnt = clnt_create (host, CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
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
    char *host = getenv("IP_TUPLAS");
	clnt = clnt_create (host, CLAVES, OPERACIONESVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
    
    retval = server_copy_key_1(key, new_key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};
