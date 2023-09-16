#include <iostream>
#include <windows.h>
#include <cstdio>
#include "../include/processo/processo.h"

int main() {
    // Caminho para o executável que você deseja iniciar em segundo plano
    std::string nome = "./install_dir.exe &";
    int rs=s::rodando(nome);
    if (rs==1){
        int resultado=s::processo(nome);
        if (resultado==0){
            std::cout << "Executável foi iniciado em segundo plano com sucesso." << std::endl;
            return 0;
        } else {
            std::cerr << "Falha ao iniciar o executável." << std::endl;
        }
    } if (rs==0){
        std::cout << "Já está rodando" << std::endl;
    }

    return 0;
}
