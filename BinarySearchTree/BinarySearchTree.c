#include "BinarySearchTree.h"

BSTree *tree_init(void *key, void *value, Compare compare)
{
  BSTree *newNode = (BSTree *)malloc(sizeof(BSTree));
  newNode->key = key;
  newNode->value = value;
  newNode->compare = compare;
  newNode->parent = newNode->right = newNode->left = NULL;
  return newNode;
}

//remover todos os nodes da arvore
void tree_destroy(BSTree *bst)
{
}

BSTree *push(BSTree *bst, void *key, void *value)
{
  if (!bst) //node folha
  {
    return tree_init(key, value, NULL);
  }
  else //caso geral
  {
    BSTree *child;
    if (bst->compare(bst->key, key) == 1)
    {
      child = push(bst->left, key, value);
      child->compare = bst->compare;
      bst->left = child;
    }
    else
    {
      child = push(bst->right, key, value);
      child->compare = bst->compare;
      bst->right = child;
    }
    child->parent = bst;
    return bst;
  }
}

BSTree *search(BSTree *bst, void *key)
{
  if (!bst)
    return NULL;

  int comp = bst->compare(bst->key, key);

  if (comp == 0)
    return bst;
  if (comp == 1)
    return search(bst->left, key);
  else
    return search(bst->right, key);
}

BSTree *max(BSTree *bst)
{
  if (!bst)
    return NULL;

  return max(bst->right) ? bst->right : bst;
}

BSTree **list(BSTree *bst, int *n)
{
  int count = 0;
  int t_s = tree_size(bst);
  BSTree **arr = malloc(sizeof(BSTree *) * t_s);

  __listR(bst, arr, &count);
  if (n)
    *n = t_s;
  return arr;
}

BSTree *pop(BSTree *target)
{
  BSTree *ret_val;
  if (target->right && target->left) //caso node tenha dois filhos
  {
    BSTree *aux = max(target->left);
    target->key = aux->key;
    target->value = aux->value;
    if (aux->parent == target)
      aux->parent->left = pop(aux);
    else
      aux->parent->right = pop(aux);
    return target;
  }
  else if (target->right || target->left) //caso node tenha um filho
  {
    BSTree *child = target->right ? target->right : target->left;
    child->parent = target->parent;

    free(target);
    return child;
  }
  //caso node não tenha filho algum
  free(target);
  return NULL;
}

int tree_size(BSTree *bst)
{
  if (!bst)
    return 0;
  return 1 + tree_size(bst->left) + tree_size(bst->right);
}

int tree_height(BSTree *bst)
{
  if (!bst)
    return -1;
  int hright = tree_height(bst->right);
  int hleft = tree_height(bst->left);
  return 1 + (hright > hleft ? hright : hleft);
}