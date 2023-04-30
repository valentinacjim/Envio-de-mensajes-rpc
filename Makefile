CC = gcc
OBJS = servidor cliente cliente_pruebas cliente_dies servidor_timeout servidor_dies
CLAVES_PATH = claves/
PRUEBAS_PATH = plan_pruebas/
BIN_FILES = servidor cliente 
CFLAGS = -lrt -g -I/usr/include/tirpc
LDLIBS = -lnsl -lpthread -ldl -ltirpc
SERVER_OBJS = servidor.o claves_svc.c claves_xdr.c sll.o 
CLIENTS_OBJS = $(CLAVES_PATH)claves.o claves_xdr.c claves_clnt.c
CLIENTE1 = cliente.o

all: $(OBJS)

libclaves.so: $(CLAVES_PATH)claves.o $(CLIENTS_OBJS)
	$(CC) $(CFLAGS) -fPIC -c -o  $< 
	$(CC) $(LDLIBS) -shared -o $@ $(CLAVES_PATH)claves.o
	
servidor: $(SERVER_OBJS) 
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@ $(LDLIBS)

cliente: $(CLIENTE1) libclaves.so
	$(CC) $(CFLAGS) $(CLIENTE1) $(CLIENTS_OBJS) -o $@ $(LDLIBS)  -L. -lclaves 

# Archivos de prueba
cliente_pruebas: $(PRUEBAS_PATH)cliente_pruebas.o libclaves.so
	$(CC) $(CFLAGS) $(PRUEBAS_PATH)cliente_pruebas.o $(CLIENTS_OBJS) -o $(PRUEBAS_PATH)$@ $(LDLIBS)  -L. -lclaves

cliente_dies: $(PRUEBAS_PATH)cliente_dies.o libclaves.so
	$(CC) $(CFLAGS) $(PRUEBAS_PATH)cliente_dies.o $(CLIENTS_OBJS) -o $(PRUEBAS_PATH)$@ $(LDLIBS)  -L. -lclaves

servidor_timeout: $(PRUEBAS_PATH)servidor_timeout.o claves_svc.c claves_xdr.c sll.o
	$(CC) $(CFLAGS) $(PRUEBAS_PATH)servidor_timeout.o claves_svc.c claves_xdr.c sll.o -o $(PRUEBAS_PATH)$@ $(LDLIBS)

servidor_dies: $(PRUEBAS_PATH)servidor_dies.o claves_svc.c claves_xdr.c sll.o
	$(CC) $(CFLAGS) $(PRUEBAS_PATH)servidor_dies.o claves_svc.c claves_xdr.c sll.o -o $(PRUEBAS_PATH)$@ $(LDLIBS)


clean:
	rm -f $(BIN_FILES) *.o *.so *.out 

re: clean all

.PHONY: all libclaves.so servidor cliente clean re sll cliente2 claves