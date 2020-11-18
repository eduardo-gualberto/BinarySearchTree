#include "Utils.h"

void __listR(BSTree *bst, BSTree **arr, int *count)
{
  if (!bst)
    return;

  __listR(bst->left, arr, count);

  arr[(*count)++] = bst;

  __listR(bst->right, arr, count);
}