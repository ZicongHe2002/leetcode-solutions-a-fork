# 0003 · Longest Substring Without Repeating Characters · C++17

[原题](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · [实现](p0003_longest_substring.cpp) · [测试](../tests/cpp/test_p0003_longest_substring.cpp)

返回无重复字符的最长连续子串长度。`Solution::lengthOfLongestSubstring`接收字符串常量引用，不复制或修改输入。采用LeetCode通常的8位字节字符环境；中文、emoji的UTF-8多字节文本不会自动按Unicode码点或显示字形处理。长度按原题范围可由int表示。

固定256项数组记录每个字节最近出现的下标，未出现为−1。扫描right时，将left更新为`max(left, latest[byte]+1)`，再登记当前位置并更新窗口长度。将char显式转为unsigned char，避免高位字节被当成负数组下标。

循环不变量：更新后的`[left,right]`不含重复字节，且是以right结尾的最长合法窗口。原窗口已无重复，唯一可能新增的冲突来自当前字节的最近位置；若它在窗口内，左端必须越过它，若在窗口外则无需移动。取max同时防止left退回已排除区域。因此枚举所有右端点的窗口长度即可得到全局答案。

例如`abba`：left依次为0、0、2、2，窗口依次为a、ab、b、ba，最大长度2。最后一个a的旧位置0在窗口外，不能把left退回1，否则会把bba当成合法窗口。

固定字节表初始化O(256)，扫描O(n)，在固定8位字母表下总时间O(n)、额外空间O(1)。空输入返回0，空格也作为普通字节计入。测试枚举abc上长度0至7的全部3280个字符串，以逐起点扫描至首个重复的独立oracle核对，另含8个固定用例及高位字节、内嵌NUL两个扩展用例。

A补写单射字节重命名性质。对每个字节应用相同单射f且不改变序列长度，两个位置的字节相等当且仅当变换后相等；所以每个区间是否含重复完全不变，最长合法长度也不变。测试用f(x)=(5x+17) mod 256：5与256互素，因此它在8位字节集合上是排列。对原3280个穷举串同时核对重命名后的独立oracle与实现，包含高位字节索引。

单射是必要前提：若把a与b都映射为x，ab的最长长度2会变成xx的1。此性质是逐字节重命名，不是Unicode编码转换。UTF-8的两个é由C3 A9 C3 A9四个字节组成，本实现返回2；按码点处理时两个相同码点的答案是1。新增用例只验证字节接口，不声称实现码点分割或显示字形识别。

A新增的3280个性质实例及UTF-8例子在交回时仅由A静态核对。2026-11-19，B实际应用补丁后用GCC16.2、C++17、-O2 -Wall -Wextra -pedantic编译最终内容，无诊断、退出0；8个固定用例、3280个原穷举字符串、2个字节扩展、3280个重命名检查及UTF-8字节例子全部通过。此记录覆盖新增内容，区别于此前初稿head的运行结果；未定义NDEBUG。最终head与回执见PR。

在仓库根目录执行：

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0003_longest_substring.cpp -o test_longest
./test_longest
```

B先编写行为测试，并实际观察占位实现因断言失败；完成实现后的运行结果见PR。测试使用assert，构建不能定义NDEBUG。未提交LeetCode，不声称Accepted。B编写滑动窗口与原有oracle；A补写字节重命名性质测试及UTF-8语义解释，均借助OpenAI Codex整理。
