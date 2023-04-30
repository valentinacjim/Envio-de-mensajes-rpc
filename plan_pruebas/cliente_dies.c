#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../claves/claves.h"

int main(void){
    int res;
    res = init_client();
    printf("init_client: %d\n", res);
}