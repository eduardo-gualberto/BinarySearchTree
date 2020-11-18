#include <stdio.h>
#include "BinarySearchTree/BinarySearchTree.h"

int compare_function(void *k1, void *k2)
{
  int K1 = *(int *)k1;
  int K2 = *(int *)k2;
  return K1 > K2 ? 1 : K1 == K2 ? 0 : -1;
}

int main()
{
  //key, value, key size and value size
  int k1, v1, k2, v2;
  k1 = 4;
  v1 = 10;
  BSTree *bst = tree_init((void *)&k1, (void *)&v1, &compare_function);
  k2 = 20;
  v2 = 30;
  bst = push(bst, (void *)&k2, (void *)&v2);

  int n;
  BSTree **l = list(bst, &n);
  for (int i = 0; i < n; i++)
    printf("%d\t", *(int *)l[i]->key);
  printf("\n");
  return 0;
}