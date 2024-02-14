#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    if (argc < 3) {
        fprintf(stderr,"Использование: %s hostname port\n", argv[0]);
        exit(0);
    }
    
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0)
        error("Ошибка открытия сокета");
    
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Ошибка, нет такого хоста\n");
        exit(0);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("Ошибка подключения");
    
    int i;
    for (i = 1; i <= 10; i++) { // Отправка числа i серверу 10 раз с задержкой в i секунд
        char buffer[256];
        sprintf(buffer, "%d", i);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
            error("Ошибка при записи в сокет");
        printf("Отправлено на сервер: %s\n", buffer);
        sleep(i);
    }
    
    close(sockfd);
    return 0;
}
