# 0206 · Reverse Linked List · C++17

[原题](https://leetcode.com/problems/reverse-linked-list/) · [实现](p0206_reverse_linked_list.cpp) · [测试](../tests/cpp/test_p0206_reverse_linked_list.cpp)

原地反转一条无环单链表。`Solution::reverseList(ListNode*)`返回原尾节点，不分配结果节点、不释放原节点；节点值不变，只重接next。节点生命周期仍由调用者管理。实现使用评测环境的ListNode，本地测试先提供节点定义再include实现。

previous指向已经反转的前缀，current指向未处理后缀。每轮先保存following=current->next，再令current->next=previous，然后分别把previous和current推进到当前节点与保存的following。顺序不能交换：若先覆盖next再读取后继，原后缀入口就丢失。

循环入口不变量：两个部分在节点身份上不相交，合起来恰好是全部原节点；前缀按原序逆向排列，后缀保持原来的访问顺序。每轮把后缀头转移到前缀，保存following保持余段可达，不分配、丢弃或复制节点。有限无环输入每轮少一个未处理节点，current为空时previous就是完整反序链。

previous初始nullptr保证原头变成尾部后next为空。空输入返回nullptr，单节点返回自身。迭代时间O(n)、额外空间O(1)，没有递归栈开销；有环输入不属于合同，不能把这段程序当成兼容环的反转接口。

测试枚举长度0至6、值−1至1的1093条链表，用原节点数组的逆序作独立身份oracle；核对每个值、终止nullptr，再反转一次核对恢复全部原节点顺序和结构。重复值仍比较指针身份，因此仅交换节点值不能通过测试。

A补写题目长度上界5000节点的反转与二次恢复测试。节点值重复取−1、0、1，核对反序访问的每个原节点身份和值、nullptr终止，再次反转后逐个恢复原身份顺序、值及尾部空指针；不能只凭值序列判断成功。与原1093个小输入共用checkReversal，所有小输入仍完整保留。测试的unique_ptr集合在两次遍历结束前持续拥有各节点，算法结果只借用这些节点，既不接管也不释放所有权。

迭代实现每轮只保存previous、current、following三个指针，链表长度增加不增加调用栈深度，因此算法额外空间O(1)。常见递归实现需要等后缀返回再重接指针，若不具备可依赖的尾调用消除则有O(n)调用栈；C++17不保证尾调用消除。本次长链用例验证已写迭代接口的身份与结构，不把它当作实测递归栈溢出或性能比较。

A交回补丁时仅静态核对长链测试和辅助函数。2026-11-19，B应用后以GCC16.2、C++17、-O2 -Wall -Wextra -pedantic编译最终内容，无诊断、执行退出0；原1093个小链及新增5000节点链均通过精确身份反序、值、nullptr终止和二次恢复检查。未定义NDEBUG；此记录包含新增长链，区别于初稿验证，最终SHA与回执见PR。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0206_reverse_linked_list.cpp -o test_reverse
./test_reverse
```

B先写测试，已观察原样返回head的占位实现断言失败；完整实现运行结果见PR。assert测试不能定义NDEBUG。未提交LeetCode，不声称Accepted。B编写迭代实现与原1093个身份用例；A补写5000节点反转/恢复测试及栈空间说明，均借助OpenAI Codex整理。
