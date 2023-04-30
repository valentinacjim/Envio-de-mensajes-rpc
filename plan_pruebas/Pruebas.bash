#!/bin/bash

# Simulación de errores
# No se define la variable de entorno con la dirección del servidor
unset IP_TUPLAS
./servidor &
servidor_pid=$!
./cliente_pruebas &
cliente_pid=$!
wait $!
kill $servidor_pid $cliente_pid



export IP_TUPLAS="holamundo"
# El cliente intenta conectarse a un servidor inexistentes
./servidor &
servidor_pid=$!
./cliente &
cliente_pid=$!
wait $!
kill $cliente_pid $servidor_pid

export IP_TUPLAS="localhost"

# El servidor no responde a la petición del cliente
./servidor_timeout &
servidor_pid=$!
./cliente &
cliente_pid=$!
wait $!
kill $servidor_pid $cliente_pid

# El servidor muere antes de enviar la respuesta al cliente
./servidor_dies &
servidor_pid=$!
./cliente &
cliente_pid=$!
wait $!
kill $servidor_pid $cliente_pid

# Varios clientes se conectan simultáneamente
./cliente &
cliente_pid1=$!
./cliente &
cliente_pid2=$!
./cliente &
cliente_pid3=$!
wait $cliente_pid1 $cliente_pid2 $cliente_pid3

# El cliente muere antes de recibir la respuesta del servidor
./servidor &
servidor_pid=$!
./cliente_dies &
cliente_pid=$!

sleep 5 # Esperar a que se envíe la petición
kill $cliente_pid # Matar el cliente
