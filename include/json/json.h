#ifndef JSON_H
#define JSON_H
#include <string>
#include <map>
class Json {
public:
    std::map<std::string,std::string> parse(std::string texto);
    std::string stringify(std::map<std::string,std::string> dicionario);
};
#endif