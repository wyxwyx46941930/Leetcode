### leetcode 134. Gas Station  

#### 题目：

There are *N* gas stations along a circular route, where the amount of gas at station *i* is `gas[i]`.

You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from station *i* to its next station (*i*+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.

**Note:**

- If there exists a solution, it is guaranteed to be unique.
- Both input arrays are non-empty and have the same length.
- Each element in the input arrays is a non-negative integer.

**Example 1:**

```
Input: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
```

**Example 2:**

```
Input: 
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
```

-----

#### 解法：

这个题意图在于，让我们找出从在一定条件下（`保证每一步上的当前 GAS 与剩余的 GAS 的总和大于到达下一个位置的 COST `）从哪一个节点上可以完成的对数组的遍历。

如果要完成遍历，那么我们还得保证`gas`的总和要大于等于 `cost`的总和，这样才能走完全程。

以`example 1为例`：设总剩余的 gas 为 total ，当前步骤上剩余的油量为 left 

- 从 gas[o] 出发，此时 left = 1 - 3 = - 2 < 0 ,此时显然不满足条件，那么我们就尝试从下一个结点开始走，此时total  = - 2 ;
- 从 gas[1] 出发，此时 left = 3 - 4 = - 1 < 0 ，此时显然不满足条件，那么我们就尝试从下一个结点开始走 ,此时total = - 3 ;
- 从 gas[2] 出发，此时 left = 3 - 5 = - 2 < 0 ,  此时显然不满足条件，那么我们就尝试从下一个结点开始走 ,此时total = - 5 ;
- 从 gas[3] 出发，此时 left = 4 - 1 = 3 > 0 , 此时满足条件，证明 gas[3] 可以作为一个出发点，此时 total = -2，**但是这里我们要保证从 gas[3] 出发一定能再回到 gas[3]** ,这时候就用到 `total `这个变量了，在下一步我们继续进行运算
- 从 gas[3] 到达 gas[4] 后，left = 5 - 2 = 3 > 0 , 且此时total = 3 + (-2) = 1 > 0 ,且此时数组已经到达结尾，这就证明我们是可以完成遍历的。

综上所述，我们得到的结论就是，从某个结点开始进行遍历，那么`这个结点往后走直到再回来的剩余油量一定要大于等于在这条路上某个结点到下一个结点的流量差值(负数)的和`

----

#### 代码：

````cpp
class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int total = 0, sum = 0, start = 0;
        for (int i = 0; i < gas.size(); ++i) {
            total += gas[i] - cost[i];
            sum += gas[i] - cost[i];
            if (sum < 0) {
                //更新起始结点
                start = i + 1;
                sum = 0;
            }
        }
        //判断能否走完
        if (total < 0) return -1;
        else return start;
    }
};
````