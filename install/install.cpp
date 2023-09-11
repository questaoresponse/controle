#include <windows.h>
#include <git2.h>
#include <iostream>
#include <lmcons.h>
#include <iostream>
#include <fstream>
// #include "../include/socket/socket.h"
#include "../include/processo/processo.h"
// Função de callback para escrever os dados do arquivo
// size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
//     size_t total_size = size * nmemb;
//     std::ostream& output = *static_cast<std::ostream*>(userp);

//     if (output.write(static_cast<char*>(contents), total_size)) {
//         return total_size;
//     }

//     return 0; // Retorna 0 para indicar erro
// }
// int clonar(std::string url,std::string destino){
//     CURL* curl;
//     CURLcode res;
//     const char* url = url.c_str();
//     const char* output_file = (destino+"controle.zip").c_str();

//     // Inicializar a biblioteca libcurl
//     curl = curl_easy_init();
//     if (curl) {
//         // Configurar a URL para baixar
//         curl_easy_setopt(curl, CURLOPT_URL, url);

//         // Configurar a função de callback para escrever os dados no arquivo
//         std::ofstream output_stream(output_file, std::ofstream::binary);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output_stream);

//         // Realizar a solicitação HTTP e baixar o arquivo
//         res = curl_easy_perform(curl);

//         // Verificar se a solicitação foi bem-sucedida
//         if (res != CURLE_OK) {
//             std::cerr << "Erro ao baixar o arquivo: " << curl_easy_strerror(res) << std::endl;
//             return 2;
//         }

//         // Finalizar a sessão do cURL
//         curl_easy_cleanup(curl);
//     } else {
//         std::cerr << "Erro ao inicializar o cURL." << std::endl;
//         return 1;
//     }

//     return 0;
// }
void iniciar_aplicacao(std::string usuario) {
    // Caminho para o executável que você deseja iniciar em segundo plano
    std::string programa = "C:/Users/"+usuario+"AppData/Local/controle/internal/init.exe";

    // Comando para listar todos os processos com o nome desejado
    int rs=s::rodando(programa);
        if (rs==1){
            int resultado=s::processo(programa);
            if (resultado==0){
                return;
            } else {
                std::cerr << "Falha ao iniciar o executável." << std::endl;
            }
        }
    return;
};
int main() {
    char path[MAX_PATH]; // Buffer para armazenar o caminho do arquivo
    // Converter para uma string wide
    // int tamanho = MultiByteToWideChar(CP_ACP, 0, path, -1, nullptr, 0);
    // wchar_t* path_wide = new wchar_t[tamanho];
    // MultiByteToWideChar(CP_ACP, 0, path, -1, path_wide, tamanho);
    // Obter o caminho do arquivo atualmente em execução
    DWORD result = GetModuleFileNameA(NULL, path, MAX_PATH);
    if (result == 0) {
        std::cerr << "Erro ao obter o caminho do arquivo." << std::endl;
        return 1;
    }
    //delete[] path_wide;
    std::cout << "Caminho do arquivo atual: " << path << std::endl;

    // Dividir o caminho usando '\' como separador
    char* token = strtok(path, "\\");
    int count = 0;
    std::string usuario_char;

    while (token != nullptr) {
        if (count == 2) {
            usuario_char = token;
            break;
        }
        token = strtok(nullptr, "\\");
        count++;
    }
    
    if (!usuario_char.empty()) {
    std::string usuario(usuario_char);
    std::string destino = "C:\\Users\\"+usuario+"AppData\\Local";
    std::string url = "https://github.com/questaoresponse/controle.git";
    int resultado=s::processo("git "+url+" "+destino,true);
    if (resultado==0){
        std::cout << "sucesso" << std::endl;
    }else{
        std::cout << "falhado" << std::endl;
    }
    // git_repository* repo = nullptr;
    // int erro = git_clone(&repo, url, destino, nullptr);
    // git_repository_free(repo);
    // git_libgit2_shutdown();
    // if (erro == 0) {
    //     std::cout << "Repositório clonado com sucesso!" << std::endl;
    //     iniciar_aplicacao(usuario);
    //     return 0;
    // } else {
    //     std::cerr << "Erro ao clonar o repositório: " << giterr_last()->message << std::endl;
    // }
    }
    return 0;
}