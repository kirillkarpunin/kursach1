OBJ=./object_files
HEAD=./header_files
FUNC=./functions

ALL_OBJ=main.o menu.o text_io.o process_text.o create_struct.o memory_interaction.o
ALL_HEAD=$(HEAD)/menu.h $(HEAD)/text_io.h $(HEAD)/process_text.h $(HEAD)/structs.h $(HEAD)/memory_interaction.h

all: main

main: $(ALL_OBJ)
	gcc $(OBJ)/main.o $(OBJ)/menu.o $(OBJ)/text_io.o $(OBJ)/process_text.o $(OBJ)/create_struct.o $(OBJ)/memory_interaction.o -o main

main.o: main.c $(ALL_HEAD)
	gcc -c main.c -o $(OBJ)/main.o

menu.o: $(FUNC)/menu.c $(HEAD)/menu.h $(HEAD)/structs.h $(HEAD)/text_io.h $(HEAD)/process_text.h
	gcc -c $(FUNC)/menu.c -o $(OBJ)/menu.o

text_io.o: $(FUNC)/text_io.c $(HEAD)/text_io.h $(HEAD)/structs.h $(HEAD)/memory_interaction.h
	gcc -c $(FUNC)/text_io.c -o $(OBJ)/text_io.o

process_text.o: $(FUNC)/process_text.c $(HEAD)/process_text.h $(HEAD)/structs.h $(HEAD)/memory_interaction.h
	gcc -c $(FUNC)/process_text.c -o $(OBJ)/process_text.o

create_struct.o: $(FUNC)/create_struct.c $(HEAD)/structs.h
	gcc -c $(FUNC)/create_struct.c -o $(OBJ)/create_struct.o

memory_interaction.o: $(FUNC)/memory_interaction.c $(HEAD)/memory_interaction.h $(HEAD)/structs.h
	gcc -c $(FUNC)/memory_interaction.c -o $(OBJ)/memory_interaction.o 

