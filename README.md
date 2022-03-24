# SLC_SysY_Language_Compiler

## 一、介绍

华为毕昇杯。SysY语言编译器。

### 1、环境
1. flex v2.6.4
2. bison v3.0.4
3. cmake 3.10.2

### 2、 构建方法
1. 进入项目根文件路径
2. 执行命令：cmake . && make
3. 编译命令（程序运行）：./compiler test.sy -o a.s

项目构建后，在/build路径下生成名为compiler的可执行程序。使用3中的编译命令，对名为test.sy的Sysy语言源文件进行编译，生成armv7的汇编代码a.s

## 二、软件架构

| 文件夹 | 阶段 | 功能 |
| ---- | ---- | ---- |
| front | 前端处理 | 预处理、词法分析、语法分析 |
| ir | 中间代码生成 | 语义分析、报错，采用LLVM格式IR |
| codegen | 最终代码生成 | 生成最终指令 |

前端完成预处理、词法分析、语法分析功能。使用flex、bison设计实现。前端会向后端提供一颗ast语法树，树的结构在./src/ast文件夹下定义。在./src/ast中提供了JsonGen.hpp、JsonGen.cpp的方法，以方便调试。

./src/ir文件夹下是中间代码生成的代码，完成语义分析、中间代码生成的功能。采用LLVM格式的中间代码，并在此之后添加代码优化的代码。这部分的代码设计参考了中科大的实现思路和开源LLVM编译器的代码实现。IrGen.cpp驱动整个程序的运行，以Block作为代码生成和处理的单位。其它的代码完成相应的IR生成等功能。

最终代码生成完成从IR到最终armv7汇编的生成。比赛中的树莓派CPU有16个寄存器，分别为r0-r15。定义其中的特定编号寄存器为pc、sp、lr等特殊用途寄存器。根据ir中生成的中间代码，进行翻译即生成最终代码。考虑到开发效率，近期我们以文件格式作为ir、codegen的接口，但目前整合的工作还未全部完成。

## 三、参考资料

1. [比赛官方网站](https://course.educg.net/sv2/indexexp/contest/contest.jsp?doVisit=true&contestID=veDBbQeZ_cs&my=false&contestCID=0)

2. [build-a-compiler-within-30-days](https://github.com/jiweixing/build-a-compiler-within-30-days)

3. [中国科学技术大学 燃烧我的编译器](https://github.com/mlzeng/CSC2020-USTC-FlammingMyCompiler)

4. [清华大学 编程是一件很危险的事](https://github.com/TrivialCompiler/TrivialCompiler)