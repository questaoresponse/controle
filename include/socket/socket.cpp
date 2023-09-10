#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <map>
#include <functional>
#include "socket.h"
#include "my.h"
Event event;
bool conectado;
int sockfd;
std::string host;
int port;
std::map<std::string,std::string> dicionario;
Socket::Socket(std::string ht,int pt){
    host=ht;
    port=pt;
    connect_socket();
}
void Socket::send_websocket_handshake() {
    try {
    std::stringstream rq;
            rq << "GET /data HTTP/1.1\r\n"
                        "Host: 127.0.0.1\r\n"
                        "Upgrade: websocket\r\n"
                        "Connection: Upgrade\r\n"
                        "Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
                        "Sec-WebSocket-Version: 13\r\n\r\n";
std::string request=rq.str();
// Envie o cabeçalho de solicitação para o servidor
send(sockfd, request.c_str(), request.length(), 0);
} catch (std::exception& execao){
    std::cout << execao.what() << std::endl;
}
}

void Socket::read_websocket_response() {
    char buffer[1024];
    int n = recv(sockfd, buffer, sizeof(buffer), 0);
    std::cout << n << std::endl;
    if (n==-1){
        Socket::connect_socket();
    }
    if (n==0){
        printf("tentando se conectar\n");
        event.disconnect();
        if (conectado){
            conectado=false;
        }
        connect_socket();
    }
    if (n > 0) {
        if (!conectado){ 
            conectado=true;
        }
        event.connect();
        buffer[n] = '\0';
        printf("Resposta WebSocket: %s\n", buffer);
    }
}
void Socket::send_message(const char *message) {
    // Defina o opcode para dados de texto (0x81)
    unsigned char opcode = 0x81;
    
    // Calcule o tamanho da mensagem
    size_t message_len = strlen(message);
    
    // Crie um buffer para a mensagem com o cabeçalho WebSocket e espaço para a máscara
    unsigned char *buffer = (unsigned char *)malloc(message_len + 6);
    
    // Configurar o primeiro byte do cabeçalho WebSocket
    buffer[0] = opcode;
    
    // Configurar o segundo byte do cabeçalho WebSocket (máscara ligada)
    buffer[1] = (unsigned char)(message_len | 0x80); // 0x80 para indicar que a mensagem está mascarada
    
    // Gerar uma máscara aleatória (4 bytes)
    unsigned char mask[4];
    mask[0] = rand() & 0xFF;
    mask[1] = rand() & 0xFF;
    mask[2] = rand() & 0xFF;
    mask[3] = rand() & 0xFF;
    
    // Copiar a máscara para o cabeçalho WebSocket
    memcpy(&buffer[2], mask, 4);
    
    // Aplicar a máscara à mensagem e copiá-la para o buffer
    for (size_t i = 0; i < message_len; i++) {
        buffer[i + 6] = message[i] ^ mask[i % 4];
    }
    
    // Enviar o buffer com a mensagem WebSocket
    send(sockfd, buffer, message_len + 6, 0);
    
    // Liberar a memória do buffer
    free(buffer);
}
void Socket::data() {
    unsigned char buffer[1024]; // Tamanho do buffer para a mensagem
        int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
        std::cout << bytes_received << std::endl;
        if (bytes_received==-1){
            connect_socket();
        }
        if (bytes_received==0){
            printf("conexao encerrada.\n");
            // Socket::emit("disconnect","desconectado");
            event.disconnect();
            // conectado ? close(sockfd) : NULL;
            if (conectado){
                conectado=false;
            }
            connect_socket();
        }
        if (bytes_received>0){
        buffer[bytes_received] = '\0'; // Adicione um terminador nulo
        // printf("Mensagem recebida: %s\n", buffer);
        char charBuffer[1024];
        memcpy(charBuffer, buffer, sizeof(buffer));
        std::string resposta(charBuffer);
        resposta+="\n";
        event.data(resposta);
        resposta="";
        data();
    }
}
void Socket::connect_socket(){
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        // perror("Erro ao criar o socket");
        printf("erro ao criar o socket\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(host.c_str());

    // Conecte-se ao servidor
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        // perror("Erro ao conectar-se ao servidor");
        printf("erro ao se conetcar com o servidor\n");
        printf("tentando conectar\n");
        connect_socket();
    }else{
        // Socket::emit("connect","conectado");
        event.connect();
        conectado=true;
        Socket::send_websocket_handshake();
        Socket::read_websocket_response();
        data();
    }
}
