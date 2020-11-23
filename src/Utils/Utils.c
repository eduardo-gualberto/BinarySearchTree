#include "Utils.h"

void __listR(Tree_t *bst, Tree_t **arr, int *count)
{
  if (!bst)
    return;

  __listR(bst->left, arr, count);

  arr[(*count)++] = bst;

  __listR(bst->right, arr, count);
}

Tree_t *__pushR(Tree_t *bst, void *key, void *value, size_t ks, int *hchange)
{
  if (!bst) //node folha
  {
    *hchange = 1;
    return tree_init(key, value, ks, NULL);
  }
  else //caso geral
  {
    Tree_t *child;
    if (bst->compare(bst->key, key) == 1)
    {
      child = __pushR(bst->left, key, value, ks, hchange);
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
            bst = rotate(bst, RIGHT);
            bst->right->balance = 0;
          }
          else
          {
            bst->left = rotate(bst->left, LEFT);
            bst = rotate(bst, RIGHT);
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
      child = __pushR(bst->right, key, value, ks, hchange);
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
            bst = rotate(bst, LEFT);
            bst->left->balance = 0;
          }
          else
          {
            bst->right = rotate(bst->right, RIGHT);
            bst = rotate(bst, LEFT);

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

Tree_t *__popR(Tree_t *target, int *hchange)
{
  if (target->right && target->left) //caso node tenha dois filhos
  {
    Tree_t *aux = max(target->left);
    int side;
    target->key = aux->key;
    target->value = aux->value;
    if (aux->parent == target)
    {
      side = LEFT;
      aux->parent->left = __popR(aux, hchange);
    }
    else
    {
      side = RIGHT;
      aux->parent->right = __popR(aux, hchange);
    }

    if (*hchange)
    {
      if (target->balance == 0)
      {
        *hchange = 1;
        if (side == LEFT)
          target->balance = +1;
        else
          target->balance = -1;
      }
      else if ((target->balance == -1 && side == LEFT) || (target->balance == +1 && side == RIGHT))
      {
        *hchange = 1;
        target->balance = 0;
      }
      else
      {
        if (side == LEFT)
        {
          if (target->right->balance == 0)
          {
            target = rotate(target, LEFT);
            *hchange = 0;
            target->balance = -1;
            target->left->balance = +1;
          }
          else if (target->right->balance == +1)
          {
            target = rotate(target, LEFT);
            *hchange = 1;
            target->balance = 0;
            target->left->balance = 0;
          }
          else
          {
            target->right = rotate(target->right, RIGHT);
            target = rotate(target, LEFT);
            *hchange = 1;
            if (target->balance == -1)
            {
              target->left->balance = 0;   //x
              target->right->balance = +1; //y
            }
            else if (target->balance == +1)
            {
              target->left->balance = -1; //x
              target->right->balance = 0; //y
            }
            target->balance = 0;
            *hchange = 1;
          }
        }
        else if (side == RIGHT)
        {
          if (target->left->balance == 0)
          {
            target = rotate(target, RIGHT);
            *hchange = 0;
            target->balance = -1;
            target->left->balance = +1;
          }
          else if (target->right->balance == -1)
          {
            target = rotate(target, RIGHT);
            *hchange = 1;
            target->balance = 0;
            target->left->balance = 0;
          }
          else
          {
            target->left = rotate(target->left, LEFT);
            target = rotate(target, RIGHT);
            *hchange = 1;
            if (target->balance == -1)
            {
              target->left->balance = 0;   //y
              target->right->balance = +1; //x
            }
            else if (target->balance == +1)
            {
              target->left->balance = -1; //y
              target->right->balance = 0; //x
            }
            target->balance = 0;
            *hchange = 1;
          }
        }
      }
    }
    return target;
  }
  else if (target->right || target->left) //caso node tenha um filho
  {
    Tree_t *child;
    if (target->right)
      child = target->right;
    else
      child = target->left;
    child->parent = target->parent;
    *hchange = 1;
    free(target);
    return child;
  }
  //caso node não tenha filho algum
  free(target);
  *hchange = 1;
  return NULL;
}