#ifndef CLAVES_H
#define CLAVES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <../claves.h>


int init();
int set_value(int key, char *value1, int value2, double value3);
respuesta get_value(int key);
int modify_value(int key, char *value1, int value2, double value3);
int delete_key(int key);
int exist(int key);
int copy_key(int key1, int key2);

#endif