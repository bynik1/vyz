#!/bin/bash

# Создание log файлов, если они не существуют
touch server.log
touch client_output_1.log
touch client_output_2.log

# Компиляция сервера
gcc server.c -o server

# Запуск сервера для получения IP адреса и порта
./server &

# Задержка, чтобы сервер успел запуститься и получить порт
sleep 1

# Получение порта сервера из вывода сервера
port=$(grep "Сервер запущен на порту" server.log | awk '{print $NF}')

# Получение IP адреса сервера
ip=$(grep "IP адрес сервера" server.log | awk '{print $NF}')

# Компиляция клиента
gcc client.c -o client1
gcc client.c -o client2


# Запуск клиента с передачей IP адреса, порта и числа
# echo "Передача аргументов в ./client1: $ip $port 10"

./client1 "$ip" "$port" 1 > client_output_1.log &
./client2 "$ip" "$port" 2 > client_output_2.log &


# Удаление лога сервера

