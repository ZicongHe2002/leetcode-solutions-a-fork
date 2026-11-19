# 0704 · Binary Search · C++17

[原题](https://leetcode.com/problems/binary-search/) · [实现](p0704_binary_search.cpp) · [测试](../tests/cpp/test_p0704_binary_search.cpp)

在严格升序、无重复的整数数组中查找目标，命中返回下标，否则−1。`Solution::search(vector<int>&, int)`保持输入不变，不通过排序改变问题。题目数组长度范围保证返回下标可用int表示；空数组作为自然扩展返回−1。

使用半开候选区间`[left,right)`，初始为`[0,nums.size())`。非空时计算`middle=left+(right-left)/2`。中点偏小时令left=middle+1，偏大时令right=middle，命中立即返回。用size_t保存边界，避免空数组先计算`size()-1`造成无符号下溢；返回−1则仍使用int返回类型。

不变量：若目标存在，其下标仍在候选区间内。严格升序使每次删除的一侧都不可能含目标。`left <= middle < right`保证两种未命中更新都使非负区间长度严格下降，最终命中或区间为空。右端不包含在区间内，不能把right=middle混写成闭区间的middle−1。

例如数组`[2,5]`查找4，区间从`[0,2)`经过中点1缩为`[0,1)`，再由中点0推进left至1，空区间返回−1。查找2时第一次缩为`[0,1)`，下标0仍保留并会被命中。

时间O(log n)，额外空间O(1)。测试覆盖9个固定边界用例，并枚举−3至3的128个有序子集，对每个检查−4至4的9个目标，共1152次与std::find线性oracle比较。每次同时核对输入不变。

A补写整体平移性质。在不发生整数溢出的前提下，同时把每个数组值和target加上同一个d，则每个比较的大小关系与相等关系不变，严格升序也保留。目标存在时同一下标仍唯一命中；不存在时平移不会制造相等值，仍返回−1。数组下标没有随数值平移改变。

对原1152个有序子集/目标组合，取d为−1000、0、1000，新增3456个实例；以原std::find结果为期望，并检查平移输入不变。原数组值在−3至3、目标在−4至4，故平移后均在−1004至1004范围，远离int溢出。不能把证明用于发生溢出的机器整数运算。空数组的每个平移目标仍不命中，维持自然扩展约定。

这些新增性质测试由A实际编写，交回时只完成静态核对。2026-11-19，B应用后用GCC16.2、C++17、-O2 -Wall -Wextra -pedantic编译最终内容，无诊断、退出0；9个固定案例、1152个线性oracle组合及3456次平移性质检查全部通过。此记录覆盖A新增内容，区别于B原始head的验证；未定义NDEBUG。最终head与回执见PR。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0704_binary_search.cpp -o test_binary
./test_binary
```

B先写测试，已实际观察占位实现因断言失败；最终实现的运行结果见PR。assert测试不能定义NDEBUG。未提交LeetCode，不声称Accepted。B编写半开区间实现与原有线性oracle；A补写平移性质证明及测试，均借助OpenAI Codex整理。
