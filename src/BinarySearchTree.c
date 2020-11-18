#include "BinarySearchTree.h"

Tree_t *tree_init(void *key, void *value, Compare_f compare)
{
  Tree_t *newNode = (Tree_t *)malloc(sizeof(Tree_t));
  newNode->key = key;
  newNode->value = value;
  newNode->compare = compare;
  newNode->parent = newNode->right = newNode->left = NULL;
  return newNode;
}

//remover todos os nodes da arvore
void tree_destroy(Tree_t *bst)
{
  if (!bst)
    return;
  tree_destroy(bst->left);
  tree_destroy(bst->right);
  free(bst);
}

Tree_t *push(Tree_t *bst, void *key, void *value)
{
  if (!bst) //node folha
  {
    return tree_init(key, value, NULL);
  }
  else //caso geral
  {
    Tree_t *child;
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

Tree_t *search(Tree_t *bst, void *key)
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

Tree_t *max(Tree_t *bst)
{
  if (!bst)
    return NULL;

  return max(bst->right) ? bst->right : bst;
}

Tree_t **list(Tree_t *bst, int *n)
{
  int count = 0;
  int t_s = tree_size(bst);
  Tree_t **arr = malloc(sizeof(Tree_t *) * t_s);

  __listR(bst, arr, &count);
  if (n)
    *n = t_s;
  return arr;
}

Tree_t *pop(Tree_t *target)
{
  Tree_t *ret_val;
  if (target->right && target->left) //caso node tenha dois filhos
  {
    Tree_t *aux = max(target->left);
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
    Tree_t *child = target->right ? target->right : target->left;
    child->parent = target->parent;

    free(target);
    return child;
  }
  //caso node não tenha filho algum
  free(target);
  return NULL;
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
  int hright = tree_height(bst->right);
  int hleft = tree_height(bst->left);
  return 1 + (hright > hleft ? hright : hleft);
}