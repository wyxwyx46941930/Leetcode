### Leetcode 90

#### 题目：

Given a collection of integers that might contain duplicates, **nums**, return all possible subsets (the power set).

**Note:** The solution set must not contain duplicate subsets.

**Example:**

```
Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
```

#### 解答：

从集合论我们可以知道，任何一个集合的子集的个数为 2^N，根据集合求出子集并不难，但是这个题目还有个要求就是`不能包含重复的子集`，所以我们需要处理一下重复的子集；

按照容器的性质，这里我们可以选用`map<vector<int>,bool>`,用来存放子集序列，也即每次放入新的序列之前，先搜索一遍`map`，如果找不到重复的，就放进去。

关于生成子集，我们可以考虑成 `0 1背包问题`，把第N个子集的N看成二进制数字，比如：

N = 4 = 100(二进制) = abc(a = 1 , b = 0 , c = 0)

那么所生成的序列应该是`{1 * 1,2 * 0,2 * 0} = { 1 }`

取数组里面的元素，可以直接使用arr[c]，然后N >> 1,再次取arr[c]，直到`N == 0` 

#### 代码：

```cpp
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > result;
        map<vector<int>, bool> m;
        int size = S.size();
        for(int i = 0; i < pow(2.0, size); i ++)
        {
            int tag = i;
            vector<int> cur;
            //生成可能的子集
            for(int j = size-1; j >= 0; j --)
            {
                if(!tag)
                    break;
                if(tag%2 == 1)
                {
                    cur.push_back(S[j]);
                }
                //数字往右边移位
                tag >>= 1;
            }
            sort(cur.begin(), cur.end());
            //查重
            if(m.find(cur) == m.end()) 
            {
                m[cur] = true;
                result.push_back(cur);
            }
        }
        return result;
    }
};
```

