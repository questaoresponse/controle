#include "define.h"
#include <string>
#include <regex>
#include <iostream>
#include <windows.h>

namespace s {
int processo(std::string nome,bool await=false){
    const char* programa=nome.c_str();
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    if (CreateProcessA(NULL,(LPSTR)programa, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        if (await){
            WaitForSingleObject(pi.hProcess, INFINITE);
        }
        // Fechar os handles dos processos (opcional)
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return 0;
    } else {
        return 1;
    }
}
int rodando(std::string nome){
    std::string comando = "ps aux | grep " + nome;
    FILE* arquivo = popen(comando.c_str(), "r");
    if (arquivo == nullptr) {
        return -1;
    }
    // Leia a saída do comando
    char buffer[128];
    if (fgets(buffer, sizeof(buffer), arquivo) != nullptr) {
        return 0;
        // O processo está em execução (em primeiro plano ou segundo plano)
    } else {
        pclose(arquivo);
        return 1;
    }
}
std::vector<std::string> split(const std::string& texto, const std::string& divisor) {
    std::vector<std::string> partes;
    size_t pos = 0;
    size_t start = 0;

    while ((pos = texto.find(divisor, start)) != std::string::npos) {
        partes.push_back(texto.substr(start, pos - start));
        start = pos + divisor.length();
    }

    // Adiciona a última parte após o último divisor
    partes.push_back(texto.substr(start));

    return partes;
}

int find(std::vector<std::string> nomes,std::string nome_procurado){
    for (size_t i = 0; i < nomes.size(); ++i) {
        if (nomes[i] == nome_procurado) {
            return i;
            break; // Termina o loop assim que o nome é encontrado
        }
    }
    return -1;
}
int find_s(std::string nomes,std::string nome_procurado){
    size_t pos=nomes.find(nome_procurado);
    if (pos != std::string::npos) {
        return 1;
    } else {
        return -1;
    }
}
int find_map(std::map<std::string,std::string> dici,std::string chave){
    auto it = dici.find(chave);
        if (it != dici.end()) {
            return 0;
        } else {
            return -1;
        }
}
void pop_s(std::vector<std::string>& meuVector){
    meuVector.erase(meuVector.begin(), meuVector.begin() + 3);
}
}