#ifndef _BinarySearchTree_
#define _BinarySearchTree_

//RIGHT > LEFT

#include <stdlib.h>
#include <stdio.h>
#include "Utils/Utils.h"

typedef struct BSTree
{
  int value, key;
  struct BSTree *parent, *right, *left;

  //implementações futuras
  // int vsize, ksize;
  // void (*compare)(void *, void *);
} BSTree;

BSTree *tree_init(int, int);
void tree_destroy(BSTree *);
BSTree *push(BSTree *, int, int);
BSTree *pop(BSTree *);
BSTree *search(BSTree *, int);
BSTree *max(BSTree *);
BSTree **list(BSTree *, int *);
int tree_size(BSTree *);
int tree_height(BSTree *);

#endif