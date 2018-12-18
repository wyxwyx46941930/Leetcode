### leetcode 179. Largest Number

#### 题目：

Given a list of non negative integers, arrange them such that they form the largest number.

**Example 1:**

```
Input: [10,2]
Output: "210"
```

**Example 2:**

```
Input: [3,30,34,5,9]
Output: "9534330"
```

**Note:** The result may be very large, so you need to return a string instead of an integer.

---

#### 解法：

这个题是一道排序的变形题，大概意思是让我们根据每个数字最后一位的大小排序，如果最后一位相同就比较前一位。

关于排序问题，我们可以使用`c++`标准库中的`sort`函数来直接解决，但是如何排序需要我们进行定义。

这里我们思考一个问题，如何比较两个简单字符串的大小，方法不外乎：

- 按照字典序
- 从右往左一位一位比较

这个题我们可以按照字典序进行处理，比如：`19` , `11`这两个数字，我们可以先把这两个数字转为字符串，然后用两种不同的顺序拼接起来，得到：

- str1 = "1911"
- str2 = "1119"

很显然，" 1911 " > " 1119 " ，那么我们就可以把 19 排在 11 前面。

所以根据这个思路我们可以写出我们的排序函数：

```cpp
sort(arr.begin(),arr.end(),cmp)//调用库函数，按照cmp函数的要求进行排序
bool cmp(string str1,string str2)
{
    string temp1 = str1 + str2 ;
    string temp2 = str2 + str1 ;
    return temp1 > temp2 ;
}
```

于此即可完成任务。

----

#### 代码：

```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        //使用匿名自定义函数
        sort(nums.begin(),nums.end(),[](int str1,int str2)
        {
            string temp1 = to_string(str1) + to_string(str2) ;
            string temp2 = to_string(str2) + to_string(str1);
            return temp1 > temp2 ;   
        });
        string test;
        for(int i = 0 ; i < nums.size() ; i ++ )
        {
            test += to_string(nums[i]) ;
        }
        //这里是为了处理全零的情况
        if(test[0] == '0')
        {
            return "0" ;
        }
        return test ;
    }
};
```



