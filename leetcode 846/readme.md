### leetcode 846. Hand of Straights 

#### 题目：

Alice has a `hand` of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size `W`, and consists of `W` consecutive cards.

Return `true` if and only if she can.

 


**Example 1:**

```bash
Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
```

**Example 2:**

```bash
Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.
```

 

**Note:**

1. `1 <= hand.length <= 10000`
2. `0 <= hand[i] <= 10^9`
3. `1 <= W <= hand.length`

-----

#### 解法：

这个题大致意思是让我们判断能否在给定序列中找到 `hand.size() / W`个长度为 W 的连续递增序列。



- 首先，我们可以判断 `hand.size() % W`是否成立，因为任意一个不满足 W 个的序列都不满足题意

- 其次，我们就要考虑怎么凑成连续的序列：

  - 这里我们可以考虑使用`map`映射的方法，举个例子：

    - 假如现在序列为`example 1` ,也即`hand = [1,2,3,6,2,3,4,7,8]`,那么

      - map[1] = 1;
      - map[2] = 2;
      - map[3] = 2;
      - map[4] = 1;
      - map[6] = 1;
      - map[7] = 1;
      - map[8] = 1;

    - 我们现在可以这么思考，如果序列连续，那么任意一个开始点 `start` 往后数`W-1`个连续数字的`map`值一定满足：
      $$
      map[start + W - 1] >= map[start + W - 2]  >=  ...... map[start]
      $$

    - 且每一次我们处理完相应的序列之后，都要让的`map[start]`之前的`map[start + W - N]`的值减去`map[start]`，这表明我们已经访问过某个序列。如果在处理过程中有某个`map[start + W - N] < 0 `，那证明序列出现了中断，也就不满足题意。

------

#### 代码：

```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        int len = hand.size();
        if(len%W != 0)
            return false;
        sort(hand.begin(), hand.end());
        map<int, int> cnt;
        for(auto h:hand)
            cnt[h]++;
        for(auto it:cnt){
            if(it.second > 0){
                for(int i=W-1; i>=0; i--){
                    cnt[it.first+i] -= cnt[it.first];
                    if(cnt[it.first+i] < 0)
                        return false;
                }
            }
        }
        return true;
    }
};
```

