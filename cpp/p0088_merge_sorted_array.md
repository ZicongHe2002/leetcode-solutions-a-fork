# 88. Merge Sorted Array · C++17

[原题](https://leetcode.com/problems/merge-sorted-array/)给nums1前m个有效值和nums2的n个值，各自非递减，nums1.size()已经是m+n。`void Solution::merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)`在原vector内合并，不resize、不额外分配，不修改nums2。两个vector必须是不同对象。合同总长度1..200、值在±10^9内；总长度0可自然处理作为扩展。

从两段有效数据的尾部选较大值，放到nums1的最右待写位置。nums1中的预留0不参与有效值比较。left=m-1、right=n-1、write=m+n-1都使用有符号int，因此−1可以表示耗尽；left>=0的短路保护避免负下标访问。输入规模保证所有索引计算不溢出。

循环内保持`write=left+right+1`和已经完成的有序最大值后缀。只要nums2未耗尽，right>=0便推出write>left，所以写入位置在nums1未读取前缀之外。若left耗尽，只需复制nums2余段；若right耗尽，write=left，剩余nums1前缀已经在正确位置，直接结束。每轮消耗一个元素，O(m+n)时间、O(1)额外空间。

例如nums1=`[2,3,0]`、m=2，nums2=`[1]`，先从后方放3、再放2、最后放1。若从前方直接放1，就会破坏尚未读取的2；本实现借预留空间避免覆盖。

测试枚举−1..1、长度0..4的35条有序数组，交叉1225对，用独立拼接后std::sort为oracle。检查完整结果、原数据地址及nums2保持。另有5个固定案例，含200元素的单侧空输入、100+100相同值和±10^9边界。测试临时数组只属于测试oracle，求解实现本身无此分配。

A补写相等值与nums1先耗尽的账本。有效nums1前缀[0,2,2]，预留3个位置；nums2=[-1,2,3]。表中三个指针为本轮开始值，“完成后缀”为写入后状态：

| left | right | write | 选择 | 完成后缀 |
| --- | --- | --- | --- | --- |
| 2 | 2 | 5 | nums2的3 | [3] |
| 2 | 1 | 4 | 相等，取nums2的2 | [2,3] |
| 2 | 0 | 3 | nums1的2 | [2,2,3] |
| 1 | 0 | 2 | nums1的2 | [2,2,2,3] |
| 0 | 0 | 1 | nums1的有效0 | [0,2,2,2,3] |
| -1 | 0 | 0 | nums1耗尽，取nums2的-1 | [-1,0,2,2,2,3] |

另一个方向，nums1前缀[0,2]、nums2=[3]时首轮写3就耗尽nums2；write=left=1，剩余[0,2]无需复制。不能把“某侧耗尽”统一写成继续复制任意一侧，也不能因值为0就判断某个位置无效：nums1里下标<m的0是真实数据，下标>=m才是预留位置，含义由m决定。

所有读取nums1的下标最初为m−1并只会下降；预留后缀不被当作输入读取。right>=0时write>left又保证写入不破坏未读前缀。因此预留内容从0改为其他合法整数不会影响结果。A对原1225对有序输入分别再用−10^9和10^9初始化预留部分，新增2450次独立排序oracle比较，保持原地址/nums2检查；有效输入范围和长度仍合法。m=0、n=0和真实有效0均在枚举中保留。

A实际补写表、占位含义证明与2450次变换测试，交回时仅静态核对并通过git apply检查，A尚未本机编译。B随后应用完整补丁，以GCC16.2、C++17、-O2 -Wall -Wextra -pedantic编译整合后的测试，断言启用；1225原输入对、5个固定案例和2450次变换全部通过，退出0且无编译诊断。此运行覆盖A新增内容，原始红绿记录对应补写之前的版本。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0088_merge_sorted_array.cpp -o test_merge_array
./test_merge_array
```

B独立实现与解释，OpenAI Codex辅助；已先观察空实现断言失败，最终运行记录在PR。未提交LeetCode，不声称Accepted。
