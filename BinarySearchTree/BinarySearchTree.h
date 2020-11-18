#ifndef _BinarySearchTree_
#define _BinarySearchTree_

//RIGHT > LEFT

#include <stdlib.h>
#include <stdio.h>
#include "Utils/Utils.h"

typedef int (*Compare)(void *, void *);

typedef struct BSTree
{
  struct BSTree *parent, *right, *left;

  void *value, *key;

  // compare returns 1 if the first argument is bigger than the second, 0 if equal
  // and -1 if lesser. it is meant to compare two keys
  Compare compare;
} BSTree;

BSTree *tree_init(void *, void *, int (*)(void *, void *));
void tree_destroy(BSTree *);
BSTree *push(BSTree *, void *, void *);
BSTree *pop(BSTree *);
BSTree *search(BSTree *, void *);
BSTree *max(BSTree *);
BSTree **list(BSTree *, int *);
int tree_size(BSTree *);
int tree_height(BSTree *);

#endif