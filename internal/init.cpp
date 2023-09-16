#include <iostream>
#include <windows.h>
#include "../include/processo/processo.h"
int main() {
    std::string nome = "main.exe &";
    std::string nome_p="main.exe";
    int rs=s::rodando(nome_p);
    if (rs==1){
            int resultado=s::processo(nome);
            if (resultado==0){
                std::cout << "executado" << std::endl;
                return 0;
            }else{
                std::cout << "nao executado" << std::endl;
                return 0;
            }
    }

    return 0;
}
