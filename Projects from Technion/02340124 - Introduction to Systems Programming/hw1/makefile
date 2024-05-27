CC = gcc
MAIN= tool/main
ASCII_ART_TOOL= tool/AsciiArtTool
RLELIST= /home/mtm/public/2122b/ex1/RLEList
OBJS = $(ASCII_ART_TOOL).o $(MAIN).o RLEList.o
EXEC = AsciiArtTool
CFLAGS = -std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG -g
$(EXEC) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS)  -o $@
$(ASCII_ART_TOOL).o: $(ASCII_ART_TOOL).c $(RLELIST).h $(ASCII_ART_TOOL).h
$(MAIN).o: $(MAIN).c $(RLELIST).h $(ASCII_ART_TOOL).h
RLEList.o: RLEList.c $(RLELIST).h
clean:
	  rm -f $(OBJS) $(EXEC)





	

