// #include "./socket.cpp"
#include "../include/json/json.h"
#include "../include/json/json.cpp"
#include "../include/socket/socket.h"
#include "../include/socket/socket.cpp"
#include "../include/socket/my.h"
#include <iostream>
#include <map>
#include <string>
#include "functions.h"
#include "functions.cpp"

Def def;
Event::Event(){

}
void Event::connect(){
    printf("conectado");  
}
void Event::data(std::string data_str){
    Json json;
    std::map<std::string,std::string> data=json.parse(data_str);
    for (const auto& [chave, valor] : data) {
        std::cout << chave << std::endl;
        std::cout << valor << std::endl;
    }
    std::string tipo=data["tipo"];
    if (tipo=="click"){
        def.clickar(std::stoi(data["x"]),std::stoi(data["y"]));
    }
    if (tipo=="rename"){
        def.rename(data["inicio"],data["final"]);
    }
}
void Event::disconnect(){
    printf("desconectado");  
}
int main(){
    Socket socket("127.0.0.1",3000);
    // socket.on("connect",[&socket](const std::string &data){
    //     socket.send_message("conectei");
    // });
    // socket.on("data",[](const std::string & data){
    //     std::cout << "dados" << std::endl;
    // });
    // socket.on("disconnect",[&socket](const std::string & data){
    //     std::cout << data << std::endl;
    // });
    // socket.d_connect()
    std::cin.get();
    return 0;
}