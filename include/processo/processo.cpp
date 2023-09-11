#include "define.h"
#include <string>
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
        return 0;
        // Fechar os handles dos processos (opcional)
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
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
}