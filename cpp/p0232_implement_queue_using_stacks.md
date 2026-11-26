# 232. Implement Queue using Stacks · C++17

[原题](https://leetcode.com/problems/implement-queue-using-stacks/)要求仅用两个栈实现 FIFO 队列，接口为 `MyQueue()`、`push(int)`、`pop()`、`peek()` 和 `empty()`。输入值为 1..9；每个测试实例至多调用四种方法共 100 次，且 pop/peek 保证在非空队列上调用。实现遵守这些前提，没有给非法空队列查询增加题外返回值。

incoming 接收新入队值，outgoing 的栈顶保存当前队首。仅当 outgoing 为空时，把 incoming 的所有元素逐个弹出并压入 outgoing，顺序恰好翻转，最早入队值出现在栈顶。pop 取出并删除该值；peek 只读取它，允许内部搬运但不改变可观察队列；empty 要同时检查两个栈。实现只调用标准栈的 push、top、pop 和 empty。

不变量：从队首到队尾的逻辑序列，总是 outgoing 从栈顶到栈底的序列，接着 incoming 从栈底到栈顶的序列。push 在后一段末端加入新值，保持 FIFO。outgoing 非空时，队首已在那里；此时不能把 incoming 新值搬到它的上方，否则会让新值越过旧值。outgoing 为空时，整体倒栈保持逻辑顺序。pop 删除逻辑首项，peek 保持逻辑序列，两者都符合接口。

例如先 push 1、2，再 peek、pop，会留下旧值 2 在 outgoing；此时 push 9 进入 incoming，下一次 peek 必须仍为 2。pop 2 后才把 9 搬到空的 outgoing。清空后两个栈都为空，再 push 可复用同一对象。

push 和 empty 为 O(1)。一次 pop/peek 可能触发 n 个值的搬运，最坏为 O(n)，不能宣称每次最坏 O(1)。但每个入队值只进入 incoming 一次、从 incoming 转入 outgoing 至多一次、最终从 outgoing 弹出至多一次，所有搬运可摊给对应 push。执行 k 次公开操作的总栈操作数为 O(k)，因此各公开操作均摊还 O(1)，空间 O(n)，n 为尚未出队值的数量。销毁两个栈会销毁尚存元素，析构不作常数时间承诺。

测试使用独立 deque 直接模拟 FIFO，不保存或检查双栈内部状态。枚举 push(1/2/9) 与合法 pop 的全部长度 0..8 操作前缀，共 59236 条；每条用新对象回放，逐步核对 empty，非空时重复两次 peek，确保查询不消耗值。每个实例最多 33 次公开调用。固定用例单独覆盖倒栈后继续 push、旧队首优先、重复 peek、清空复用。

另建一个实例恰好执行 100 次公开调用：初始 empty 一次，push 25 个 `1 + i % 9`，对前 24 项逐一 peek/pop，检查并移除最后的 7，确认空，再 push/peek/pop 9 并确认空，最后连续检查空队列 19 次。所有 pop/peek 均合法；这个边界用例不会把多次独立穷举累加到同一个实例。

状态表把两个栈都按“栈底到栈顶”列出，逻辑队列按“队首到队尾”列出。peek 可以触发内部搬运，但不消费队首。

| 操作 | incoming | outgoing | 逻辑队列 | 返回值 |
| --- | --- | --- | --- | --- |
| 初始 | [] | [] | [] | — |
| push(1) | [1] | [] | [1] | — |
| push(2) | [1,2] | [] | [1,2] | — |
| peek() | [] | [2,1] | [1,2] | 1 |
| pop() | [] | [2] | [2] | 1 |
| push(9) | [9] | [2] | [2,9] | — |
| peek() | [9] | [2] | [2,9] | 2 |
| pop() | [9] | [] | [9] | 2 |
| pop() | [] | [] | [] | 9 |
| push(2) | [2] | [] | [2] | — |
| peek() | [] | [2] | [2] | 2 |
| pop() | [] | [] | [] | 2 |

势能证明可把一次完整的单元素倒栈视为一个单位工作，因为它只包含常数次标准栈操作。令势能 Φ 为 incoming 的元素数，初始为 0，始终非负。push 的实际成本为 1、势能增加 1，摊还成本为 2；搬运 m 项的 pop/peek 实际成本为 m+O(1)，势能降低 m，摊还成本为 O(1)。不搬运的查询、删除及 empty 的实际成本为 O(1)，势能不增加。对任意合法操作前缀求和，势能差抵消，总实际成本不超过总摊还成本，因此每次操作摊还 O(1)。这不改变某次倒栈需要 O(n) 的最坏时间。

值重命名性质：对 1..9 上任意双射 f，保持 push/pop/peek/empty 的调用顺序，只把每个 push(v) 改为 push(f(v))。双栈仅搬运值，不按数值比较或分支，所以两对象的元素位置始终对应，empty 相同，每次 pop/peek 的结果恰好变为 f(原结果)。新增测试对全部 59236 条合法序列分别应用 f(v)=10-v 和 f(v)=v%9+1，共核对 118472 对独立回放；每个对象最多 33 次调用，全部值仍在 1..9。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0232_implement_queue_using_stacks.cpp -o test_queue
./test_queue
```

B（ZicongHe2002）使用 OpenAI Codex 辅助编写实现、证明和测试。TDD 的 API 占位实现已在 `peek()==1` 的 FIFO 断言上实际失败；最终版本运行结果见对应 PR。未向 LeetCode 提交，不声明 Accepted。真实共同补写后才增加共同署名，正式 review 本身不算内容创作。

A（lw-liuwang）使用 OpenAI Codex 辅助补写上述性质证明、状态表与对应性质测试；实现及原有证明和测试由 B 提供。双方实际内容共同保留，正式 review 与运行测试不代替创作。
