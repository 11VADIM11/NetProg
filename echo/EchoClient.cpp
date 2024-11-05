
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

    // Создание сокета
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    // Подключение к серверу
    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка подключения к серверу" << std::endl;
        close(sockfd);
        return 1;
    }

    // Отправка и получение сообщений
    while(true) {
        std::string message;
        std::cout << "Введите сообщение (введите 'exit' для выхода): ";
        std::getline(std::cin, message);

        if(message == "exit") {
            break;
        }

        // Отправка сообщения на сервер
        send(sockfd, message.c_str(), message.size(), 0);

        // Получение ответа от сервера
        char buffer[1024] = { 0 };
        int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
        if(bytes_received > 0) {
            std::cout << "Сервер вернул: " << std::string(buffer, bytes_received) << std::endl;
        } else {
            std::cerr << "Ошибка получения сообщения от сервера" << std::endl;
            break;
        }
    }

    // Закрытие сокета
    close(sockfd);
    return 0;
}