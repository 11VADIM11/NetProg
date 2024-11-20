#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <IP_СЕРВЕРА> <ПОРТ_СЕРВЕРА>" << std::endl;
        return 1;
    }

    const char* server_ip = argv[1];
    int port = std::stoi(argv[2]);

    // Создание UDP сокета
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        std::cerr << "Неверный адрес" << std::endl;
        close(sockfd);
        return 1;
    }

    // Отправка сообщения на сервер
    const char* request = "ЗАПРОС"; 
    if(sendto(sockfd, request, strlen(request), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка отправки" << std::endl;
        close(sockfd);
        return 1;
    }

    // Получение ответа от сервера
    char buffer[1024] = { 0 }; 
    socklen_t server_len = sizeof(server_addr);
    int bytes_received = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server_addr, &server_len);
    if(bytes_received < 0) {
        std::cerr << "Ошибка получения сообщения от сервера" << std::endl;
        close(sockfd);
        return 1;
    }

    buffer[bytes_received] = '\0'; 
    std::cout << "Ответ от сервера: " << buffer << std::endl;

    // Закрытие сокета
    close(sockfd);
    return 0;
}
