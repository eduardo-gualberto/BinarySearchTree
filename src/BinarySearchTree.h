#ifndef _BinarySearchTree_
#define _BinarySearchTree_

//RIGHT > LEFT

#include <stdlib.h>
#include <stdio.h>
#include "Utils/Utils.h"

typedef int (*Compare_f)(void *, void *);

typedef struct BSTree
{
  struct BSTree *parent, *right, *left;

  void *value, *key;
  // compare returns 1 if the first argument is bigger than the second, 0 if equal
  // and -1 if lesser. it is meant to compare two keys
  Compare_f compare;
} Tree_t;

Tree_t *tree_init(void *, void *, Compare_f);
void tree_destroy(Tree_t *);
Tree_t *push(Tree_t *, void *, void *);
Tree_t *pop(Tree_t *);
Tree_t *search(Tree_t *, void *);
Tree_t *max(Tree_t *);
Tree_t **list(Tree_t *, int *);
int tree_size(Tree_t *);
int tree_height(Tree_t *);

#endif