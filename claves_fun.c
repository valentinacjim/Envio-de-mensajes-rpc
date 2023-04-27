#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "claves_fun.h"
#include "claves.h"
#
// #include <rpc/rpc.h>


int init(){
    CLIENT *clnt;
	enum clnt_stat retval;
	int result;
	clnt = clnt_create ("127.0.0.1", CLAVES, OPERACIONESVER, "tdp");
    if (clnt == NULL) {
        clnt_pcreateerror ("127.0.0.1");
        exit (1);
    }
    retval = server_init_1(&result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return 0;
};

int set_value(int key, char *value1, int value2, double value3){
    CLIENT *clnt;
	enum clnt_stat retval;
	int result;
    
    retval = server_set_value_1(key, value1, value2, value3, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};

respuesta get_value(int key){
    CLIENT *clnt;
	enum clnt_stat retval;
	respuesta result;

    
    retval = server_get_value_1(key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};

int modify_value(int key, char *value1, int value2, double value3){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
   
    retval = server_modify_value_1(key, value1, value2, value3, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};

int delete_key(int key){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
    retval = server_delete_key_1(key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};

int exist(int key){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
    retval = server_exist_1(key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};

int copy_key(int key, int new_key){
    CLIENT *clnt;
	enum clnt_stat retval;
    int result;
    
    retval = server_copy_key_1(key, new_key, &result, clnt);
    if (retval != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }
    return result;
};
