CC = gcc
OBJS = servidor cliente cliente2 
# CLAVES_PATH = claves
BIN_FILES = servidor cliente 
CFLAGS = -lrt -g -I/usr/include/tirpc
LDLIBS = -lnsl -lpthread -ldl -ltirpc
SERVER_OBJS = servidor.o claves_svc.c claves_xdr.c
CLIENTS_OBJS = claves_fun.o claves_xdr.c claves_clnt.c
CLIENTE1 = cliente.o

all: $(OBJS)

libclaves.so: claves_fun.o $(CLIENTS_OBJS)
	$(CC) $(CFLAGS) -fPIC -c -o  $< 
	$(CC) $(LDLIBS) -shared -o $@ claves_fun.o 
	
servidor: $(SERVER_OBJS) 
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@.out $(LDLIBS)

cliente: $(CLIENTE1) libclaves.so
	$(CC) $(CFLAGS) $(CLIENTE1) $(CLIENTS_OBJS) -o $@.out $(LDLIBS)  -L. -lclaves 

clean:
	rm -f $(BIN_FILES) *.o *.so *.out 

re: clean all

.PHONY: all libclaves.so servidor cliente clean re sll cliente2 