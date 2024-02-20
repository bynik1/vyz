#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        return 1;
    }

    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];


    // Создание сокета
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        printf("Could not create socket");
    }
    
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    // Подключение к серверу
    if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
    
    for(int i = 0; i < 10; i++) {
        sprintf(message, "Number: %d\n", i);
        // Отправка сообщения
        if(send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }
        
        // Получение ответа от сервера
        if(recv(sock, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            break;
        }
        
        puts("Server reply:");
        puts(server_reply);
        sleep(i); // Задержка в i секунд
    }
    
    close(sock);
    return 0;
}
