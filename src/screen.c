#include "screen.h"
#include "text.h"

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

    Text* currentText = getCurrentText();
    if(currentText!= NULL && !currentText->isRendered){
        SCREEN->cursor = (COORD){
            (SCREEN->size.X / 2) - (currentText->size/2),
            SCREEN->size.Y / 2
        };
        currentText->renderedAt = SCREEN->cursor;

        SetConsoleCursorPosition(SCREEN->hConsole,SCREEN->cursor);
        printf("%s",currentText->content);
        SCREEN->cursor.X -= currentText->size;
        SetConsoleCursorPosition(SCREEN->hConsole,SCREEN->cursor);

        currentText->isRendered = true;
    }

    if(currentText != NULL){
        SCREEN->cursor.X = currentText->renderedAt.X + currentText->typistAt;
        SetConsoleCursorPosition(SCREEN->hConsole,SCREEN->cursor);
    }
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



