### leetcode 145. Binary Tree Postorder Traversal  

#### 题目：

Given a binary tree, return the *postorder* traversal of its nodes' values.

**Example:**

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
```

**Follow up:** Recursive solution is trivial, could you do it iteratively?

-----

#### 解法：

这个题就是让我们实现二叉树的后序遍历，可以用递归的方式也可以用非递归的方式，由于非递归只有几行代码，比较简单，这里主要是需要了解一下非递归的方式。

非递归的后序遍历主要是用到了数据结构`栈`来存储最下层的结点，通过每一次一个一个结点的弹出，从最下层来访问对应的元素。

-----

#### 代码：

```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        stack<TreeNode*> s{{root}};
        TreeNode *head = root;
        while (!s.empty()) {
            TreeNode *t = s.top();
            if ((!t->left && !t->right) || t->left == head || t->right == head) {
                res.push_back(t->val);
                s.pop();
                head = t;
            } else {
                if (t->right) s.push(t->right);
                if (t->left) s.push(t->left);
            }
        }
        return res;
    }
};
```

