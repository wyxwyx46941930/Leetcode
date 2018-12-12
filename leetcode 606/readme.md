### leetcode 606. Construct String from Binary Tree 

#### 题目：

You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

**Example 1:**

```bash
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())",  but you need to omit all the unnecessary empty parenthesis pairs. And it will be "1(2(4))(3)".
```

**Example 2:**

```bash
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example, except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.
```

-----

#### 解法：

这个题就是一个`先根遍历`的问题，但是我们在输出时候需要注意一个问题，就是我们应该怎么处理返回时候的字符串；

这里从例子中我们可以看出：

- 当左结点为空，右结点不为空时候，需要返回的是  () + 右结点
- 当右结点为空，左结点不为空时候，需要返回的是 左结点
- 当左右结点均为空的时候，返回空字符串

所以只需要注意上面三个方面，我们就可以完成任务了。

-----

#### 代码：

```cpp
class Solution {
public:
    string tree2str(TreeNode* t) {
        if (!t) return "";
        string res = to_string(t->val);
        string left = tree2str(t->left), right = tree2str(t->right);
        if (left == "" && right == "") return res;
        //如果左结点为空  则返回res+()+右结点
        if (left == "") return res + "()" + "(" + right + ")";
        //如果右结点为空则返回res +（左结点）
        if (right == "") return res + "(" + left + ")";
        return res + "(" + left + ")" + "(" + right + ")";
    }
};
```

