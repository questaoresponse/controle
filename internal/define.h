#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
class Def {
public:
    void clickar(int x,int y);
    void rename(std::string nome,std::string novo_nome);
    void remove(std::string nome);
    void move(std::string caminho,std::string novo_caminho);
};
#endif