
#ifndef _CLAVES
#define _CLAVES

int init();
int set_value(int clave, char val1[256], int val2, double val3);
int get_value(int clave, char val1[256], int *val2, double *val3);
int modify_value(int clave, char *value1, int value2, double value3);
int delete_key(int key);
int exist(int key);
int copy_key(int key1, int key2);



#endif