### leetcode 690. Employee importance

#### 题目：

You are given a data structure of employee information, which includes the employee's **unique id**, his **importance value**and his **direct** subordinates' id.

For example, employee 1 is the leader of employee 2, and employee 2 is the leader of employee 3. They have importance value 15, 10 and 5, respectively. Then employee 1 has a data structure like [1, 15, [2]], and employee 2 has [2, 10, [3]], and employee 3 has [3, 5, []]. Note that although employee 3 is also a subordinate of employee 1, the relationship is **not direct**.

Now given the employee information of a company, and an employee id, you need to return the total importance value of this employee and all his subordinates.

**Example 1:**

```
Input: [[1, 5, [2, 3]], [2, 3, []], [3, 3, []]], 1
Output: 11
Explanation:
Employee 1 has importance value 5, and he has two direct subordinates: employee 2 and employee 3. They both have importance value 3. So the total importance value of employee 1 is 5 + 3 + 3 = 11.
```

**Note:**

1. One employee has at most one **direct** leader and may have several subordinates.
2. The maximum number of employees won't exceed 2000.

----

#### 解法：

这个题大致意思是，给定一个id我们找出所有他的下属，并对其所有下属、下属的下属以及他自己的importance求和，最后返回求和结果。

具体做的话，可以看作是对一颗二叉树求层次遍历，对每一个结点都进行求和，将子结点的和返回给父节点。

`为了降低时间复杂度，我们可以把 list 中的结点存放在 hashmap 中.`

#### 代码：

````java
/*
// Employee info
class Employee {
    // It's the unique id of each node;
    // unique id of this employee
    public int id;
    // the importance value of this employee
    public int importance;
    // the id of direct subordinates
    public List<Integer> subordinates;
};
*/
class Solution {
    public int getImportance(List<Employee> employees, int id) {
        if (employees == null || employees.size() == 0) {
            return 0;
        }

        Map<Integer, Employee> map = new HashMap<>();
        for (Employee e : employees) {
            map.put(e.id, e);
        }

        return helper(map, id);
    }

    private int helper(Map<Integer, Employee> map, int id) {
        if (!map.containsKey(id)) {
            return 0;
        }

        int total = map.get(id).importance;
        for (int subId : map.get(id).subordinates) {
            total += helper(map, subId);
        }
        return total;
    }
};

````

