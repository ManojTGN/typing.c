#include "text.h"

#define TEXT_SIZE 50
uint8_t TEXT_LENGTH;
uint8_t TYPIST_AT;
Text** TEXTS;

void initText(){
    if(TEXTS != NULL){
        for(uint8_t i = 0; i < TEXT_SIZE; i++){
            if(TEXTS[i] != NULL){
                free(TEXTS[i]->content);
                free(TEXTS[i]);
            }
        }
    }

    TEXTS = (Text**) calloc(TEXT_SIZE,sizeof(Text*));
    TEXT_LENGTH = TYPIST_AT = 0;
}

Text* getCurrentText(){
    if(TEXTS == NULL) return NULL;
    return TEXTS[TYPIST_AT];
}

void setTypistTo(uint8_t textIndex){
    TYPIST_AT = textIndex;
}

bool isTextWrittern(){
    return (TEXTS == NULL || TEXTS[TYPIST_AT] == NULL || TEXTS[TYPIST_AT]->typistAt >= TEXTS[TYPIST_AT]->size);
}

uint8_t createText(){
    Text* newText = (Text*) calloc(1,sizeof(Text*));

    newText->size = 30;
    newText->content = "manojtgn developed this game!!";
    TEXTS[TEXT_LENGTH++] = newText;

    return TEXT_LENGTH-1;
}
