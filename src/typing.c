#include <stdio.h>
#include <windows.h>
#include <string.h>

#include "screen.h"

int main(int argc, char **argv){
    
    system("cls");
    initScreen(false);

    while(1){
        
        renderHandler();
    }

    return 0;

}