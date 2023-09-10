#include "functions.h"
#include <windows.h>
void Def::clickar(int x,int y){
    SetCursorPos(x, y);
    // Emule um clique com o botão esquerdo do mouse
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

}
void Def::rename(std::string inicio,std::string final){

}