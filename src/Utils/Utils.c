#include "Utils.h"

void __listR(Tree_t *bst, Tree_t **arr, int *count)
{
  if (!bst)
    return;

  __listR(bst->left, arr, count);

  arr[(*count)++] = bst;

  __listR(bst->right, arr, count);
}

Tree_t *__pushR(Tree_t *bst, void *key, void *value, int *hchange)
{
  if (!bst) //node folha
  {
    *hchange = 1;
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

    int rheight = bst->right ? bst->right->height : 0;
    int lheight = bst->left ? bst->left->height : 0;

    bst->height = (rheight > lheight ? rheight : lheight) + 1;

    bst->balance = rheight - lheight;

    child->parent = bst;
    return bst;
  }
}