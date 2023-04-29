#ifndef _CLAVES_FUN_H
#define _CLAVES_FUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int init_client();
int set_value_client(int key, char *value1, int value2, double value3);
int get_value_client(int key, char *value1, int *value2, double *value3);
int modify_value_client(int key, char *value1, int value2, double value3);
int delete_key_client(int key);
int exist_client(int key);
int copy_key_client(int key1, int key2);

#endif