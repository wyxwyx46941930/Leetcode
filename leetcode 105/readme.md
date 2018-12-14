### leetcode 105. Construct Binary Tree from Preorder and Inorder Traversal 

#### 题目：

Given preorder and inorder traversal of a tree, construct the binary tree.

**Note:**
You may assume that duplicates do not exist in the tree.

For example, given

```bash
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
```

Return the following binary tree:

```bash
    3
   / \
  9  20
    /  \
   15   7
```

-----

#### 解法：

这个题是大二时候学数据结构在sicily遇到的一道题。

由一颗二叉树的先根遍历和中根遍历是可以还原一颗二叉树的，思路具体如下：

思想如下：

- 根据前序遍历结果，第一个元素为二叉树的根结点；
- 观察中序遍历结果，根结点左侧的为左子树，若左子树根结点前（后）再无任何元素，则左（右）子树的左分支为空；根结点右侧的为右子树，若右子树根结点前（后）再无任何元素，则左（右）子树的左分支为空；
- 上面的过程是递归的。先找到当前树的根结点，然后划分为左右子树，再进入左子树重复上面的过程，最后进入右子树重复上面的过程，最终还原一棵树。

所以这个题，我们根据这个思路就可以完成一颗二叉树的还原，每次都在先根遍历序列中找到根节点，然后再中根遍历序列中进行递归序列划分。

-----

#### 代码：

```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
    TreeNode *buildTree(vector<int> &preorder, int pLeft, int pRight, vector<int> &inorder, int iLeft, int iRight) {
        if (pLeft > pRight || iLeft > iRight) return NULL;
        int i = 0;
        for (i = iLeft; i <= iRight; ++i) {
            if (preorder[pLeft] == inorder[i]) break;
        }
        TreeNode *cur = new TreeNode(preorder[pLeft]);
        cur->left = buildTree(preorder, pLeft + 1, pLeft + i - iLeft, inorder, iLeft, i - 1);
        cur->right = buildTree(preorder, pLeft + i - iLeft + 1, pRight, inorder, i + 1, iRight);
        return cur;
    }
};

```



