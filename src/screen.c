#include "screen.h"

Screen* SCREEN = NULL;

void initScreen(bool reinit){
    if(!reinit && SCREEN != NULL) return;
    
    if(SCREEN != NULL){
        system("cls");
        free(SCREEN);
    }

    SCREEN = (Screen*)  calloc(1,sizeof(Screen));
    SCREEN->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SCREEN->cursor = (COORD) {0,0};

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(SCREEN->hConsole, &csbi);
    SCREEN->size = (COORD) {
        csbi.srWindow.Right - csbi.srWindow.Left + 1,
        csbi.srWindow.Bottom - csbi.srWindow.Top + 1
    };
}

void renderScreen(){
    if(SCREEN == NULL) return;

    if(!SCREEN->isBorderRendered){
        SCREEN->border = (char*) calloc(SCREEN->size.X + 1,sizeof(char)); 
        memset(SCREEN->border,(int)'#',SCREEN->size.X);
        
        SetConsoleCursorPosition(SCREEN->hConsole,(COORD){0,0});
        printf("%s",SCREEN->border);

        SetConsoleCursorPosition(SCREEN->hConsole,(COORD){0,SCREEN->size.Y-1});
        printf("%s",SCREEN->border);

        SCREEN->isBorderRendered = true;
    }

    if(!SCREEN->isInitalTextRendered){

    }

}

void renderHandler(){
    if(isScreenResized()){
        initScreen(true);
        return;
    }

    renderScreen();
}

bool isScreenResized(){
    if(SCREEN == NULL) return false;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(SCREEN->hConsole, &csbi);

    return (
        !(SCREEN->size.X == csbi.srWindow.Right - csbi.srWindow.Left + 1 &&
        SCREEN->size.Y == csbi.srWindow.Bottom - csbi.srWindow.Top + 1)
    );
}

