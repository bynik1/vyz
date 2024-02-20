#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 5
pthread_mutex_t lock;

void *client_handler(void *socket_desc) {
    int sock = *(int*)socket_desc;
    int read_size;
    char client_message[2000];
    
    // Чтение данных от клиента
    while((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        // Блокировка мьютекса для обеспечения целостности файла
        pthread_mutex_lock(&lock);
        
        // Запись данных в файл
        FILE *fp = fopen("data.txt", "a");
        if(fp != NULL) {
            fputs(client_message, fp);
            fclose(fp);
        } else {
            perror("Error opening file");
        }
        
        // Разблокировка мьютекса
        pthread_mutex_unlock(&lock);
        
        // Отправка эхо-ответа клиенту
        send(sock, client_message, strlen(client_message), 0);
    }
    
    if(read_size == 0) {
        puts("Client disconnected");
    } else if(read_size == -1) {
        perror("recv failed");
    }
    
    free(socket_desc);
    return 0;
}

int main(int argc, char *argv[]) {
    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;
    
    // Создание сокета
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_desc == -1) {
        perror("Could not create socket");
        return 1;
    }
    
    // Подготовка структуры sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(0); // 0 для автоматического выбора свободного порта
    
    // Привязка
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        return 1;
    }
    
    // Получение и вывод номера порта
    socklen_t len = sizeof(server);
    if(getsockname(socket_desc, (struct sockaddr *)&server, &len) == -1) {
        perror("getsockname failed");
        return 1;
    }
    printf("Listening on port: %d\n", ntohs(server.sin_port));
    
    // Прослушивание
    listen(socket_desc, MAX_CLIENTS);
    
    // Принятие и обработка соединений
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    pthread_mutex_init(&lock, NULL);
    
    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
        
        if(pthread_create(&sniffer_thread, NULL, client_handler, (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
        
        puts("Handler assigned");
    }
    
    if(client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    
    return 0;
}
