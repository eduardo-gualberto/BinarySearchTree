#ifndef __UTILS__
#define __UTILS__

#include "../BinarySearchTree.h"

typedef struct BSTree Tree_t;

void __listR(Tree_t *, Tree_t **, int *);
Tree_t *__pushR(Tree_t *, void *, void *, size_t, int *);
Tree_t *__popR(Tree_t *, int *);
#endif