#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Использование: %s <IP> <Порт> <Число>\n", argv[0]);
        return 1;
    }

    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];
    int number = atoi(argv[3]);

    // Создание сокета
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        printf("Не удалось создать сокет\n");
        return 1;
    }
    
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    // Подключение к серверу
    if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Ошибка подключения");
        return 1;
    }

    FILE *log_file = fopen("client.log", "a");
    if(log_file != NULL) {
        fprintf(log_file, "Клиент подключен к серверу с IP: %s, порт: %s\n", argv[1], argv[2]);
    } else {
        perror("Ошибка открытия файла лога клиента");
    }
    
    for(int i = 0; i < number; i++) {
        sprintf(message, "Число: %d\n", i);

        printf("Отправка на сервер: %s", message);
        if(log_file != NULL) {
            fprintf(log_file, "Отправка на сервер: %s", message);
        }

        // Отправка сообщения
        if(send(sock, message, strlen(message), 0) < 0) {
            puts("Ошибка отправки");
            return 1;
        }

        printf("Ожидание ответа от сервера...\n");
        if(log_file != NULL) {
            fprintf(log_file, "Ожидание ответа от сервера...\n");
        }

        // Получение ответа от сервера
        if(recv(sock, server_reply, 2000, 0) < 0) {
            puts("Ошибка получения данных");
            break;
        }

        printf("Получено с сервера: %s", server_reply);
        if(log_file != NULL) {
            fprintf(log_file, "Получено с сервера: %s", server_reply);
        }

        sleep(i); // Задержка
    }
    
    if(log_file != NULL) {
        fclose(log_file);
    }
    
    close(sock);
    return 0;
}
