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
      child = __pushR(bst->left, key, value, hchange);
      child->compare = bst->compare;
      bst->left = child;
      if (*hchange)
      {
        if (bst->balance == +1)
        {
          bst->balance = 0;
          *hchange = 0;
        }
        else if (bst->balance == 0)
        {
          bst->balance = -1;
          *hchange = 1;
        }
        else if (bst->balance == -1)
        {
          if (bst->left->balance == -1)
          {
            bst = tree_rotate(bst, RIGHT);
            bst->right->balance = 0;
          }
          else
          {
            bst->left = tree_rotate(bst->left, LEFT);
            bst = tree_rotate(bst, RIGHT);
            if (bst->balance == 0)
            {
              bst->right->balance = bst->left->balance = 0;
            }
            else if (bst->balance == -1)
            {
              bst->left->balance = 0;
              bst->right->balance = +1;
            }
            else
            {
              bst->left->balance = -1;
              bst->right->balance = 0;
            }
          }
          bst->balance = 0;
          *hchange = 0;
        }
      }
    }
    else
    {
      child = __pushR(bst->right, key, value, hchange);
      child->compare = bst->compare;
      bst->right = child;
      if (*hchange)
      {
        if (bst->balance == -1)
        {
          bst->balance = 0;
          *hchange = 0;
        }
        else if (bst->balance == 0)
        {
          bst->balance = +1;
          *hchange = 1;
        }
        else if (bst->balance == +1)
        {
          if (bst->right->balance == +1)
          {
            bst = tree_rotate(bst, LEFT);
            bst->left->balance = 0;
          }
          else
          {
            bst->right = tree_rotate(bst->right, RIGHT);
            bst = tree_rotate(bst, LEFT);

            if (bst->balance == 0)
            {
              bst->right->balance = bst->left->balance = 0;
            }
            else if (bst->balance == +1)
            {
              bst->left->balance = 0;
              bst->right->balance = -1;
            }
            else
            {
              bst->left->balance = +1;
              bst->right->balance = 0;
            }
          }
          bst->balance = 0;
          *hchange = 0;
        }
      }
    }

    child->parent = bst;
    return bst;
  }
}

void setBalance(Tree_t *t)
{
  if (!t)
    return;
  t->balance = tree_height(t->right) - tree_height(t->left);
  printf("%d's balance = %d\n", *(int *)t->key, t->balance);
  setBalance(t->left);
  setBalance(t->right);
}