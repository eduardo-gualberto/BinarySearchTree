#include "./src/BinarySearchTree.h"

int compare(void *a, void *b)
{
  int va = *(int *)a, vb = *(int *)b;
  return va > vb ? 1 : va == vb ? 0 : -1;
}

int main()
{
  Compare_f c = &compare;
  int k[] = {80, 20, 90, 10, 100, 50, 15};
  int v0 = 'A';
  Tree_t *t = tree_init((void *)&k[0], (void *)&v0, c);
  for (int i = 1; i < 7; i++)
  {
    char v = 'A' + i;
    t = tree_push(t, (void *)(&k[i]), (void *)(&v));
    printf("inseriu %d\troot balance = %d\troot = %d\troot parent = %p\tmax = %d\n", k[i], t->balance, *(int *)t->key, t->parent, *(int *)tree_max(t)->key);
  }

  printf("Root before pop = %d\n", *(int *)t->key);
  t = tree_pop(t, (void *)&k[4]);
  printf("Root after pop = %d\n", *(int *)t->key);
  int n;
  Tree_t **l = tree_list(t, &n);

  printf("nodes:\n");
  for (int i = 0; i < n; i++)
    printf("%d  ", *(int *)l[i]->key);
  printf("\n");

  printf("parents:\n");
  for (int i = 0; i < n; i++)
    printf("%d  ", l[i]->parent ? *(int *)l[i]->parent->key : -1);
  printf("\n");

  printf("Root's balance in the end = %d\n", t->balance);

  return 0;
}