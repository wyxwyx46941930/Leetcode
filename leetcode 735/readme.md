## Leetcode 735

### 题目：

We are given an array `asteroids` of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

**Example 1:**

```
Input: 
asteroids = [5, 10, -5]
Output: [5, 10]
Explanation: 
The 10 and -5 collide resulting in 10.  The 5 and 10 never collide.
```

**Example 2:**

```
Input: 
asteroids = [8, -8]
Output: []
Explanation: 
The 8 and -8 collide exploding each other.
```

**Example 3:**

```
Input: 
asteroids = [10, 2, -5]
Output: [10]
Explanation: 
The 2 and -5 collide resulting in -5.  The 10 and -5 collide resulting in 10.
```

**Example 4:**

```
Input: 
asteroids = [-2, -1, 1, 2]
Output: [-2, -1, 1, 2]
Explanation: 
The -2 and -1 are moving left, while the 1 and 2 are moving right.
Asteroids moving the same direction never meet, so no asteroids will meet each other.
```

**Note:**

The length of `asteroids` will be at most `10000`.

Each asteroid will be a non-zero integer in the range `[-1000, 1000].`.

### 解法：

看了看测试样例，这个题可以看作是堆栈类问题：

具体的情况可以分为 2 种

- 若栈顶为空，直接把待入栈数数字push到栈中
- 若栈顶不为空，那么
  - 如果栈顶为负数，那么直接把当前待入栈数字push到栈中
  - 如果栈顶为正数，且待入栈元素为正数，那么直接把当前待入栈数字push到栈中
  - 如果栈顶为正数，且待入栈元素为负数
    - 若栈顶数字的绝对值大于当前待入栈负数的绝对值，那么继续读取下一个待入栈数字
    - 若栈顶数字的绝对值等于当前待入栈负数的绝对值，那么pop当前栈顶元素，继续读下一个待入栈数字
    - 若栈顶数字的绝对值小于当前待入栈数字的绝对值，那么pop当前栈顶元素，继续上述的一系列判断操作，直到满足栈为空或者栈顶元素为负数，那么向栈中push待入栈元素

---

注：

这个题最后是让你返回一个 vector 类型的数据，所以还需要把栈中的数据 pop 到 vector 中，并且完成一个vector的逆序交换。

### 代码：

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> result;
        if (asteroids.size() == 0)
            return asteroids;
        for (int i = 0; i < asteroids.size(); i++) {
            int flag = 0;
            if (result.empty()) {
                result.push(asteroids[i]);
                continue;
            }
            if (asteroids[i] > 0) {
                result.push(asteroids[i]);
            } else {
                if (result.top() < 0) {
                    result.push(asteroids[i]);
                } else {
                    while (!result.empty()&&result.top()>0) {
                        if (abs(asteroids[i])<result.top()) {
                            flag = 1;
                            break;
                        } else if (abs(asteroids[i]) == result.top()) {
                            result.pop();
                            flag = 1;
                            break;
                        } else {
                            result.pop();
                        }
                    }
                    if (flag == 0)
                        result.push(asteroids[i]);
                }
            }
        }
        vector<int> sum;
        while (!result.empty()) {
            sum.push_back(result.top());
            result.pop();
        }
        for (int i = 0; i < sum.size()/2; i++) {
            int temp  = sum[sum.size()-i-1];
            sum[sum.size()-i-1] = sum[i];
            sum[i] = temp;
        }
        return sum;
    }
};

```