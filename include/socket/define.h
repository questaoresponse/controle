#ifndef MINHACLASSE_H
#define MINHACLASSE_H
#include <string>

class Socket {
public:
    Socket(std::string ht,int pt);
    void send_websocket_handshake();
    void read_websocket_response();
    void send_message(const char *message);
    void connect_socket();
    void data();
    void message(std::string data);
    void connection();
    void disconnect();
};
#endif
