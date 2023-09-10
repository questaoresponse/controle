#ifndef MY_H
#define MY_H

#include <string>
class Event {
    public:
        Event();
        void connect();
        void disconnect();
        void data(std::string resposta);
};
#endif