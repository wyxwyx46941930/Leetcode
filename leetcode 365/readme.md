### leetcode 365. Water and Jug Problem 

#### 题目：

You are given two jugs with capacities *x* and *y* litres. There is an infinite amount of water supply available. You need to determine whether it is possible to measure exactly *z* litres using these two jugs.

If *z* liters of water is measurable, you must have *z* liters of water contained within **one or both buckets** by the end.

Operations allowed:

- Fill any of the jugs completely with water.
- Empty any of the jugs.
- Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.

**Example 1:** (From the famous [*"Die Hard"* example](https://www.youtube.com/watch?v=BVtQNK_ZUJg))

```bash
Input: x = 3, y = 5, z = 4
Output: True
```

**Example 2:**

```bash
Input: x = 2, y = 6, z = 5
Output: False
```

------

#### 解法：

拿到这个题，我最开始的想法是直接找出可以测量出水量的解法，比如：

- `z = x + y || z = x || z = y` 
- 且必须满足 `z <= x + y`

但是后来发现，当 x，y各放一半且能把 z 全部放出的时候，也是满足题意的，这就有点让人不懂了。

后来搜了一下解题大神的解法，思路大致如下：

设 `z = ax + by` ，设 `u = gcd(x,y)` ，也即求出x，y的最大公约数 u ，所以`x = nu ，y = mu `，随后原式 `z = anu + bmu` = `(an+bm)u`；

所以这个题我们就可以看作是求 z 可否由 x，y的最大公约数的倍数表示，也即 `(z % gcd(x,y) == 0)` 是否成立 

----

#### 代码：

```cpp
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        return z == 0 || (x + y >= z && z % gcd(x, y) == 0);
    }
    int gcd(int x, int y) {
        return y == 0 ? x : gcd(y, x % y);
    }
};

```



