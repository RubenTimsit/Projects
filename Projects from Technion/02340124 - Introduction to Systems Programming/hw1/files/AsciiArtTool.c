#include <stdio.h>
#include <stdlib.h>
#include "AsciiArtTool.h"


static int array_to_num( char* array, int n);
static char* list_to_string(RLEList list);


//implement the functions here

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList new_list = RLEListCreate();
    if(new_list == NULL)
    {
        return NULL;
    }
    char buffer[2];
    buffer[1] = '\0';
    while (fgets(buffer, 2, in_stream) != NULL)
    {
        RLEListAppend(new_list,buffer[0]);

    }
    return new_list;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    /*
    if(list == NULL || out_stream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
     */
    char* str = list_to_string(list);
    fputs(str, out_stream);
    free(str);
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list == NULL || out_stream ==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char* str = RLEListExportToString(list,&result);
    fputs(str, out_stream);
    free(str);
    return RLE_LIST_SUCCESS;

}


static int array_to_num( char* array, int n)
{
    int number = 0;
    for (int i = 0; i < n; i++)
    {
        array[i] -= '0';
        number = 10 * number + array[i];
    }
    return number;
}


static char* list_to_string(RLEList list)
{
    RLEListResult result;
    char* str = RLEListExportToString(list, &result);
    char* new_str = calloc(RLEListSize(list)+1,1);
  //  char* new_str = malloc(RLEListSize(list)+1);
    new_str[RLEListSize(list)] = '\0';
    int index = 0;
    int new_str_index = 0;
    int num_digits = 0;
    char* s = NULL;
    //char* old = NULL;
    int current = 0;
    while(str[index] != '\0')
    {
        char c = str[index];
        index++;
        s = calloc(2,1); //at least there is one digit

        if(s == NULL)
        {
            return NULL;
        }
        s[0] = str[index];
        num_digits++;
        int num_size = num_digits+1;
        index++;
        while(str[index] != '\n')
        {
            //old = s;
            s = realloc(s, num_size+1);
            //free(old);
            s[index -current-1] = str[index];
            num_digits++;
            num_size = num_digits+1;
            index++;
        }
        current = index;
        s[num_digits] = '\0';
        int occurrences = array_to_num(s, num_digits);
        free(s);
        s = NULL;
        num_digits = 0;
        num_size = 0;
        int max_size = new_str_index+occurrences;

        while( new_str_index < max_size)
        {

            new_str[new_str_index] = c;
            new_str_index++;
        }
        index++;
    }
    free(str);
    return new_str;
}


