#ifndef _BinarySearchTree_
#define _BinarySearchTree_

//RIGHT > LEFT

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Utils/Utils.h"
#include <string.h>

enum DIRECTION
{
  LEFT = 0,
  RIGHT = 1
};

typedef int (*Compare_f)(void *, void *);

typedef struct BSTree
{
  int balance;
  struct BSTree *parent, *right, *left;
  void *value, *key;
  size_t keysize;
  Compare_f compare;
} Tree_t;

Tree_t *tree_init(void *, void *, size_t, Compare_f);
void tree_destroy(Tree_t *);
Tree_t *tree_push(Tree_t *, void *, void *);
Tree_t *tree_pop(Tree_t *, void *);
Tree_t *tree_search(Tree_t *, void *);
Tree_t *tree_max(Tree_t *);
Tree_t **tree_list(Tree_t *, int *);
int tree_size(Tree_t *);
int tree_height(Tree_t *);
Tree_t *tree_rotate(Tree_t *, enum DIRECTION);

#endif