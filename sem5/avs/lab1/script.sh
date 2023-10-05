#!/bin/bash

# Функция для получения информации о процессоре
get_processor_info() {
    model=$(grep 'model name' /proc/cpuinfo | uniq | awk -F ': ' '{print $2}')
    architecture=$(uname -m)
    max_freq=$(dmidecode -t processor | awk '/Max Speed/ {print $3}')
    cur_freq=$(grep -m 1 MHz /proc/cpuinfo | awk '{print $4}')
    cores=$(grep 'cpu cores' /proc/cpuinfo | uniq | awk -F ': ' '{print $2}')
    threads=$(grep 'siblings' /proc/cpuinfo | uniq | awk -F ': ' '{print $2}')
    load=$(uptime | awk -F 'load average: ' '{print $2}' | awk -F ', ' '{print $1}')

    echo "Процессор:"
    echo "Модель - $model"
    echo "Архитектура - $architecture"
    echo "Тактовая частота максимальная - $max_freq MHz"
    echo "Тактовая частота текущая - $cur_freq MHz"
    echo "Количество ядер - $cores"
    echo "Количество потоков на одно ядро - $threads"
    echo "Загрузка процессора - $load"
    echo
}

# Функция для получения информации об оперативной памяти
get_memory_info() {
    l1_cache=$(lscpu | grep 'L1d cache' | awk -F ': ' '{print $2}')
    l2_cache=$(lscpu | grep 'L2 cache' | awk -F ': ' '{print $2}')
    l3_cache=$(lscpu | grep 'L3 cache' | awk -F ': ' '{print $2}')
    total_mem=$(free -h | awk '/^Память:/ {print $2}')
    available_mem=$(free -h | awk '/^Память:/ {print $7}')

    echo "Оперативная память:"
    echo "Cache L1 - $l1_cache"
    echo "Cache L2 - $l2_cache"
    echo "Cache L3 - $l3_cache"
    echo "Всего - $total_mem"
    echo "Доступно - $available_mem"
    echo
}

# Функция для получения информации о жестком диске
get_disk_info() {
    total_disk=$(df -h --total | awk '/^total/ {print $2}')
    available_disk=$(df -h --total | awk '/^total/ {print $4}')
    partitions=$(df -h --total | awk '{if (NR>1) print $6 " - " $2 " - " $4}')

    echo "Жесткий диск:"
    echo "Всего - $total_disk"
    echo "Доступно - $available_disk"
    echo "Количество разделов - $(( $(df -h --total | wc -l) - 2 ))"
    echo "По каждому разделу общий объём и доступное свободное место:"
    echo "$partitions"
    echo
    echo "Смонтировано в корневую директорию / - $(df -h / | awk '{print $2 " - " $4}')"
    disk_usage=$(df / | grep / | awk '{print $3}')
    disk_nousage=$(df / | grep / | awk '{print $4}')
    remaining_space=$(bc <<< "scale=3; ($disk_nousage - $disk_usage) / 1024 / 1024")
    echo "Объём неразмеченного пространства - $remaining_space"
    echo
}

# Функция для получения информации о сетевых интерфейсах
get_network_info() {
    interfaces=$(ip link show | awk -F ': ' '/^[0-9]+:/ {print $2}')

    echo "Сетевые интерфейсы:"
    echo "Количество сетевых интерфейсов - $(( $(ip link show | grep -c '^[0-9]')))"

    for interface in ${interfaces[@]}; do
        mac=$(ip link show $interface | awk '/ether/ {print $2}')
        ip=$(ip addr show $interface | awk '/inet / {print $2}')
        link=$(ip link show $interface | awk '/link/ {print $2}')
        max_speed=$(iwconfig wlp2s0 | grep "Bit Rate" | awk '{print $2}' | cut -d= -f2
)
        actual_speed=$(speedtest-cli --simple | grep "Download:" | awk '{print $2}'
)

        echo "Имя: $interface"
        echo "MAC: $mac"
        echo "IP: $ip"
        echo "Стандарт связи: $link"
        echo "Максимальная скорость соединения: $max_speed"
        echo "Фактическая скорость соединения: $actual_speed"
        echo
    done
}

# Выводим текущую дату
echo "Дата: $(date)"
echo

# Получаем и выводим информацию о процессоре, оперативной памяти, жестком диске и сетевых интерфейсах
get_processor_info
get_memory_info
get_disk_info
get_network_info