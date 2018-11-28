## Leetcode 84.Largest Rectangle in Histogram 

### 题目：

Given *n* non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

 

![img](https://assets.leetcode.com/uploads/2018/10/12/histogram.png)  

Above is a histogram where width of each bar is 1, given height = `[2,1,5,6,2,3]`.

 

![img](https://assets.leetcode.com/uploads/2018/10/12/histogram_area.png)  

The largest rectangle is shown in the shaded area, which has area = `10` unit.

 

**Example:**

```
Input: [2,1,5,6,2,3]
Output: 10
```

----

### 解法：

这个题思考了比较久的时间，但是始终得不到太好的解题过程，然后就去论坛上看了看dalao们的解法，其中有一种比较好理解且效率比较高的方法，我看懂了之后在这里介绍一下：

我们可以使用**栈**存储长方形的坐标，比如：

input = [2,1,5,6,2,3]

坐标 position = [0,1,2,3,4,5]

这样我们就可以给每一个输入设定一个坐标。

题目中给的要求是找出最大的矩形面积，我们就需要做的就是：从第一个矩形开始往后遍历，但是这个过程中我们会遇到很多种组合形的面积，比如图中的阴影部分，那么我们就需要判断一下：`当前的组合面积与已有记录的最大面积的大小以及是否可以进一步扩充组合面积`。

具体用栈实现的话，步骤大概如下：

- 如果当前`stack`为空，或者`input[i]`大于等于栈顶坐标对应高度，则将i加入stack中；
-  如果`input[i]`小于栈顶坐标对应高度，说明可以开始处理栈内的坐标形成的局部递增高度，以求得当前最大矩形面积。弹出当前栈顶坐标 = top，此时栈顶新坐标 = top'，那么对应计算面积的宽度`w = i - 1 - top'`（若弹出栈顶坐标后，stack为空，则对应w = i），得到面积` s = input[top] * w`，此时将i减一（因为进入循环i会加一，而待会儿需要重复考察第i个高度）；
- 遍历完成i∈[0→n]，返回最大矩形面积。

### 代码：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
		// Exceptional Case: 
		if(n == 0){
			return 0;
		}
		if(n == 1){
			return heights[0];
		}
		// insert 0 height
		heights.push_back(0);
		stack<int> st;
		int ans = 0;
		for(int i = 0; i <= n; i++){
			if(st.empty() || heights[i] >= heights[st.top()]){
				st.push(i);
			}
			else{
				int top = st.top();
				st.pop();
				int w = st.empty()? i: i - 1 - st.top();
				ans = max(ans, heights[top] * w);
				i--;
			}
		}
		return ans;
    }
};

```
