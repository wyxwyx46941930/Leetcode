### leetcode 109. Convert Sorted List to Binary Search Tree 

#### 题目:

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of *every*node never differ by more than 1.

**Example:**

```
Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```

----

#### 解法：

这个题跟 [108](https://blog.csdn.net/wyxwyx469410930/article/details/84824892) 基本是一样的题，思路完全相同，不过这个题我先将链表放置在 `vector` 中,用空间来换取时间复杂度 

---

#### 代码：

````cpp
class Solution {
public:
    TreeNode* _sortedArrayToBST(vector<int>& num, int start, int end){
        if(start==end)
            return new TreeNode(num[start]);
        if(start>end) {
            return NULL;
        }
        int mid=start+(end-start)/2; //避免溢出
        TreeNode* root=new TreeNode(num[mid]);
        root->left=_sortedArrayToBST(num, start,mid-1);
        root->right=_sortedArrayToBST(num,mid+1,end);
        return root;
    }
    TreeNode *sortedListToBST(ListNode *head) {
        ListNode* node=head;
        vector<int> vec;
        while(node!=NULL){
            vec.push_back(node->val);
            node=node->next;
        }
        return _sortedArrayToBST(vec,0,(int)vec.size()-1);
    }
};

````