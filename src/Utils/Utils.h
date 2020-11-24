#ifndef __UTILS__
#define __UTILS__

#include "../BinarySearchTree.h"

typedef struct BSTree Tree_t;

void __listR(Tree_t *, Tree_t **, int *);
Tree_t *__pushR(Tree_t *bst, void *key, void *value, size_t ks, int *hchange);
void setBalance(Tree_t *);
#endif
