COMPILER = gcc
IN_FILES = ./src/BinarySearchTree.c  ./src/Utils/Utils.c ./main.c
OUT_FILE = main
FLAGS = 

all:
	+@-$(COMPILER) $(IN_FILES) -o $(OUT_FILE) $(FLAGS)
	+@-./main
	+@-rm main