#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAXLINE 1024

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd;
    int data, i;
    struct sockaddr_in servaddr;

    if (argc != 4) {
        fprintf(stderr, "Использование: %s <IP сервера> <порт сервера> <число>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Создание сокета UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Заполнение информации о сервере
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    if (inet_aton(argv[1], &servaddr.sin_addr) == 0) {
        fprintf(stderr, "Неверный IP адрес\n");
        fprintf(stderr, "errno = %d\n", errno); // Выводим errno
        printf("IP адрес сервера: %s\n", inet_ntoa(servaddr.sin_addr));
        exit(EXIT_FAILURE);
    }

    data = atoi(argv[3]);

    for (i = 0; i < 10; i++) {
        // Отправляем данные на сервер
        sendto(sockfd, &data, sizeof(data), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        sleep(data);
        // Ждем ответа от сервера
        printf("Ожидание ответа от сервера...\n");
        ssize_t bytesRead = recvfrom(sockfd, &data, sizeof(data), 0, NULL, NULL);
        if (bytesRead < 0) {            
            perror("Ошибка получения данных");
        } else {            
            printf("Получено с сервера: %d\n", data);        
        }

        sleep(data); // Задержка в data секунд
    }

    close(sockfd);
    return 0;
}
