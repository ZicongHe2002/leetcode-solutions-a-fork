# 0141 · Linked List Cycle · C++17

[原题](https://leetcode.com/problems/linked-list-cycle/) · [实现](p0141_linked_list_cycle.cpp) · [测试](../tests/cpp/test_p0141_linked_list_cycle.cpp)

判断沿next访问是否会再次到达同一节点。`Solution::hasCycle(ListNode*)`只读取指针和值，不修改链表或分配节点；题目里的pos只是输入构造说明，并非函数参数。实现依赖评测环境的ListNode定义，本地测试在include实现前提供兼容类型。

slow每轮走一步，fast走两步，移动后比较指针身份。循环先判断fast及fast->next非空，才读取fast->next->next；无环情况下fast到达尾部即退出。slow移动较慢，在这项循环条件成立时仍有合法当前节点可访问。

若存在环，设入环前缀长μ、环长λ。slow至多μ步进入环，fast此时也在环中；之后每轮相对位置增加1模λ，至多λ轮必为0，于是相遇。无环时fast有限步后遇到nullptr。时间O(n)（有环时O(μ+λ)）、额外空间O(1)。

初始slow和fast同时指向head不能作为环证据，否则普通非空链表都会被误报。指针比较也不能换成val比较：三个值同为7的无环节点，第一轮slow和fast可能值相同但身份不同。

测试遍历长度0至8、无环或每个合法环入口，共45种结构；全部节点故意同值，使用unordered_set记录已访问指针作为独立oracle，随后核对所有next和值完全不变。unique_ptr只负责各独立节点的生命周期，next为非拥有指针，因此测试含环时也不会递归释放或泄漏这些节点。

A补写slow解引用安全性。设在第t轮入口已完成t次移动；在无环链中，slow位于从head起第t个节点，fast若非空则位于第2t个节点。循环条件同时保证fast和它的后继存在，即长度至少2t+2，因此第t个节点及其后继都存在，slow=slow->next安全。若有环，所有沿next可达的节点都有后继，slow同样不会解引用空指针。这个论证依赖输入为静态有效链表，不能用于节点被并发释放的情况。

A把原45种小结构的身份oracle和拓扑不变检查提为同一checkStructure，新增6种长结构：9999/10000节点的奇偶无环尾部，以及10000节点下入口9000、1000、0、9999的环。分别覆盖长前缀、长环、纯环与尾节点自环，仍以独立指针集合判断，并逐个核对全部next和值不变。next为非拥有指针，含环时unique_ptr也独立管理各节点，不沿环递归析构。

A交回补丁时仅静态核对新增测试。2026-11-19，B应用后以GCC16.2、C++17、-O2 -Wall -Wextra -pedantic编译最终内容，无诊断、执行退出0；原45种小结构及6种长结构全部通过独立身份集合oracle和完整next/值保持检查。未定义NDEBUG；此为包含新增测试的验证，区别于原head的45种结构记录，最终SHA与回执见PR。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0141_linked_list_cycle.cpp -o test_cycle
./test_cycle
```

B先写测试并实际观察恒False占位实现断言失败；完整运行结果见PR。测试要求NDEBUG未定义。未提交LeetCode，不声称Accepted。B编写Floyd实现与原45种结构oracle；A补写slow安全性证明及6种长结构测试，均借助OpenAI Codex整理。
