#!/bin/bash

# Переменная с URL вашего репозитория на GitHub
REPO_URL="https://github.com/bynik1/vyz"

# Проверка, что git установлен
if ! command -v git &> /dev/null; then
    echo "Git не установлен. Пожалуйста, установите Git."
    exit 1
fi

# Проверка наличия SSH ключа
if [ ! -f ~/.ssh/id_rsa ]; then
    echo "SSH ключ не найден. Генерация нового SSH ключа..."
    ssh-keygen -t rsa -b 4096 -C "alesha.bessonov2003@mail.ru" -f ~/.ssh/github -N ""
fi
# Вывод открытого SSH ключа
echo "Открытый SSH ключ:"
cat ~/.ssh/github.pub

# Настройка Git для использования SSH ключа
git config --global user.email "alesha.bessonov2003@mail.ru"
git config --global user.name "bynik"
git config --global credential.helper store

# Клонирование репозитория, если его нет на вашем компьютере
if [ ! -d "repository" ]; then
    git clone $REPO_URL
fi

# Переход в папку с репозиторием
cd vyz

exit 0
