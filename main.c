#include <stdio.h>
#include "BinarySearchTree/BinarySearchTree.h"

int main()
{
  //key, value
  BSTree *bst = tree_init(4, 20);
  bst = push(bst, 2, 10);
  bst = push(bst, 1, 10);
  bst = push(bst, 7, 10);
  bst = push(bst, 5, 10);

  int n;
  BSTree **l = list(bst, &n);
  for (int i = 0; i < n; i++)
    printf("%d\t", l[i]->key);
  printf("\n");

  bst = pop(bst);

  l = list(bst, &n);

  for (int i = 0; i < n; i++)
    printf("%d\t", l[i]->key);
  printf("\n");
  return 0;
}