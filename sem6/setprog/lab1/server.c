#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define MAXLINE 1024

int main() {
    int sockfd;
    int port = 0;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    // Создание сокета UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Выбор свободного порта
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(0);  // 0 означает, что порт будет выбран автоматически

    // Привязка сокета
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Ошибка привязки");
        exit(EXIT_FAILURE);
    }

    // Получаем назначенный порт
    getsockname(sockfd, (struct sockaddr *)&servaddr, &len);
    port = ntohs(servaddr.sin_port);
    char *ip_address = inet_ntoa(servaddr.sin_addr);
    printf("Сервер запущен на IP: %s, порту: %d\n", ip_address, port);

    // Открытие лог-файла для записи
    FILE *logFile = fopen("server.log", "w");
    if (logFile == NULL) {
        perror("Ошибка открытия лог-файла");
        exit(EXIT_FAILURE);
    }

    fprintf(logFile, "Сервер запущен на порту %d\n", port);
    fprintf(logFile, "IP адрес сервера: %s\n", ip_address);
    fflush(logFile);  // Принудительный сброс буфера

    while (1) {
        // Получение данных от клиента
        int data = 0;
        ssize_t bytesRead = recvfrom(sockfd, &data, sizeof(data), 0,(struct sockaddr*)&cliaddr, &len);
        if (bytesRead < 0) {
            perror("Ошибка получения данных");            
            continue;
        }

        // Вывод полученных данных и адреса клиента на экран
        printf("Получено от клиента: %d\n", data);
        printf("IP клиента: %s\n", inet_ntoa(cliaddr.sin_addr));
        printf("Порт клиента: %d\n", ntohs(cliaddr.sin_port));

        // Отправка преобразованных данных обратно клиенту 

        int result = data;        //printf("---%d\n", data);
        // Отправляем преобразованные данные обратно клиенту       
        sendto(sockfd, &result, sizeof(result), 0,(struct sockaddr*)&cliaddr, len);
        // Запись в лог-файл
        fprintf(logFile, "Получено от клиента: %d\n", data);
        fprintf(logFile, "IP клиента: %s\n", inet_ntoa(cliaddr.sin_addr));
        fprintf(logFile, "Порт клиента: %d\n", ntohs(cliaddr.sin_port));
        fflush(logFile);
    }

    // Закрытие лог-файла и сокета
    fclose(logFile);
    close(sockfd);

    return 0;
}
