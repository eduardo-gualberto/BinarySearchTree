IN_FILES = BinarySearchTree/Utils/Utils.c main.c BinarySearchTree/BinarySearchTree.c
COMPILER = gcc
OUT_FILE = main

all:
	+@-echo "compiling and running...\n"
	+@-$(COMPILER) $(IN_FILES) -o $(OUT_FILE)
	+@-./$(OUT_FILE)
	+@-rm ./main