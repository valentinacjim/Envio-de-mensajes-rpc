#include "claves_fun.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(void){
    // char string[256];
    // strncpy(string, "hola", 256);
    // if(set_value(1, string, 2, 3.0) == 0){
    //     printf("Clave guardada correctamente (cliente.c) \n");}
    // else{
    //     printf("Expected: Error al guardar la clave (cliente.c) \n");}
    
    if(init() == 0){
        printf("Expected: Iniciado correctamente (cliente.c) \n");}
    else{
        printf("Error al iniciar (cliente.c) \n");}

//     if(set_value(1, string, 2, 3.0) == 0){
//         printf("Expected: Clave guardada correctamente (cliente.c) \n");}
//     else{
//         printf("Error al guardar la clave (cliente.c) \n");}

//     if(set_value(1, string, 2, 3.0) == 0){
//         printf("Clave guardada correctamente (cliente.c) \n");}
//     else{
//         printf("Expected: Error al guardar la clave (cliente.c) \n");}

//     char val1[256];
//     int a;
//     int *val2 = &a;
//     double b;
//     double *val3 = &b;

//     if(get_value(1, val1, val2, val3) == 0){
//         printf("Expected: Clave obtenida correctamente (cliente.c) \n");
//         printf("Clave: %d, Val1: %s, Val2: %d, Val3: %f \n", 1, val1, *val2, *val3);}

//     else{
//         printf("Error al obtener la clave (cliente.c) \n");}

//     if(modify_value(1, string, 4, 5.5) == 0){
//         printf("Expected: Clave modificada correctamente (cliente.c) \n");}
//       else{
//         printf(" Error al modificar la clave (cliente.c) \n");}   
//      if(modify_value(4, string, 4, 5.5) == 0){
//         printf("Clave modificada correctamente (cliente.c) \n");}
//     else{
//         printf("Expected: Error al modificar la clave (cliente.c) \n");}

//     if(delete_key(1) == 0){
//         printf("Expected: Clave eliminada correctamente (cliente.c) \n");}
//     else{
//         printf("Error al eliminar la clave (cliente.c) \n");}
        
//     if(delete_key(4) == 0){
//         printf("Clave eliminada correctamente (cliente.c) \n");}
//     else{
//         printf("Expected: Error al eliminar la clave (cliente.c) \n");}
    
//     if(set_value(1, string, 2, 3.0) == 0){
//         printf("Expected: Clave guardada correctamente (cliente.c) \n");}
//     else{
//         printf("Error al guardar la clave (cliente.c) \n");}

//     if(exist(1) == 0){
//         printf("Clave no existe (cliente.c) \n");}
//     else if (exist(1) == 1){
//         printf("Expected: Clave existe \n");}
//     else{
//         printf("Error al comprobar si existe la clave (cliente.c) \n");}
    
//     if(exist(4) == 0){
//         printf("Expected: Clave no existe (cliente.c) \n");}
//     else if (exist(4) == 1){
//         printf("Clave existe \n");}
//     else{
//         printf("Error al comprobar si existe la clave (cliente.c) \n");}

//     if(copy_key(1, 4) == 0){
//         printf("Expected: Clave copiada correctamente (cliente.c) \n");}
//     else{
//         printf("Error al copiar la clave (cliente.c) \n");}
    
//     if(copy_key(5, 2) == 0){
//         printf("Clave copiada correctamente (cliente.c) \n");}
//     else{
//         printf("Expected: Error al copiar la clave (cliente.c) \n");}
    
    
}
