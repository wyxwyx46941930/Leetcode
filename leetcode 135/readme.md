## Leetcode 135.Candy

### 题目：

There are *N* children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

- Each child must have at least one candy.
- Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give?

**Example 1:**

```
Input: [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
```

**Example 2:**

```
Input: [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
             The third child gets 1 candy because it satisfies the above two conditions.
```

----

### 解法：

这个题的意思大概是在给定优先级的孩子序列里，求出需要分发出去的糖的最小数目，且优先级的孩子要比相邻优先级小的孩子获得的糖多，举个例子：

例如：现在孩子的优先级为{1,2,3,4,2,1}

`注：由于要让总糖数最小且每个孩子必须要有一颗糖，所以我们可以初始化将每一个孩子需要的糖数都设为 1，且优先级大的每次递增 1  `

从第一个孩子开始：

- 第 1 个孩子优先级为 1 ，需要的糖数为 1 
- 第 2 个孩子优先级为 2 ，其优先级大于第 1 个孩子，所以需要的糖数为 1 + 1 = 2
- 第 3 个孩子优先级为 3 ，其优先级大于第 2 个孩子，所以需要的糖数也为 2 +1 = 3
- 第 4 个孩子优先级为 4 ，其优先级大于第 3 个孩子，所以需要的糖数为 3 + 1 = 4

下面问题就出现了：

如果我们按照刚才的算法继续从左往右算的话，那么第 5 个孩子跟第 6 个孩子得到的糖数都会为 1 ，但是这是不对的，因为第 5 个孩子的优先级要大于第 6 个孩子，所以我们需要

`当从左往右扫描完毕之后，再从右往左进行一次上面的操作，也即如果后一个孩子比前一个孩子优先级低，那么前一个孩子在后一个孩子的糖数上加一`

那么从后往前算：

- 第 6 个孩子优先级为 1 ，需要的糖数为 1
- 第 5 个孩子优先级为 2 ，其优先级大于第 6 个孩子，所以需要的糖数为 1 + 1 = 2
- 第 4 个孩子优先级为 4 ，其优先级大于第 5 个孩子，所以需要的糖数为 2 + 1 = 3

这里就又出现矛盾了，我们第一次遍历从左往右算的时候，第四个孩子已经分到了 4 颗糖果，现在从右往左算的时候，反而第四个孩子的糖果数目变少了，这是不对的，所以我们在进行完从左往右搜索遍历之后进行从右往左遍历时候，`需要递增candy[y-1]的时候`，可以判断一下 `candy[y] +1 与 candy[y-1]`的大小，选用其中比较大的一个数字。

----

### 代码：

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int a[ratings.size()] = {0} ;
        //初始化candy序列
        for(int i = 0 ; i < ratings.size() ; i ++ )
        {
            a[i] = 1 ;
        }
        //从左往右搜
        for(int i = 0 ; i < ratings.size() -1 ; i ++)
        {
            if(ratings[i]<ratings[i+1])
            {
                a[i+1] = a[i] + 1 ;
            }
        }
        //从右往左搜
        for(int i = ratings.size()-1 ; i >=1 ; i -- )
        {
            if(ratings[i-1] > ratings[i] )
            {
                a[i-1] = max( a[i-1] , a[i] + 1 ) ;
            }
        }
        int total = 0 ;
        for(int i = 0 ; i < ratings.size() ; i ++ )
        {
            total = total + a[i] ;
        }
        return total ;
    }
};
```

 