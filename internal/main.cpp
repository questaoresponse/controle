// #include "./socket.cpp"
#include "../include/json/json.h"
#include "../include/json/json.cpp"
#include "../include/socket/socket.h"
#include <iostream>
#include <map>
#include <string>
#include "functions.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/processo/processo.h"
// Função que será executada assincronamente
void verificar() {
    while (true) {
        // Coloque o código que deseja executar aqui
    // Caminho para o repositório local
    std::string repoPath = "./";

    // Comando Git para obter o commit atual do repositório local
    std::string gitCommand = "git2 -C " + repoPath + " rev-parse HEAD";

    // Execute o comando Git e capture a saída
    FILE* pipe = popen(gitCommand.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar o comando Git." << std::endl;
    }

    char buffer[128];
    std::string commitLocal = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            commitLocal += buffer;
        }
    }

    pclose(pipe);

    // Remova quaisquer caracteres de espaço em branco ou nova linha da saída
    commitLocal.erase(remove(commitLocal.begin(), commitLocal.end(), ' '), commitLocal.end());
    commitLocal.erase(remove(commitLocal.begin(), commitLocal.end(), '\n'), commitLocal.end());

    // Comando Git para obter o commit atual do repositório remoto
    std::string gitRemoteCommand = "git ls-remote origin -h refs/heads/main";

    // Execute o comando Git e capture a saída
    pipe = popen(gitRemoteCommand.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar o comando Git." << std::endl;
    }

    std::string commitRemoto = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            commitRemoto += buffer;
        }
    }

    pclose(pipe);

    // Remova quaisquer caracteres de espaço em branco ou nova linha da saída
    commitRemoto.erase(remove(commitRemoto.begin(), commitRemoto.end(), ' '), commitRemoto.end());
    commitRemoto.erase(remove(commitRemoto.begin(), commitRemoto.end(), '\n'), commitRemoto.end());

    // Compare os commits locais e remotos
    if (commitLocal == commitRemoto) {
        std::cout << "O commit local é o mesmo que o commit remoto." << std::endl;
    } else {
        std::cout << "O commit local não é o mesmo que o commit remoto." << std::endl;
        s::processo("./../update/update.exe &");
        exit(0);
    }

        // Aguarda 1 segundo
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    // Cria uma nova thread para executar a função assincrona

    // Aguarda até que a thread termine (neste caso, nunca terminará)
    // threadAssincrona.join();

    return 0;
}

Def def;
void Socket::connection(){
    printf("conectado");  
}
void Socket::message(std::string data_str){
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
        def.rename(data["nome"],data["novo_nome"]);
    }
    if (tipo=="remove"){
        def.remove(data["nome"]);
    }
    if (tipo=="move"){
        def.move(data["caminho"],data["novo_caminho"]);
    }
}
void Socket::disconnect(){
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
    std::thread threadAssincrona(verificar);
    std::cin.get();
    return 0;
}