#include "../include/processo/processo.h"
int main(){
    s::processo("git.exe config --global user.name \"questaoresponse\"",true);
    s::processo("git.exe config --global user.email \"eneagonlosamigos@gmail.com\"",true);
    s::processo("git.exe add ./..",true);
    s::processo("git.exe commit -m \"adicionar pasta\"",true);
    s::processo("git.exe push -u origin main",true);
    return 0;
}