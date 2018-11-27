## Leetcode 250.

### 题目：

Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

For example:
Given binary tree,

              5
             / \
            1   5
           / \   \
          5   5   5
return 4

### 解法：

这个题比较直接，就是通过**递归找出左右子树的节点值和父节点值均相同的子树个数**，比如结点1的两个子树的值都是5，则证明满足情况；同时叶子结点也是满足情况的，因为叶子结点不含有子树，所以左右子树节点值都为 0 

### 代码：

```cpp
class Solution {
public:
    bool DFS(TreeNode* root, int pre, int& ans)
    {
        if(!root) return true;
        bool flag1 = DFS(root->left, root->val, ans);
        bool flag2 = DFS(root->right, root->val, ans);
        if(flag1 && flag2) ans++;
        return (root->val == pre) && flag1 && flag2;
    }
    
    int countUnivalSubtrees(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        DFS(root, root->val, ans);
        return ans;
    }
};
```