# 34. Find First and Last Position · C++17

[原题](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)要求在非递减数组中找target首尾下标，缺失时返回[-1,-1]。`vector<int> Solution::searchRange(vector<int>& nums, int target)`保持输入。官方允许空数组，长度最多100000，数值与target在[-10^9,10^9]；相同值可以连续重复。

第一次二分找首个不小于target的位置first。候选元素半开区间为[left,right)，右侧哨兵size允许作为答案：nums[middle]<target时left=middle+1，否则right=middle。若first=size或该位置不等于target，即不存在目标；短路检查保证不会访问nums[size]。

目标存在时，再在[first,size)找首个严格大于target的位置。此时nums[middle]<=target才推进left，否则收缩right；得到的边界减一就是最后一个target。没有计算target+1，也没有从首个命中处向左右线性扫描，所以大量重复元素仍保持对数时间。

第一次搜索把已经排除的前缀全部证明为<target，后缀全部证明为>=target，答案边界始终在闭区间[left,right]。mid始终位于当前非空元素区间，两个更新都保持分区且严格缩小。终止left=right时即唯一分界。第二次同理，前缀判定改为<=target、后缀改为>target；第一次已经证明first之前全小于目标，故可以从first开始。已确认nums[first]=target，最终上边界必大于first，减一不会产生越界答案。

例如[1,2,2,2,4]查2，下边界是1，上边界是4，因此返回[1,3]；若只找到任意一个2就返回两次该位置，会漏掉重复范围。两个搜索各O(log n)，总时间O(log n)，空数组常数时间；除固定两个返回下标外只用O(1)额外空间。官方长度允许int下标，中点写作left+(right-left)/2。

测试oracle从头到尾线性记录首个和最后一个相等位置，不使用二分或标准库边界算法。穷举五个值−2..2上长度0..8的全部非递减数组，共1287个，每个查询−3..3，共9009次。8个固定例子包含重复段、缺失、单元素、空输入和两个值域端点。另有5次长度100000检查，覆盖全相等、全缺失和每值重复10次数组的首段、中段、尾段。每次检查输入未变。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0034_search_range.cpp -o test_range
./test_range
```

B独立编写实现、解释及测试，OpenAI Codex辅助。总返回[-1,-1]的占位实现已实际触发存在目标的断言失败，最终运行结果按实际日志补充。未向LeetCode提交，不声称Accepted。

最终本机验证：GCC16.2、C++17、`-O2 -Wall -Wextra -pedantic`，上述目标测试及完整分支25个程序均编译无诊断、运行退出0。独立完整内容评审无阻塞。实际目标输出：

```text
1287 sorted arrays / 9009 linear-oracle queries; 8 fixtures and 5 maximum-length checks passed; input unchanged
```

未提交LeetCode。A后续真实补写将另行核验并记录，不提前共同署名。

## A实际补写与最终验证

A补写[1,2,2,2,4]查找2的两个半开边界账本：

| 搜索 | left / middle / right | 比较与下一步 |
| --- | --- | --- |
| 下边界 | 0 / 2 / 5 | 2>=2，right=2 |
| 下边界 | 0 / 1 / 2 | 2>=2，right=1 |
| 下边界 | 0 / 0 / 1 | 1<2，left=1，first=1 |
| 上边界 | 1 / 3 / 5 | 2<=2，left=4 |
| 上边界 | 4 / 4 / 5 | 4>2，right=4，边界为4 |

返回[1,3]。两次比较分别是<与<=，否则会把重复段的首尾混成同一个边界；缺失检查发生在第二次搜索之前。

若在数组头部添加一个严格小于原全部元素且严格小于target的合法值，新值不会成为目标，原有目标下标全部加1；原来缺失则仍返回[-1,-1]。A令新值为min(target,原最小值)−1，仅在旧长度小于100000且该最小值大于−1000000000时应用。9009个小查询及6个符合条件的固定例子共9015次检查；两个已到数值下界的例子和5个满长度边界跳过。空数组可以合法添加一个比target小的值，缺失结论保持。原线性首尾扫描oracle、重复次数和变换前后输入保持断言均保留，没有计算target+1。

A在本机Ubuntu WSL使用GCC15.2、C++17、`-O2 -Wall -Wextra -pedantic`实际编译新增性质后的精确测试，无诊断、运行退出0，未定义NDEBUG。测试文件LF SHA256 `b681823cd449f75706299b84a27980782485028b6f56794ea4e8e747f467ce79`。上方GCC16.2/25程序结果属于B初稿阶段；A本次只运行本题，不冒充整条分支验证。

```text
9015 prefixChecks passed; 1287 sorted arrays / 9009 linear-oracle queries; 8 fixtures and 5 maximum-length checks passed; input unchanged
```

A实际编写账本、证明与性质测试，双方贡献将整合为同一内容提交。未向LeetCode提交。
