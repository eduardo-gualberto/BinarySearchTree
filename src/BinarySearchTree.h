#ifndef _BinarySearchTree_
#define _BinarySearchTree_

//RIGHT > LEFT

#include <stdlib.h>
#include <stdio.h>
#include "Utils/Utils.h"

enum DIRECTION
{
  LEFT = 0,
  RIGHT = 1
};

typedef int (*Compare_f)(void *, void *);

typedef struct BSTree
{
  int balance, height;
  struct BSTree *parent, *right, *left;
  void *value, *key;
  Compare_f compare;
} Tree_t;

Tree_t *tree_init(void *, void *, Compare_f);
void tree_destroy(Tree_t *);
Tree_t *push(Tree_t *, void *, void *);
Tree_t *pop(Tree_t *);
Tree_t *popR(Tree_t *);
Tree_t *search(Tree_t *, void *);
Tree_t *max(Tree_t *);
Tree_t **list(Tree_t *, int *);
int tree_size(Tree_t *);
int tree_height(Tree_t *);
Tree_t *rotate(Tree_t *, enum DIRECTION);
int isAVL(Tree_t *t);

#endif