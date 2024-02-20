#!/bin/bash

# Создание log файлов, если они не существуют
touch server.log
touch client_output_1.log
touch client_output_2.log

# Компиляция сервера
gcc server.c -o server

# Запуск сервера в новом терминале xterm и запись его вывода в файл для последующего получения порта и IP
xterm -e "bash -c './server > server.log; exec bash'" &

# Задержка, чтобы сервер успел запуститься и получить порт
sleep 2

# Чтение порта и IP адреса из лога сервера
# Замените 'Listening on port' на соответствующую строку вывода вашего сервера, если необходимо
port=$(grep "Listening on port" server.log | awk '{print $NF}')
# IP адрес может потребоваться установить статически, если сервер слушает на localhost или 0.0.0.0
#ip="0.0.0.0"

# Получение IP адреса сервера
ip=$(grep "IP адрес сервера" server.log | awk '{print $NF}')
echo $ip $port
# Компиляция клиентов
gcc client.c -o client1
gcc client.c -o client2

# Запуск клиентов в новых терминалах xterm с передачей IP адреса и порта
xterm -e "bash -c './client1 $ip $port; exec bash'" &
xterm -e "bash -c './client2 $ip $port; exec bash'" &
