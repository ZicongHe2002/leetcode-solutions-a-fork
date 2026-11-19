# 167. Two Sum II · C++17

[原题](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)给非递减数组，保证恰有一个不同下标对的和等于target。`std::vector<int> Solution::twoSum(std::vector<int>& numbers, int target)`返回递增的1基下标，不修改输入。重复值允许来自不同位置。原题长度2..30000、元素及target在[-1000,1000]；无解抛std::invalid_argument是接口扩展。

left/right从首尾开始。和小于target时，固定left，任何仍在区间内的另一个值都不大于numbers[right]，因而和仍太小，排除left安全。和大于target时，固定right，任何候选搭档都不小于numbers[left]，和仍太大，排除right安全。相等就返回{left+1,right+1}。非严格排序足以支持这些不等式，无需先按值去重。

不变量是未找到的合法对仍在[left,right]内，两个分支只排除被证明不可能的端点；right-left每轮减少1，保证终止。left<right防止重复使用同一位置，相等分支输出满足1<=left+1<right+1<=n。求和前先把左操作数转long long，因此加法在宽类型执行；测试包含INT_MIN与INT_MAX这一超出官方值域的扩展。长度转int由30000上界保证，空输入的right=-1也不会访问元素。

时间O(n)、工作空间O(1)，输出固定两个整数。独立oracle枚举长度2..6、值[-2,2]的非递减数组和target[-4,4]，穷举所有first<second的下标对，只对恰有一解的输入比较精确1基答案和输入不变。实际通过543个唯一解输入；另有7个明确答案和4个无解扩展。值域扩展中，[1,2,INT_MAX]目标3的首轮和超过INT_MAX，[INT_MIN,-2,-1]目标-3的首轮和低于INT_MIN，正确排除方向分别为right减1和left加1，用来覆盖宽类型求和的必要性。INT_MIN与INT_MAX互加仍在int内，因此不单靠该案例声称覆盖加法溢出风险。

A补写numbers=[−3,0,1,1,6]、target=2的完整指针表，left/right为0基下标：

| left / right | 端点值 | 和 | 动作 |
| --- | --- | --- | --- |
| 0 / 4 | −3 / 6 | 3 | 太大，right变3 |
| 0 / 3 | −3 / 1 | −2 | 太小，left变1 |
| 1 / 3 | 0 / 1 | 1 | 太小，left变2 |
| 2 / 3 | 1 / 1 | 2 | 返回1基[3,4] |

两个1来自不同位置，是唯一合法下标对；先去重会破坏位置与解。最后left仍严格小于right，两个输出都在1..n。若输入有多个合法下标对，原题的唯一答案保证已不成立，不能指定其中一组后要求实现一定返回它；无解抛异常也只按已声明扩展检验。

元素全加k、target加2k后，对任意原下标i<j，有(numbers[i]+k)+(numbers[j]+k)=target+2k当且仅当原和等于target，所有下标解构成同一集合。加同一常数保持非递减顺序，唯一解及1基位置因此保持。A只对小枚举中543个唯一解输入加k=3：元素−2..2变1..5，目标−4..4变2..10，仍在官方范围且无溢出；INT_MIN/MAX扩展不平移。新增核对使用原穷举oracle的精确下标对，并验证映射后数组不变。

A实际编写以上内容和性质检查，尚未本机编译C++；补丁适用/空白检查通过，需B验证最终内容，不能沿用原head运行记录。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0167_two_sum_ii.cpp -o test_two_sum_ii
./test_two_sum_ii
```

B独立实现、解释和测试，OpenAI Codex辅助。已先观察空结果占位实现断言失败；真实最终验证见PR。未提交LeetCode，不声称Accepted。
