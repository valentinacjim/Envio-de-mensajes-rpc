#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../claves/claves.h"

int main(void){    
    if(init_client() == 0){
        printf("Expected: Iniciado correctamente (cliente.c) \n");}
    else{
        printf("Error al iniciar (cliente.c) \n");}
}