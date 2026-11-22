# 74. Search a 2D Matrix · C++17

[原题](https://leetcode.com/problems/search-a-2d-matrix/)给矩形矩阵，各行非递减，后一行首元素严格大于前一行末元素；判断target是否出现。官方行数和列数均在1..100，元素及target在[-10000,10000]。`bool Solution::searchMatrix(vector<vector<int>>& matrix, int target)`保持输入。不要求行内元素互异；仅保证行列分别有序、但不满足上述跨行关系的矩阵不属于本题合同。

按行优先顺序把矩阵看作一个虚拟数组，不复制数据。列数为columns，虚拟下标i对应`matrix[i/columns][i%columns]`。在半开区间[left,right)上二分，初始[0,rows*columns)。中点值等于target就返回true，小于target则丢弃直到中点的前缀，大于target则保留中点之前的候选。最终空区间意味着目标缺失。

行内相邻元素非递减，行边界两侧又严格递增，所以虚拟序列整体非递减，重复值只可能留在同一行内。每个合法i都唯一拆成商和余数，0<=商<rows、0<=余数<columns；row*columns+column还原同一下标，访问与线性顺序一一对应。

循环不变量是若target存在且未返回，至少一个匹配下标仍在[left,right)。中点较小时，之前所有值都不大于中点，故不可能命中；中点较大时，中点及之后都不小于它，故可以排除。两种更新严格缩小候选长度，且每次至多保留一半。时间O(log(rows*columns))，额外空间O(1)；不会产生矩阵副本或扁平数组。官方总元素至多10000，int下标及乘积安全。

例如[[1,1,3],[5,5,7]]找5，初始虚拟区间[0,6)，middle=3映射(1,0)，立即命中。找4时middle=3的5过大，区间变[0,3)；middle=1的1过小变[2,3)；middle=2的3过小变[3,3)，返回false。用行数作除数会在非方阵上错误映射，因此测试同时覆盖单行、单列及不同矩形尺寸。

空矩阵或零列矩形作为扩展返回false，进入除法前已检查列数。ragged行长度不一致的输入不承诺支持；生产代码不做O(mn)排序或形状验证，以维持本题复杂度。

独立oracle用两个循环逐元素扫描，不使用虚拟下标或二分。测试对行数、列数各1..3，枚举五个值−2..2上所有非递减序列，按尺寸重塑，再只保留跨行严格递增的合法矩阵。得到277个矩阵，每个查询−3..3，共1939次；含行内重复值。8个固定例子覆盖缺失、单元素、单列、行边界和值域两端；空矩阵与零列另有2个扩展。

100x100边界有两种：全部不同的行优先序列检查7个首尾、跨行和缺失目标；每行100个相等值、各行值递增时检查全部100个行值及两侧缺失值，共102次。两个最大尺寸合计109次，全部调用检查输入保持。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0074_search_matrix.cpp -o test_matrix
./test_matrix
```

B独立编写实现、证明与测试，OpenAI Codex辅助。返回false占位实现已经实际触发已存在目标的断言失败，最终运行结果另据日志记录。未向LeetCode提交，不声称Accepted。

最终本机验证：GCC16.2、C++17、`-O2 -Wall -Wextra -pedantic`，目标测试及完整分支25个程序均编译无诊断、运行退出0；独立完整评审无阻塞。实际输出：

```text
277 legal matrices / 1939 scan-oracle queries; 8 fixtures, 2 empty extensions and 109 maximum-shape queries passed; input unchanged
```

未向LeetCode提交。A后续实际补写另行核验，不提前共同署名。

## A实际补写与最终验证

A补写非方阵[[1,3,5],[7,9,11]]查找9的虚拟下标账本，列数固定为3：

| left / middle / right | middle对应(row,column) | 值与动作 |
| --- | --- | --- |
| 0 / 3 / 6 | (1,0) | 7<9，left=4 |
| 4 / 5 / 6 | (1,2) | 11>9，right=5 |
| 4 / 4 / 5 | (1,1) | 9命中 |

查找6时，mid=3的7使right=3，mid=1的3使left=2，mid=2的5使left=3，区间为空返回false。以行数2当除数会在mid=5映射到不存在的第2行，不能用只覆盖方阵的例子验证映射。

矩阵所有元素和target同时增加5，所有相等/大小关系及跨行严格递增保持，因此存在性不变。A只在矩阵非空且元素与target都不大于9995时应用，保证新值不超过10000；加正数不会越过−10000下界。1939个枚举查询、6个可变换固定例子、109个最大尺寸查询共2054次性质核验；2个空扩展与2个不满足数值上界的固定例子不变换。原逐元素扫描oracle保留，并单独检查平移后的矩阵没有被求解器改动。

A在本机Ubuntu WSL使用GCC15.2、C++17、`-O2 -Wall -Wextra -pedantic`实际编译新增性质后的精确测试，无诊断、运行退出0，未定义NDEBUG。测试文件LF SHA256 `7abcd039d7ebb7e96d05b4992bf6fbaff97cf4763c0b418eb590146d3edf187d`。上方GCC16.2/25程序结果属于B初稿阶段；A本次只运行本题，不冒充整条分支验证。

```text
2054 translationChecks passed; 277 legal matrices / 1939 scan-oracle queries; 8 fixtures, 2 empty extensions and 109 maximum-shape queries passed; input unchanged
```

A实际编写账本、证明与性质测试，双方贡献将整合为同一内容提交。未向LeetCode提交。
