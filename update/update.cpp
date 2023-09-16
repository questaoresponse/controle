#include "update.h"
#include "windows.h"
#include "../include/processo/processo.h"
#include "./../internal/functions.h"
int main(){
    Def def;
    def.remove("./../controle");
    int r=s::processo("git2 clone ./../",true);
    s::processo("./../controle/internal/main.exe &");
    return 0;
}