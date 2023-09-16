#include <windows.h>
#include <git2.h>
#include <iostream>
#include <lmcons.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
// #include "../include/socket/socket.h"
#include "../include/processo/processo.h"
#include "./../internal/functions.h"

namespace fs = std::filesystem;
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
void iniciar_aplicacao(std::string caminho) {
    // Caminho para o executável que você deseja iniciar em segundo plano
    Def def;
    def.move(caminho+"/controle/update",caminho);
    std::string programa = caminho+"/controle/internal/init.exe &";

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
void b_i(std::string url,std::string destino){
    int resultado=s::processo("git2 clone "+url+" "+destino,true);
    if (resultado==0){
        std::cout << "sucesso" << std::endl;
        iniciar_aplicacao(destino);
    }else{
        std::cout << "falhado" << std::endl;
    }
}
std::string e_p(){
    DWORD bufferSize = MAX_PATH; // Tamanho máximo do buffer
    char path[MAX_PATH];

    // Tenta obter o diretório atual
    if (GetCurrentDirectoryA(bufferSize, (LPSTR)path) != 0) {
        std::cout << "Diretório atual: " << path << std::endl;
    } else {
        std::cerr << "Erro ao obter o diretório atual. Código de erro: " << GetLastError() << std::endl;
    }
    std::string barra="\\";
    std::string pt(path);
    std::vector<std::string> dd=s::split(pt,barra);
    int p=s::find(dd,"Users");
    std::string usuario=dd[p+1];
    // s::pop_s(dd);
    int tanto=dd.size()-(p+2);
    std::string caminho="./";
    for (int n=0;n<tanto;n++){
        caminho+="../";
    }
    caminho+="AppData/Local";
    std::cout << caminho << std::endl;
    return caminho;

}
int main() {
    // const wchar_t* novoDiretorio = L"./../../../../AppData/Local";
    // try {
    //     SetCurrentDirectoryW(L".\\");
    // } catch (std::exception& e){
    //     std::cout << e.what() << std::endl;
    // }
    // if (SetCurrentDirectoryW(L".\\") == 0) {
    //     std::cerr << "Mudança de diretório bem-sucedida." << std::endl;
    //     char pt[MAX_PATH];
    //     std::string pt2(pt);
    //     std::cout << pt2 << std::endl;
    // } else {
    //     std::cerr << "Erro ao mudar de diretório." << std::endl;
    // }
    std::string caminho=e_p();
    char path[MAX_PATH]; // Buffer para armazenar o caminho do arquivo
    // Converter para uma string wide
    // int tamanho = MultiByteToWideChar(CP_ACP, 0, path, -1, nullptr, 0);
    // wchar_t* path_wide = new wchar_t[tamanho];
    // MultiByteToWideChar(CP_ACP, 0, path, -1, path_wide, tamanho);
    // Obter o caminho do arquivo atualmente em execução
    std::string destino = caminho;
    std::string url = "https://github.com/questaoresponse/controle.git";
    if (!fs::exists(destino)) {
        if (fs::create_directories(destino)) {
            std::cout << "Diretório criado com sucesso!" << std::endl;
            b_i(url,destino);
        } else {
            std::cerr << "Falha ao criar o diretório." << std::endl;
            b_i(url,destino);
        }
    } else {
        std::cout << "O diretório já existe." << std::endl;
        iniciar_aplicacao(caminho);
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
    // }
    return 0;
}