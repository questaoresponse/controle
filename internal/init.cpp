#include <iostream>
#include <windows.h>
#include "../include/processo/processo.h"
int main() {
    std::string nome = "./main.exe";
    int rs=s::processo(nome);
    if (rs==1){
            int resultado=s::processo(nome);
            if (resultado==0){
                std::cout << "executado" << std::endl;
            }else{
                std::cout << "nao executado" << std::endl;
            }
    }

    return 0;
}
