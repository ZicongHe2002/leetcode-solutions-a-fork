# LeetCode 题解与代码

本仓库：`lw-liuwang/leetcode-solutions`。双方各有一个工作仓库：

- A：[lw-liuwang/leetcode-solutions](https://github.com/lw-liuwang/leetcode-solutions)，维护并评审B提交的C++代码。
- B：[ZicongHe2002/leetcode-solutions](https://github.com/ZicongHe2002/leetcode-solutions)，维护并评审A提交的Python代码。

A用Python，直接向B上游仓库提交Issue，通过自己的fork提交PR；B用C++17，直接向A上游仓库提交Issue，通过自己的fork提交PR。两个独立工作仓库分别保留，不用fork替换。工作任务、补写、评审及交接都在接收方的工作仓库中进行。

## 工作入口与已启用规则

| 接收仓库 | 新任务入口 | 默认分支审批规则 |
| --- | --- | --- |
| A接收B的C++17实现 | [A仓库Issues](https://github.com/lw-liuwang/leetcode-solutions/issues) | [规则27621383](https://github.com/lw-liuwang/leetcode-solutions/rules/27621383) |
| B接收A的Python实现 | [B仓库Issues](https://github.com/ZicongHe2002/leetcode-solutions/issues) | [规则27623033](https://github.com/ZicongHe2002/leetcode-solutions/rules/27623033) |

两条规则均已在各自main实际启用：至少一个有权限的非PR作者正式批准、内容推送撤销旧批准，仅使用merge commit。上游所有者评审对方的PR；普通外部账号的批准不能替代规则要求的审批。当前不互邀或授予对方写权限，旧邀请状态只作[初始化历史](https://github.com/ZicongHe2002/rsi-notes/issues/135)保留。

互投fork：[A向B的fork](https://github.com/lw-liuwang/leetcode-solutions-b-fork)、[B向A的fork](https://github.com/ZicongHe2002/leetcode-solutions-a-fork)。接收方需要补写时，使用PR允许的维护者编辑；若该权限不可用，直接在PR交回明确补丁，由原作者应用后再核对最终head。不能为补写临时绕过审批或新增协作者权限。

实现按四位题号命名，例如`python/p0001_two_sum.py`和`cpp/p0001_two_sum.cpp`，测试分别位于`tests/python/`与`tests/cpp/`。每篇题解附原题链接、自己的算法解释、不变量、复杂度与边界。完整规范见[CONTRIBUTING.md](CONTRIBUTING.md)。

每个代码PR必须由另一账号正式Code review；作者不能自approve。内容推送撤销旧批准，只以merge commit合并。实际共同补写才共同署名，review本身不替代共同创作。程序未运行或未提交LeetCode时如实记录，不声称已通过。代码由各账号借助OpenAI Codex辅助编写。
