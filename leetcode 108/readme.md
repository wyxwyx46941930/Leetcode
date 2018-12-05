### leetcode 108. Convert Sorted Array to Binary Search Tree 

### 题目:

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of *every*node never differ by more than 1.

**Example:**

```
Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```

----

#### 解法： 

这个题是让把排序好的数组存放在一颗平衡二叉搜索树中，所谓的平衡树也即：`任意一个结点的左右子树的高度不能相差超过 1 `,二叉搜索树我们老生常谈的概念了，那么构建这么一颗平衡二叉搜索树，我的思考大致如下：

- 找出数组的中间点，将中间点作为二叉树的根，这样就可以保证每次构建出来的二叉树一定是左右平衡的
- 采用递归的思想，每次将已经划分过的左右两部分再次从中点进行划分，并将此时的中点作为根结点，继续构造子树

基本的思路大致就是如此，需要注意几个小问题:

- 如果数组中只有一个数字，那么这个数字就是根，左右子树为空
- 如果数组中有两个数字，那么第一个数字为根，第二个数字为右子树

-----

#### 代码：

```cpp
class Solution {
public:
    TreeNode* _sortedArrayToBST(vector<int>& num, int start, int end){
        if(start==end)  //边界情况1
            return new TreeNode(num[start]);
        if(start>end) { //边界情况2
            return NULL;
        }
        int mid=start+(end-start)/2; 
        TreeNode* root=new TreeNode(num[mid]);
        root->left=_sortedArrayToBST(num, start,mid-1);
        root->right=_sortedArrayToBST(num,mid+1,end);
        return root;
    }
    
    TreeNode *sortedArrayToBST(vector<int> &num) {
        if(num.size()==0)
            return NULL;
        int mid=(0+(int)num.size()-1)/2;
        TreeNode* root=new TreeNode(num[mid]);
        root->left=_sortedArrayToBST(num, 0, mid-1);
        root->right=_sortedArrayToBST(num, mid+1, (int)num.size()-1);
        return root;
    }
};
```