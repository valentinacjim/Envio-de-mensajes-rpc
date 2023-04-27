#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <claves.h>


int init(){
	clnt = clnt_create (host, CLAVES, CLAVESVER, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
    return 0;
};

int set_value(int key, char *value1, int value2, double value3){
    int *result_1;
    set_value_1_argument arg;
    arg.key = key;
    arg.value1 = value1;
    arg.value2 = value2;
    arg.value3 = value3;
    result_1 = set_value_1(&arg, clnt);
    if (result_1 == (int *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    return *result_1;
};

int get_value(int key, char *value1, int *value2, double *value3){
    int *result_1;
    get_value_1_argument arg;
    arg.key = key;
    arg.value1 = value1;
    arg.value2 = value2;
    arg.value3 = value3;
    result_1 = get_value_1(&arg, clnt);
    if (result_1 == (int *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    return *result_1;
};

int delete_key(int key){
    int *result_1;
    result_1 = delete_key_1(&key, clnt);
    if (result_1 == (int *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    return *result_1;
};

int modify_value(int key, char *value1, int value2, double value3){
    int *result_1;
    modify_value_1_argument arg;
    arg.key = key;
    arg.value1 = value1;
    arg.value2 = value2;
    arg.value3 = value3;
    result_1 = modify_value_1(&arg, clnt);
    if (result_1 == (int *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    return *result_1;
};

int delete_key(){
    int *result_1;
    result_1 = delete_key_1(&key, clnt);
    if (result_1 == (int *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    return *result_1;
};

int exist(int key){
    int *result_1;
    result_1 = exist_1(&key, clnt);
    if (result_1 == (int *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    return *result_1;
};

int copy_key(int key, int new_key){
    int *result_1;
    copy_key_1_argument arg;
    arg.key = key;
    arg.new_key = new_key;
    result_1 = copy_key_1(&arg, clnt);
    if (result_1 == (int *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    return *result_1;
};
