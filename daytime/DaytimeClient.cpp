#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    if(argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <server_ip> <порт>" << std::endl;
        return 1;
    }

    const char* ip_address = argv[1];
    int port_number = std::stoi(argv[2]);

    // Создание UDP сокета
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket < 0) {
        perror("Не удалось создать сокет");
        return 1;
    }

    // Настройка адреса сервера
    sockaddr_in server_address;
    std::memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);

    if(inet_pton(AF_INET, ip_address, &server_address.sin_addr) <= 0) {
        std::cerr << "Неверный адрес / Адрес не поддерживается" << std::endl;
        close(udp_socket);
        return 1;
    }

    // Отправка запроса на сервер
    const char* message = "ЗАПРОС";
    if(sendto(udp_socket, message, std::strlen(message), 0, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Не удалось отправить данные");
        close(udp_socket);
        return 1;
    }

    // Получение ответа от сервера
    char response_buffer[BUFFER_SIZE];
    socklen_t address_length = sizeof(server_address);
    int response_length =
        recvfrom(udp_socket, response_buffer, BUFFER_SIZE - 1, 0, (sockaddr*)&server_address, &address_length);
    if(response_length < 0) {
        perror("Не удалось получить данные");
        close(udp_socket);
        return 1;
    }

    response_buffer[response_length] = '\0'; // Завершение строки
    std::cout << "Данные от сервера: " << response_buffer << std::endl;

    // Закрытие сокета
    close(udp_socket);
    return 0;
}