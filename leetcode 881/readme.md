### leetcode 881. Boats to Save People 

#### 题目：

The `i`-th person has weight `people[i]`, and each boat can carry a maximum weight of `limit`.

Each boat carries at most 2 people at the same time, provided the sum of the weight of those people is at most `limit`.

Return the minimum number of boats to carry every given person.  (It is guaranteed each person can be carried by a boat.)

 

**Example 1:**

```bash
Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)
```

**Example 2:**

```bash
Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)
```

**Example 3:**

```bash
Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)
```

**Note**:

- `1 <= people.length <= 50000`
- `1 <= people[i] <= limit <= 30000`

----

#### 解法：

暴力遍历法，从头开始往后遍历，累加法求结果，可以求解，但是这个题会超时；

```cpp
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(),people.end());
        int total = 0 ; 
        int temp = 0 ; 
        int times ++ ;
        for(int i = 0 ; i < people.size() ; i ++)
        {
            if(temp + people[i] < limit && times != 2 )
            {
                times ++ ;
                temp += people[i] ;
                continue ;
            }
            else
            {
                times = 0 ;
                total ++ ;
                temp = 0 ;
                i -- ;
            }
        }
        return total ;
    }
};
```

![2](https://img-blog.csdnimg.cn/20181223160828405.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3d5eHd5eDQ2OTQxMDkzMA==,size_16,color_FFFFFF,t_70)

所以选择换一种方法做；

我们可以这么思考，先对`people`进行排序，然后我们就可以得到一个升序的`people`序列，随后`我们每次都将体重最轻跟体重最重的人求和，来判断是否船是否可以成功承受`：

- 如果可以承载，那么证明我们可以用这艘船一次拉走两个人，也就同时将需要拉走的人数从头往后推 1 从尾部往前推 1  
- 如果不可以承载，那么我们只能用这艘船将最重的人拉走，最轻的人还留在当地，同时将需要拉走的人从尾往前推 1 

这样就可以避免超时的问题。

-----

#### 代码：

```cpp
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(),people.end());
        int first = 0 ;
        int end = people.size() - 1;
        int total = 0 ;
        while(first <= end)
        {
            total ++ ;
            if(people[first]+people[end] <= limit)
            {
                first ++ ;
            }
            end -- ;
        }
        return total ;
    }
};
```

