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
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Получаем информацию о клиенте
    getpeername(sock, (struct sockaddr *)&client_addr, &client_addr_len);

    // Чтение данных от клиента
    while((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        client_message[read_size] = '\0'; // Обеспечиваем корректное завершение строки

        // Блокировка мьютекса для обеспечения целостности файла
        pthread_mutex_lock(&lock);
        
        // Запись данных в файл и вывод в консоль
        FILE *fp = fopen("data.txt", "a");
        if(fp != NULL) {
            fprintf(fp, "IP клиента: %s\nПорт клиента: %d\nПолучено от клиента: %s\n", 
                    inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), client_message);
            fclose(fp);
            
            // Также выводим данные в консоль сервера
            printf("IP клиента: %s\nПорт клиента: %d\nПолучено от клиента: %s\n", 
                   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), client_message);
        } else {
            perror("Ошибка открытия файла");
        }
        
        // Разблокировка мьютекса
        pthread_mutex_unlock(&lock);
        
        // Отправка эхо-ответа клиенту
        send(sock, client_message, strlen(client_message), 0);
    }
    
    if(read_size == 0) {
        puts("Клиент отключился");
    } else if(read_size == -1) {
        perror("Ошибка при получении данных");
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
        perror("Не удалось создать сокет");
        return 1;
    }
    
    // Подготовка структуры sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // Привязка ко всем интерфейсам
    server.sin_port = htons(0); // 0 для автоматического выбора свободного порта
    
    // Привязка
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Ошибка привязки");
        return 1;
    }
    
    // Получение и вывод номера порта
    socklen_t len = sizeof(server);
    if(getsockname(socket_desc, (struct sockaddr *)&server, &len) == -1) {
        perror("Ошибка getsockname");
        return 1;
    }
    
    // Вывод IP-адреса и порта сервера
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;
    
    char *ip_address = inet_ntoa(server.sin_addr);
    printf("Сервер запущен на IP: %s, порту: %d\n", ip_address, ntohs(server.sin_port));
    
    // Прослушивание
    listen(socket_desc, MAX_CLIENTS);
    
    // Принятие входящих соединений
    puts("Ожидание входящих соединений...");
    c = sizeof(struct sockaddr_in);
    pthread_mutex_init(&lock, NULL);
    
    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
        
        if(pthread_create(&sniffer_thread, NULL, client_handler, (void*) new_sock) < 0) {
            perror("Не удалось создать поток");
            return 1;
        }
        
        puts("Обработчик назначен");
    }
    
    if(client_sock < 0) {
        perror("Ошибка при принятии соединения");
        return 1;
    }
    
    return 0;
}
