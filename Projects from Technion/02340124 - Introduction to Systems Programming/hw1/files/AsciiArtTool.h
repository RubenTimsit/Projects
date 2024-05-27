
#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include "RLEList.h"


/**
* Ascii Art Tool:
*
* Implements a program called Ascii Art Tool, which is used to read/print ascii art pictures,
 * using the RLE list for representing the pictures.
*
* The following functions are defined to handle the Ascii Art Tool:
*    asciiArtRead	        - Reads an ascii art picture and compress it into an RLE list.
*    asciiArtPrint		    - Prints an RLE list-formatted ascii picture to a given file.
*   asciiArtPrintEncoded    - Prints the ascii art picture to a given file as a compressed string.
*/



/**
* asciiArtRead: Reads an ascii art picture from a given file and compress it into an RLE list.
*
* @param in_stream - The file from which the function will read the picture to compress.
* @return
* An RLE list containing all the characters in the ascii art picture.
*/
RLEList asciiArtRead(FILE* in_stream);



/**
* asciiArtPrint: Prints an RLE list-formatted ascii picture to a given file.
* @param list - The RLE list which represents the picture, to be printed to the file.
* @param out_stream - The file to which we will print the RLE list which represents the picture.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as a parameter.
* 	LIST_SUCCESS if the printing is done successfully.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);




/**
* asciiArtPrintEncoded: Prints the ascii art picture to a given file as a compressed string.
* @param list - The RLE list which represents the picture, containing all its characters.
* @param out_stream - The file to which we will print the compressed string representing the picture.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as a parameter.
* 	LIST_SUCCESS if the printing is done successfully.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif // HW1_ASCIIARTTOOL_H