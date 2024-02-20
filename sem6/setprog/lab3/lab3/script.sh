#!/bin/bash

# Создание log файлов, если они не существуют
touch server.log
touch client_output_1.log
touch client_output_2.log

# Компиляция сервера и клиентов
gcc server.c -o server
gcc client.c -o client1
gcc client.c -o client2

# Даем права на выполнение
chmod +x server client1 client2

# Запуск сервера в новом терминале GNOME Terminal и запись его вывода в файл server.log для последующего получения порта и IP
gnome-terminal -- bash -c "./server > server.log 2>&1; exec bash"

# Задержка, чтобы сервер успел запуститься и получить порт
sleep 2

# Получение порта сервера из вывода сервера
port=$(grep "Сервер запущен на порту" server.log | awk '{print $NF}')

# Получение IP адреса сервера
ip=$(grep "IP адрес сервера" server.log | awk '{print $NF}')

echo "IP: $ip, Port: $port"

# Запуск клиентов в новых терминалах GNOME Terminal с передачей IP адреса и порта и перенаправлением их вывода в соответствующие log файлы
gnome-terminal -- bash -c "./client1 $ip $port 10 > client_output_1.log 2>&1; exec bash"
gnome-terminal -- bash -c "./client2 $ip $port 10 > client_output_2.log 2>&1; exec bash"
