#include <stdio.h>
#include "BinarySearchTree/BinarySearchTree.h"

#define N 5

int compare_function(void *k1, void *k2)
{
  int K1 = *(int *)k1;
  int K2 = *(int *)k2;
  return K1 > K2 ? 1 : K1 == K2 ? 0 : -1;
}

int main()
{
  //assigning what the keys and values will be
  int k[N] = {4, 6, 5, 12, 3};
  char v[N] = {'a', 'c', 'z', 'p', 'e'};

  //creating the tree
  Compare_f c = &compare_function;
  Tree_t *bst = tree_init((void *)&k[0], (void *)&v[0], c);

  //pushing some stuff to the tree
  for (int i = 1; i < N; i++)
    bst = push(bst, (void *)&k[i], (void *)&v[i]);

  //remove the root of the tree
  bst = pop(bst);

  //list in ascending order the tree nodes
  int n;
  BSTree **l = list(bst, &n);

  //print the list and test tree's height and node number
  for (int i = 0; i < n; i++)
    printf("%d\t", *(int *)l[i]->key);
  printf("\ntree_size = %d, tree_height = %d\n", n, tree_height(bst));

  //free the tree's heap allocated space
  tree_destroy(bst);
  return 0;
}