## Leetcode 6. ZigZag Conversion 

### 题目：

The string `"PAYPALISHIRING"` is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

```
P   A   H   N
A P L S I I G
Y   I   R
```

And then read line by line: `"PAHNAPLSIIGYIR"`

Write the code that will take a string and make this conversion given a number of rows:

```
string convert(string s, int numRows);
```

**Example 1:**

```
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
```

**Example 2:**

```
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
```

### 解法：

刚开始拿到这个题是一头雾水，完全不知道如何下手，看测试样例也是十分的懵逼，后来搜索题解发现这是一道找规律的题，<u>大概意思就是把你输入的字符串按照`写倒立的大写N的顺序`再排列一遍，随后按行输出。</u>

这个题有很多种方法，我个人的思路是这样的，以 N = 4 为例，图中的数字代表字母的下标：![tmp](https://github.com/wyxwyx46941930/Leetcode/blob/master/leetcode%206/tmp.png)

- step 1 ：分块

我们可以把每个往下再往右上走的序列看做一个块，我们可以发现每个块填满时候的字符的个数是 2N - 2 个 ，图中为 6 个

- step 2 ：分组

我们可以把每一块内的字符分为两组，一组是下降的序列，一组是上升的序列，根据这两组不同的性质，找寻不同的规律

- step 3： 找规律(注：index代表字符在字符串中的位置)
  - 下降序列部分：这部分的规律：横坐标递增，纵坐标不变，所以根据这个规律，我们可以得到如下推导式：

    > x =  index % (2 * rowNumber - 2)
    >
    > y =  index / (2 * rowNumber - 2) + i * (rowNumber - 2)

  - 上升序列部分：这部分的规律：横纵坐标都变，且横坐标每次减一，纵坐标每次加一，我们可以得到如下推导式：

    > x = rowNumber - 1 - index % (rowNumber - 1)
    >
    > y = index % (rowNumber - 1) + i * (Number - 1) 

- step 4 ：动态申请二维数组完成赋值

```cpp
//这里的数组尽量要大，要容下所有的字符序列
int number = numRows ; 
int N = s.size() / ( 2 * number - 2) + 1 ;
int row = number ;
char** array = new char*[row];
int colomn = (number - 1) * N ; 

for(int i= 0 ; i < row ; ++ i) {
	array[i] = new char[colomn];
}
for(int  i = 0 ; i < row ; i ++ )
{
	for(int j = 0 ; j < colomn ; j ++ )
	{
		array[i][j] = ' ' ;
	}
}	
```

- step 5 ：按行输出序列释放数组空间

### 代码：

````cpp
class Solution {
public:
    string convert(string s, int numRows) {
    if(numRows == 1)
    {
        return s ;
    }
    int number = numRows ; 
    int N = s.size() / ( 2 * number - 2) + 1 ;
    int row = number ;
    
    //动态申请 number * [ (number - 1) * N] 大小的矩阵 

    char** array = new char*[row];
    
    int colomn = (number - 1) * N ; 

    for(int i= 0 ; i < row ; ++ i) {
        array[i] = new char[colomn];
    }
    for(int  i = 0 ; i < row ; i ++ )
    {
        for(int j = 0 ; j < colomn ; j ++ )
        {
            array[i][j] = ' ' ;
        }
    }
    int total = 0 ; 
    for(int i = 0 ; i < N ; i ++ )
    {
        for(int j = 0 ; j < ( 2 * number - 2 ) ; j ++)
        {
            if(total == s.size())
            {
                break ;
            }
            //下降序列
            if(total - i * (2 * number - 2) < number)
            {
                array[total % (2 * number - 2) ][total / (2 * number - 2) + i * (number - 2)] = s[total] ;
            }
            //上升序列
            else
            {
                array[number - 1 - total % (number - 1) ][ total % (number - 1) + i * (number - 1) ] = s[total] ;
            }
            
            total ++ ;
        }
    }
    string test;
    for(int  i = 0 ; i < row ; i ++ )
    {
        for(int j = 0 ; j < colomn ; j ++ )
        {
            if(array[i][j]!=' ')
            {
                test += array[i][j] ;
            }
        }
    }
    return test ;
    }
    
};
````

---

注：这种算法效率会比较低，但是比较好理解比较好想，我暂时没有想到什么更好更有效率的方法，欢迎能看到这篇博客的朋友提供思路。