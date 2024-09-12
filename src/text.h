#ifndef TEXT_H
#define TEXT_H

#include <windows.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TypingText{
    uint8_t size;
    char* content;
    uint8_t typistAt;

    bool isRendered;
    COORD renderedAt;
} Text;

void initText();
void setTypistTo(uint8_t);

uint8_t createText();
Text* getCurrentText();

bool isTextWrittern();

#endif /* TEXT_H */