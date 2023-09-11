#include "define.h"
#include <windows.h>
#include <iostream>
void Def::clickar(int x,int y){
    SetCursorPos(x, y);
    // Emule um clique com o botão esquerdo do mouse
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

}
void Def::rename(std::string nome,std::string novo_nome){
    const char* nomeAtual = nome.c_str();
    const char* novoNome = novo_nome.c_str();

    if (std::rename(nomeAtual, novoNome) == 0) {
        std::cout << "Arquivo renomeado com sucesso." << std::endl;
    } else {
        std::perror("Erro ao renomear o arquivo");
    }

}  
void Def::remove(std::string nome){
    const char* nomeArquivo = nome.c_str();

    if (std::remove(nomeArquivo) == 0) {
        std::cout << "Arquivo excluído com sucesso." << std::endl;
    } else {
        std::perror("Erro ao excluir o arquivo");
    }
}
void Def::move(std::string caminho,std::string novo_caminho){
    const char* arquivoOrigem = caminho.c_str();
    const char* novoCaminho = novo_caminho.c_str();

    if (std::rename(arquivoOrigem, novoCaminho) == 0) {
        std::cout << "Arquivo movido com sucesso." << std::endl;
    } else {
        std::perror("Erro ao mover o arquivo");
    }
}
