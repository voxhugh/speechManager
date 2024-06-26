# 基于STL的演讲比赛流程管理系统



### 管理类、菜单、退出

1. 创建演讲比赛流程管理源文件，提供主函数接口
2. 创建演讲管理类：提供菜单界面，控制演讲比赛流程，进行文件读写交互。构造析构空实现
3. 演讲管理类里扩展展示菜单功能，主函数调用
4. 主函数循环调用菜单界面，接收用户输入
5. 管理类里扩展退出系统功能



### 演讲比赛

1. 创建选手类，包含两个属性：姓名、得分数组（记录最多两轮的比赛成绩）
2. 管理类里添加属性：三个vector容器，分别存放第一轮、第二轮以及获胜选手；map容器，存放编号选手键值对；整形变量，记录比赛轮数
3. 扩展初始化属性的函数：保证容器为空，轮数默认1。构造调用
4. 扩展创建选手函数：创建12名选手存入map容器里。构造调用
5. 扩展开始比赛函数：控制整个比赛流程
6. 扩展抽签函数：依轮数进分支洗牌
7. 菜单调用开始比赛，比赛调用抽签
8. 扩展比赛函数
9. 依轮数索引声明正式比赛开始
10. 准备编号容器依轮数索引指向对应容器
11. 准备<double,int,Greater<double>>临时容器，准备记录遍历人数的属性
12. 循环遍历编号容器
13. 每次循环创建deque容器，(600～1000)/10.f遍历10次，依次存入评委打分
14. deque降序排列后去头去尾
15. 获取累加总分，求得平均分存入维护的<int,Speaker>容器
16. 每次循环将分数，编号存入<double,int>容器
17. 每遍历6个人，开始降序遍历小组容器打印当前轮小组的比赛名次
18. 再次遍历前三名，依轮数索引将入选编号存入下一轮容器中，清空小组容器
19. 依轮数索引声明比赛完毕
20. 扩展显示比赛结果的函数
21. 依轮数索引取晋级选手容器，遍历显示信息
22. 第二轮：同上，轮数索引自增后，抽签、比赛、显示结果
23. 扩展保存记录的函数。流程调用
24. 文件输出流以out｜app方式保存到./speech.csv
25. 遍历获胜数组保存编号分数，逗号分割
26. 关闭，声明记录已保存
27. 声明本届比赛完毕



### 查看记录

1. 添加文件是否为空标志，添加往届记录容器<int,vector<string>>
2. 扩展读取记录的函数。构造调用
3. ifs读文件，判断文件不存在
4. 读一个字符检定是否为eof，判断文件为空
5. 文件不为空，putback读回首字符
6. 准备一个记录届数的索引
7. 准备一个接收数据的字符串，ifs循环读入
8. 准备两个整形分别记录逗号pos和start，一个vector容器记录一届6个数据
9. 死循环从start开始查到逗号位置更新到pos，找不到则退出
10. 找到后从start开始截pos-start长度的子串
11. 将子串存入vector，更新start为pos的下一个位置
12. 将<index,v>存入维护的往届记录容器
13. 届数自增后关闭对象
14. 扩展显示记录的函数。菜单调用
15. 遍历map容器输出每届的冠亚季军编号及得分
16. 下面优化解决bug
17. 查看往届记录时添加文件不存在或记录为空的提示
18. 记录保存完毕更新文件存在标志
19. 比赛完毕重新调用构造里函数的调用，保证实时更新
20. 初始化函数里清空记录容器
21. 主函数里添加随机数种子



### 清空记录

1. 扩展清空记录的函数。菜单调用
2. 用户二次确认后trunc方式打开文件
3. 重新调用构造里函数的调用，实时更新
4. 声明清空成功