## leetcode 553.Optimal Division 

### 题目：

Given a list of **positive integers**, the adjacent integers will perform the float division. For example, [2,3,4] -> 2 / 3 / 4.

However, you can add any number of parenthesis at any position to change the priority of operations. You should find out how to add parenthesis to get the **maximum** result, and return the corresponding expression in string format. **Your expression should NOT contain redundant parenthesis.**

**Example:**

```
Input: [1000,100,10,2]
Output: "1000/(100/10/2)"
Explanation:
1000/(100/10/2) = 1000/((100/10)/2) = 200
However, the bold parenthesis in "1000/((100/10)/2)" are redundant, 
since they don't influence the operation priority. So you should return "1000/(100/10/2)". 

Other cases:
1000/(100/10)/2 = 50
1000/(100/(10/2)) = 50
1000/100/10/2 = 0.5
1000/100/(10/2) = 2
```

**Note:**

1. The length of the input array is [1, 10].
2. Elements in the given array will be in range [2, 1000].
3. There is only one optimal division for each test case.

----

### 解法：

这是一道数学类的问题，看起来很难其实思路很简单。

这个题的目的是`求给定的数字序列加入除号之后让所求的值最大`，那么要想除法的结果最大，要么除数最小，要么被除数最大，现在的情况是被除数不能变，那么我们只能让除数变得最小；若要让除数变得最小，就只能让被除数之外的数字按顺序除下去，所以解题的情况大致有三种：

- 若只给一个数字，那么这一个数字就是最终结果
- 若给两个数字，第一个数字当被除数，第二个数字当除数
- 若给三个数字，则第一个数字当被除数，第二个数字除以第三个数字当除数

依次类推，最终就可以得到最大的解；由于这个题我们不需要计算出准确的解，所以我们只需要给出具体的表达式形式就行，但是要注意`加上括号`

---

### 代码：

```cpp
class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        if (nums.empty()) return "";
        string res = to_string(nums[0]);
        if (nums.size() == 1) return res;
        if (nums.size() == 2) return res + "/" + to_string(nums[1]);
        res += "/(" + to_string(nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            res += "/" + to_string(nums[i]);
        }
        return res + ")";
    }
};
```