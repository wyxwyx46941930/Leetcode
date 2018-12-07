### leetcode 444. Sequence Reconstruction

Check whether the original sequence `org` can be uniquely reconstructed from the sequences in `seqs`. The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequence of the sequences in `seqs` (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). Determine whether there is only one sequence that can be reconstructed from `seqs` and it is the `org` sequence.

**Example 1:**

```markdown
Input:

org: [1,2,3], seqs: [[1,2],[1,3]]

Output:

false

Explanation:

[1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.

```

**Example 2:**

```
Input:

org: [1,2,3], seqs: [[1,2]]

Output:

false

Explanation:

The reconstructed sequence can only be [1,2].
```

**Example 3:**

```
Input:

org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]

Output:

true

Explanation:

The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
```


**Example 4:**

```
Input:

org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]

Output:

true
```

*UPDATE (2017/1/8):*

The seqs parameter had been changed to a list of list of strings (instead of a 2d array of strings). Please reload the code definition to get the latest changes.

----

#### 思路：

这个题是让我们遍历所有 `seqs` 序列来推断是否可以唯一确定所给出的` org`，换句话说就是求[拓扑排序](https://blog.csdn.net/qq_24028753/article/details/77692447) ；

这里对 `example` 中的例子稍作解释，例如`example 1` 与 `example 3 `：

这两个例子中所给定的 `org`是完全一样的`[1，2，3]`，但是`seqs`序列中`example 1`中给定的是`[1,2],[2,3]`而`example 3`中给定的是`[1,2],[1,3],[2,3]`，这里我们可以假设给定的 `seqs` 序列是可以边叠加在同一个有向图中的依赖序列，那么可推出：

![TIM截图20181207163727](.\TIM截图20181207163727.png)

接着我们对这两个图示进行**拓扑排序，我们每次都从出度最多的节点出发，在出发前检查是否这个点是否是只有出度，如果存在入度，那么去找它的入度节点中出度数目最大的**，那么`example 1`可推出序列：[1,2,3]或者[1,3,2]；`example 3`可以推出序列：[1,2,3]；所以从这里我们就可以从`example 3 `中唯一确定原序列，而`example 1`并不可以。

----

#### 代码：

``` cpp
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (seqs.empty()) return false;
        int n = org.size(), cnt = n - 1;
        vector<int> pos(n + 1, 0), flags(n + 1, 0);
        bool existed = false;
        for (int i = 0; i < n; ++i) pos[org[i]] = i;
        for (auto& seq : seqs) {
            for (int i = 0; i < seq.size(); ++i) {
                existed = true;
                if (seq[i] <= 0 || seq[i] > n) return false;
                if (i == 0) continue;
                int pre = seq[i - 1], cur = seq[i];
                if (pos[pre] >= pos[cur]) return false;
                if (flags[cur] == 0 && pos[pre] + 1 == pos[cur]) {
                    flags[cur] = 1; --cnt;
                }
            }
        }
        return cnt == 0 && existed;
    }
};
```