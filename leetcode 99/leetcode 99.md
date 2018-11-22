## Leetcode 99. Recover Binary Search Tree  

### 题目：

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

**Example 1:**

```
Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2
```

**Example 2:**

```
Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
```

### 解法：

在不改变源二叉树结构的情况下，我们可以将这个题可以分为三种情况讨论，以中序遍历得到的序列[1,2,3,4,5,6]为例：

- 当出现一对逆序对的时候，如2，3位置错误时候，我们得到的序列应该是`[1,3,2,4,5,6]`，这时我们只需要将2与3的位置交换，也即将唯一一对逆序对的两个元素进行交换，那么就可以完成任务
- 当出现两对逆序对的时候，如2，5位置错误时候，我们得到的序列应该是`[1,5,3,4,2,6]`，这时我们需要`将第一个逆序对[5,3]的第一个元素和第二个逆序对[2,6]的第二个元素置换`，完成操作后即可完成任务
- 当出现两对逆序对但是两个逆序对有共用元素的时候，如2，4位置错误，我们得到的序列应该是`[1,4,3,2,5,6]`，这时我们记录下来的结点只会有三个，那么就将第三个结点的值同第一个结点的值进行交换，完成操作后即可完成任务。

具体操作可以如下：

首先中序遍历，维护一个变量记录前一个访问的节点值，当出现第一次逆序时，我们把前一个访问节点和当前节点全部放入vector中，遍历结束我们对vector进行判断，有如下几种情况： 

1. 为空，没有逆序对，不做任何操作 
2. 不为空，判断容器大小： 
     - `vec.size()==2`，交换vec[0]与vec[1] 
     - `vec.size()==4`，交换vec[0]和vec[3]
     - `vec.size() ==3， `交换vec[0]与vec[2]
### 代码：

```cpp
class Solution {
private:
    void helper(TreeNode*root, TreeNode*&pre, vector<TreeNode*>&res)
    {
        if (root == NULL)
            return;
        helper(root->left, pre, res);
        if (pre != NULL&&pre->val > root->val)
        {
            res.push_back(pre);
            res.push_back(root);
        }
        pre = root;
        helper(root->right, pre, res);
    }

public:
    void recoverTree(TreeNode* root) {
        vector<TreeNode*>res;
        TreeNode*pre = NULL;
        helper(root, pre, res);
        if (res.size() > 0)
        {
            if(res.size()==2)
                swap(res[0]->val, res[1]->val);
            if(res.size()==3)
                swap(res[0]->val,res[2]->val);
            if(res.size()==4)
                swap(res[0]->val,res[3]->val);
        }
    }
};
```