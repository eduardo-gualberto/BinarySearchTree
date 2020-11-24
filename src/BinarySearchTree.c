#include "BinarySearchTree.h"

Tree_t *tree_init(void *key, void *value, size_t ks, Compare_f compare)
{
  Tree_t *newNode = (Tree_t *)malloc(sizeof(Tree_t));

  newNode->keysize = ks;
  newNode->key = malloc(newNode->keysize);
  memcpy(newNode->key, key, newNode->keysize);

  newNode->value = value;
  newNode->compare = compare;
  newNode->parent = newNode->right = newNode->left = NULL;
  newNode->balance = 0;
  return newNode;
}

//remover todos os nodes da arvore
void tree_destroy(Tree_t *bst)
{
  if (!bst)
    return;
  tree_destroy(bst->left);
  tree_destroy(bst->right);

  free(bst->key);
  free(bst->value);
  free(bst);
}

Tree_t *tree_push(Tree_t *bst, void *key, void *value)
{
  int hchange;
  Tree_t *ret = __pushR(bst, key, value, bst->keysize, &hchange);
  ret->parent = NULL;
  return ret;
}

Tree_t *tree_search(Tree_t *bst, void *key)
{
  if (!bst)
    return NULL;

  int comp = bst->compare(bst->key, key);

  if (comp == 0)
    return bst;
  if (comp == 1)
    return tree_search(bst->left, key);
  else
    return tree_search(bst->right, key);
}

Tree_t *tree_max(Tree_t *bst)
{
  Tree_t *aux = bst;
  while (aux->right)
    aux = aux->right;
  return aux;
}

Tree_t **tree_list(Tree_t *bst, int *n)
{
  int count = 0;
  int t_s = tree_size(bst);
  Tree_t **arr = malloc(sizeof(Tree_t *) * t_s);

  __listR(bst, arr, &count);
  if (n)
    *n = t_s;
  return arr;
}

Tree_t *tree_pop(Tree_t *t, void *key)
{
  if (!t)
    return t;
  int comp = t->compare(t->key, key);
  if (comp == 1)
    t->left = tree_pop(t->left, key);
  else if (comp == -1)
    t->right = tree_pop(t->right, key);
  else
  {
    if (t->right && t->left) //caso node tenha dois filhos
    {
      Tree_t *aux = tree_max(t->left);
      t->key = aux->key;
      t->value = aux->value;

      t->left = tree_pop(t->left, aux->key);
    }
    else if (t->right || t->left) //caso node tenha um filho
    {
      Tree_t *child = t->right ? t->right : t->left;
      child->parent = t->parent;

      *t = *child;
      free(child);
    }
    else //caso node não tenha filho algum
    {
      Tree_t *aux = t;
      t = NULL;
      free(aux);
    }
  }
  if (!t)
    return t;

  int t_balance = tree_height(t->right) - tree_height(t->left),
      l_balance = t->left ? tree_height(t->left->right) - tree_height(t->left->left) : 0,
      r_balance = t->right ? tree_height(t->right->right) - tree_height(t->right->left) : 0;

  if (t_balance < -1 && l_balance < 0) // left left
  {
    t = tree_rotate(t, RIGHT);
  }
  else if (t_balance < -1 && l_balance >= 0) // left right
  {
    t->left = tree_rotate(t->left, LEFT);
    t = tree_rotate(t, RIGHT);
  }
  else if (t_balance > +1 && r_balance >= 0) // right right
    t = tree_rotate(t, LEFT);
  else if (t_balance > +1 && r_balance < 0) // right left
  {
    t->right = tree_rotate(t->right, RIGHT);
    t = tree_rotate(t, LEFT);
  }

  setBalance(t);

  return t;
}

int tree_size(Tree_t *bst)
{
  if (!bst)
    return 0;
  return 1 + tree_size(bst->left) + tree_size(bst->right);
}

int tree_height(Tree_t *bst)
{
  if (!bst)
    return -1;

  int left = tree_height(bst->left);
  int right = tree_height(bst->right);

  return 1 + (left > right ? left : right);
}

Tree_t *tree_rotate(Tree_t *t, enum DIRECTION dir)
{
  Tree_t *aux;
  if (dir == RIGHT)
  {
    if (!t->left)
      return t;
    aux = t->left;
    t->left = aux->right;
    if (aux->right)
      aux->right->parent = t;
    aux->right = t;
  }
  else if (dir == LEFT)
  {
    if (!t->right)
      return t;
    aux = t->right;
    t->right = aux->left;
    if (aux->left)
      aux->left->parent = t;
    aux->left = t;
  }
  aux->parent = t->parent;
  t->parent = aux;
  return aux;
}
