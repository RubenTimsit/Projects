#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RLEList.h"
#include "AsciiArtTool.h"




/**This  Is A Function For Mapping The AsciiArt Picture according To The -i Flag: **/
char invert_picture(char c)
{
    if(c == 64) //if the char in the picture is: '@'
    {
        c = c - 32;  //invert it to space char
        return c;
    }
    if(c == 32) //if the char in the picture is: ' '
    {
        c = c + 32; //invert it to '@'
        return c;
    }
    return c;
}


int main(int argc, char** argv) {
    FILE* input =  fopen(argv[2], "r");
    if (!input) {
        return 1;
    }
    FILE* output =  fopen(argv[3], "w");
    if (!output) {
        fclose(input);
        return 1;
    }
    if(!strcmp(argv[1], "-e"))
    {
        RLEList list = asciiArtRead(input);
        if(list == NULL)
        {
            return 1;
        }
        asciiArtPrintEncoded(list,output);
        RLEListDestroy(list);
    }
    else
    {
        RLEList list = asciiArtRead(input);
        RLEListMap(list,invert_picture);
        asciiArtPrint(list,output);
        RLEListDestroy(list);
    }
    fclose(input);
    fclose(output);
    return 0;
}