### leetcode 93.Restore IP Addresses

#### 题目：

Given a string containing only digits, restore it by returning all possible valid IP address combinations.

**Example:**

```
Input: "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]
```

----

#### 解法：

这个题直接给了一串数字让我们将其拆分成有效的 ip 地址。

ip地址由 32 位 2 进制数字构成的，每八位为一个段，共 4 个段，也即每个段最大为十进制数字 255 ；

当我们进行拆分时候，可以判断每个段内的数字是否小于 255 来判断出 ip 地址是否符合要求；

所以我们可以用 3 重循环的思路，将所给的字符串进行拆分为 4 个段，按位进行遍历；

---

#### 代码：

````cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ret;
        if(s.size() > 12)
            return ret;
        for(int i = 0; i < s.size(); i ++)
        {//第一段从第 0 位到第 i 位
            for(int j = i+1; j < s.size(); j ++)
            {//第二段从第 i+1 位到第 j 位
                for(int k = j+1; k < s.size()-1; k ++)
                {//第三段从 j+1 位到 k 位 
                 //第四段从 k+1 位到 s.size()-1 位
                    string ip1 = s.substr(0, i+1);
                    string ip2 = s.substr(i+1, j-i);
                    string ip3 = s.substr(j+1, k-j);
                    string ip4 = s.substr(k+1);
                    if(check(ip1) && check(ip2) && check(ip3) && check(ip4))
                    {
                        string ip = ip1 + "." + ip2 + "." + ip3 + "." + ip4;
                        ret.push_back(ip);
                    }
                }
            }
        }
        return ret;
    }
    bool check(string ip)
    {
        int value = stoi(ip);
        if(ip[0] == '0')
        {
            return (ip.size() == 1);
        }
        else
        {
            if(value <= 255)
                return true;
            else
                return false;
        }
    }
};
````