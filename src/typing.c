#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include "screen.h"
#include "text.h"

bool isTypingRunning = false;

void keyEventHandler(){
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000){
        isTypingRunning = false;
        return;
    }else if(GetAsyncKeyState(VK_BACK) & 0x8000){
        Text* currentText = getCurrentText();
        if(currentText->typistAt == 0) return;
        
        currentText->typistAt--;
        Sleep(150);
        printf("\b%c",currentText->content[currentText->typistAt]);
    }else if(kbhit()){
        Text* currentText = getCurrentText();
        char ch = getch();
        if(ch == currentText->content[currentText->typistAt]){
            printf("%c",toupper(ch));
            currentText->typistAt++;
        }

    }
}

int main(int argc, char **argv){
    
    system("cls");
    initScreen(false);
    initText();
    isTypingRunning = true;

    while(isTypingRunning){
        if(isScreenResized()){
            initScreen(true);
            Text* currentText = getCurrentText();
            if(currentText!=NULL) currentText->isRendered=false;
        }

        if(isTextWrittern()){
            uint8_t textIndex = createText();
            setTypistTo(textIndex);
        }

        renderScreen();
        keyEventHandler();
    }

    system("cls");
    return 0;

}