# 35. Search Insert Position · C++17

[原题](https://leetcode.com/problems/search-insert-position/)给严格递增数组，要求返回target现有下标或保持顺序的插入下标。`int Solution::searchInsert(std::vector<int>& nums, int target)`不修改数组；原题长度1..10000，空数组返回0是扩展。答案可以是n，它表示尾后插入位置而非可读取元素。

设p是第一个不小于target的位置，若不存在则p=n。维护闭答案范围left<=p<=right，初始[0,n]，而实际可查元素范围为[left,right)。当nums[middle]<target时，排序保证所有下标<=middle的元素也小于target，因此p>=middle+1；否则middle本身已经满足条件，故p<=middle。前者更新left=middle+1，后者更新right=middle。

循环条件left<right保证left<=middle<right<=n，读取nums[middle]不会访问尾后n。两分支均严格缩短right-left；结束时left=right，夹住的唯一p就是返回值。不能在大于等于分支使用right=middle-1，因为middle仍可能正是答案。没有元素加减运算，INT_MIN/MAX也能正确比较；middle用left+(right-left)/2避免端点相加。

时间O(log n)，额外空间O(1)。测试对[-3,3]的全部128个递增子集和9个target核对1152次，以线性统计小于target的数量为独立oracle；另有4个明确期望、5个int边界和5个10000长度边界，并检查输入不变。空子集是显式扩展。

A补写nums=[−2,0,3,7]的区间账本，使用0基下标。每个箭头都是一次比较后的新区间；括号内为middle及读到的值：

| target / 位置类型 | [left,right)与比较过程 | 返回 |
| --- | --- | --- |
| −3 / 首前 | [0,4) → (2,3) → [0,2) → (1,0) → [0,1) → (0,−2) → [0,0) | 0 |
| 0 / 命中 | [0,4) → (2,3) → [0,2) → (1,0) → [0,1) → (0,−2) → [1,1) | 1 |
| 2 / 中间 | [0,4) → (2,3) → [0,2) → (1,0) → [2,2) | 2 |
| 9 / 尾后 | [0,4) → (2,3) → [3,4) → (3,7) → [4,4) | 4 |

闭答案范围仍是left<=p<=right；表里的半开区间只约束可读取元素。返回4合法，但从未读取nums[4]。命中middle=1时保留right=1，之后仍需排除其左侧更早的位置，不能用right=middle−1丢掉候选。

同时平移全部元素和target同一个k，只要结果不溢出且仍满足题目值域，就保持每个比较nums[i]<target的真假，故第一个不小于目标的位置保持。A对1152组小枚举增加k=7的性质检查：原元素−3..3、目标−4..4，映射后元素4..10、目标3..11均合法；期望来自原数组的线性计数，并检查映射后输入不变。未对INT_MIN/MAX扩展做加7，避免测试自己溢出；空数组仅沿用已声明扩展。

A编写以上账本、证明及性质测试，已静态核对并通过补丁适用/空白检查，尚未本机编译C++；需B对最终整合内容实际运行。

B已应用A补丁，使用GCC16.2、C++17、`-O2 -Wall -Wextra -pedantic`实际编译并运行共同内容：1152组原oracle、1152次合法平移、4个固定例子及10个整数/长度边界通过，无编译诊断；原基线分支全部13个测试程序退出0。初始占位失败日志保留，当前绿色日志对应新增性质测试后的文件。服务端提交如另行生成，其精确head的运行与字节核对在PR单独回填；没有将源分支运行等同于已运行服务端head。未提交LeetCode。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0035_search_insert.cpp -o test_insert
./test_insert
```

B独立编写实现、证明和测试，OpenAI Codex辅助。已先观察恒0接口断言失败；实际最终运行记录见PR。未提交LeetCode，不声称Accepted。
