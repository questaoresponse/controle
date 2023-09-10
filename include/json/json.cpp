#include "json.h"
#include <map>
#include <string>
std::map<std::string,std::string> Json::parse(std::string texto2){
    std::map<std::string,std::string> meuMapa;
    std::string texto = texto2.substr(2, texto2.length() - 2);

    // Divide a string em pares chave-valor com base na vírgula
    size_t pos = 0;
    while ((pos = texto.find(',')) != std::string::npos) {
        std::string par = texto.substr(0, pos);
        texto.erase(0, pos + 1);

        // Divide o par chave-valor com base nos dois pontos
        size_t pos2 = par.find(':');
        if (pos2 != std::string::npos) {
            std::string chave = par.substr(0, pos2);
            std::string valor = par.substr(pos2 + 1);
            meuMapa[chave] = valor;
        }
    }

    // Trata o último par chave-valor
    size_t pos2 = texto.find(':');
    if (pos2 != std::string::npos) {
        std::string chave = texto.substr(0, pos2);
        std::string valor = texto.substr(pos2 + 1);
        meuMapa[chave] = valor;
    }
    return meuMapa;
}
std::string Json::stringify(std::map<std::string,std::string> dicionario){
    std::string json="{";
    int c=0;
    for (const auto& [chave, valor] : dicionario) {
        c==0 ? json+="{" : json+=",";
        json+=chave+":"+valor;
    }
    json+="}";
    return json;
}   