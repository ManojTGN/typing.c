#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct TypingScreen {
    COORD cursor;
    COORD size;
    HANDLE hConsole;

    bool isInitalTextRendered;
    bool isBorderRendered;
    bool isTyping;

    char* border;
} Screen;

void initScreen(bool reinit);
void renderScreen();
bool isScreenResized();
void setRelativeCursorPos(int8_t x, int8_t y);

#endif /* SCREEN_H */
