### leetcode  98.Validate Binary Search Tree 

#### 题目：

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

- The left subtree of a node contains only nodes with keys **less than** the node's key.
- The right subtree of a node contains only nodes with keys **greater than** the node's key.
- Both the left and right subtrees must also be binary search trees.

**Example 1:**

``` bash
Input:
    2
   / \
  1   3
Output: true
```

**Example 2:**

```bash
    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
             is 5 but its right child's value is 4.
```

#### 解法：

这个题让我们验证这课二叉树是否是一颗严格意义上的二叉搜索树，也即所有子树的右子节点的值一定大于根节点，左子结点小于根节点。

根据这个思路，我们就可以得出代码的求解了。

#### 代码：

```cpp

class Solution {
public:
    bool isValidBST(TreeNode * root) {
        return isValidBSTHelper(root, INT64_MIN, INT64_MAX);
    }
    
    bool isValidBSTHelper(TreeNode *root, long lower, long upper){
        if(root == NULL)    return true;
        if(root->val>=upper || root->val<=lower)    return false;
        return isValidBSTHelper(root->left,lower,root->val)&&isValidBSTHelper(root->right,root->val,upper);
    }
};
```