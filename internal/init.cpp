#include <iostream>
#include <windows.h>

int main() {
    // Caminho para o executável que você deseja iniciar em segundo plano
    const char* programa = "./main.exe";

    // Comando para listar todos os processos com o nome desejado
    std::string nome(programa);
    std::string comando = "ps aux | grep " + nome;
FILE* arquivo = popen(comando.c_str(), "r");
    if (arquivo == nullptr) {
        std::cerr << "Erro ao executar o comando." << std::endl;
        return 1;
    }

    // Leia a saída do comando
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), arquivo) != nullptr) {
            // O processo está em execução (em primeiro plano ou segundo plano)
        } else {
            pclose(arquivo);
            STARTUPINFO si = {};
            si.cb = sizeof(STARTUPINFO);

            PROCESS_INFORMATION pi = {};

            // Tentar iniciar o processo em segundo plano
            if (CreateProcess(NULL,(LPSTR)programa, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
                std::cout << "Executável foi iniciado em segundo plano com sucesso." << std::endl;
                return 0;
                // Fechar os handles dos processos (opcional)
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            } else {
                std::cerr << "Falha ao iniciar o executável." << std::endl;
            }
    }

    return 0;
}
