# Использование базового образа
FROM ubuntu:latest

# Установка компилятора C++, CMake, Ninja, Make и Git
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    ninja-build \
    make \
    git \
    procps \
    net-tools

# Установка рабочей директории
WORKDIR /app

# Копирование исходного кода и файлов CMake в контейнер
COPY . /app

# Запуск CMake с использованием пресетов и сборка проекта
RUN cmake --preset release
RUN cmake --build --preset release

# Запуск приложения
CMD ["./build/release/bin/app", "--file", "file.txt"]
