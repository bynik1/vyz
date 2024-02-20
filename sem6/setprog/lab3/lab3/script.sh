#!/bin/bash

# Создание log файлов, если они не существуют
touch server.log client_output_1.log client_output_2.log

# Компиляция сервера и клиентов
gcc server.c -o server
gcc client.c -o client1
gcc client.c -o client2

# Даем права на выполнение
chmod +x server client1 client2

# Запуск сервера и клиентов в новых терминалах xterm
xterm -hold -e "./server > server.log" &
sleep 2  # Даем время серверу на запуск

# Извлекаем порт и IP (адаптируйте эти команды под формат вашего лога)
port=$(grep "Listening on port" server.log | awk '{print $NF}')
# IP адрес может потребоваться установить статически, если сервер слушает на localhost или 0.0.0.0
ip=$(grep "IP адрес сервера" server.log | awk '{print $NF}') # Если ваш сервер выводит IP адрес, иначе установите статически


# Запуск клиентских программ
xterm -hold -e "./client1 $ip $port 10 > client_output_1.log" &
xterm -hold -e "./client2 $ip $port 5 > client_output_2.log" &
