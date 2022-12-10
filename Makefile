CC=gcc -Wall
OBJ=./object_files
HEAD=./header_files
FUNC=./functions

ALL_OBJ=$(OBJ)/main.o $(OBJ)/menu.o $(OBJ)/text_io.o $(OBJ)/preprocess_text.o $(OBJ)/create_struct.o $(OBJ)/memory_interaction.o $(OBJ)/del_sents_more_10_words.o $(OBJ)/highlight_word.o $(OBJ)/replace_tsya.o $(OBJ)/sort_text.o
ALL_HEAD=$(HEAD)/menu.h $(HEAD)/text_io.h $(HEAD)/preprocess_text.h $(HEAD)/structs.h $(HEAD)/memory_interaction.h $(HEAD)/del_sents_more_10_words.h $(HEAD)/highlight_word.h $(HEAD)/replace_tsya.h $(HEAD)/sort_text.h

all: main clear

main: main.o menu.o text_io.o preprocess_text.o create_struct.o memory_interaction.o del_sents_more_10_words.o highlight_word.o replace_tsya.o sort_text.o
	$(CC) $(ALL_OBJ) -o main

main.o: main.c $(HEAD)/menu.h $(HEAD)/text_io.h $(HEAD)/preprocess_text.h $(HEAD)/structs.h $(HEAD)/memory_interaction.h
	$(CC) -c main.c -o $(OBJ)/main.o

menu.o: $(FUNC)/menu.c $(HEAD)/menu.h $(HEAD)/structs.h $(HEAD)/text_io.h $(HEAD)/del_sents_more_10_words.h $(HEAD)/highlight_word.h $(HEAD)/replace_tsya.h $(HEAD)/sort_text.h
	$(CC) -c $(FUNC)/menu.c -o $(OBJ)/menu.o

text_io.o: $(FUNC)/text_io.c $(HEAD)/text_io.h $(HEAD)/structs.h $(HEAD)/memory_interaction.h
	$(CC) -c $(FUNC)/text_io.c -o $(OBJ)/text_io.o

preprocess_text.o: $(FUNC)/preprocess_text.c $(HEAD)/preprocess_text.h $(HEAD)/structs.h $(HEAD)/memory_interaction.h
	$(CC) -c $(FUNC)/preprocess_text.c -o $(OBJ)/preprocess_text.o

create_struct.o: $(FUNC)/create_struct.c $(HEAD)/structs.h
	$(CC) -c $(FUNC)/create_struct.c -o $(OBJ)/create_struct.o

memory_interaction.o: $(FUNC)/memory_interaction.c $(HEAD)/memory_interaction.h $(HEAD)/structs.h
	$(CC) -c $(FUNC)/memory_interaction.c -o $(OBJ)/memory_interaction.o

del_sents_more_10_words.o: $(FUNC)/del_sents_more_10_words.c $(HEAD)/del_sents_more_10_words.h $(HEAD)/memory_interaction.h $(HEAD)/structs.h
	$(CC) -c $(FUNC)/del_sents_more_10_words.c -o $(OBJ)/del_sents_more_10_words.o

highlight_word.o: $(FUNC)/highlight_word.c $(HEAD)/highlight_word.h $(HEAD)/memory_interaction.h $(HEAD)/structs.h $(HEAD)/text_io.h
	$(CC) -c $(FUNC)/highlight_word.c -o $(OBJ)/highlight_word.o

replace_tsya.o: $(FUNC)/replace_tsya.c $(HEAD)/replace_tsya.h $(HEAD)/memory_interaction.h $(HEAD)/structs.h
	$(CC) -c $(FUNC)/replace_tsya.c -o $(OBJ)/replace_tsya.o

sort_text.o: $(FUNC)/sort_text.c $(HEAD)/sort_text.h $(HEAD)/structs.h
	$(CC) -c $(FUNC)/sort_text.c -o $(OBJ)/sort_text.o

clear: main
	rm -f $(OBJ)/*.o
