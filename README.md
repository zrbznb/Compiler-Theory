

./build/minic -S -T -o ./tests/test1-1.png ./tests/test1-1.c

./build/minic -S -T -A -o ./tests/test1-1.png ./tests/test1-1.c

./build/minic -S -T -D -o ./tests/test1-1.png ./tests/test1-1.c

./build/minic -S -I -o ./tests/test1-1.ir ./tests/test1-1.c

./build/minic -S -I -A -o ./tests/test1-1.ir ./tests/test1-1.c

./build/minic -S -I -D -o ./tests/test1-1.ir ./tests/test1-1.c

./build/minic -S -o ./tests/test1-1.s ./tests/test1-1.c

./build/minic -S -A -o ./tests/test1-1.s ./tests/test1-1.c

./build/minic -S -D -o ./tests/test1-1.s ./tests/test1-1.c

```

## 1.7. 工具

本实验所需要的工具或软件在实验一环境准备中已经安装，这里不需要再次安装。

这里主要介绍工具的功能。

### 1.7.1. Flex 与 Bison

```shell
flex -o MiniCFlex.cpp --header-file=MiniCFlex.h minic.l
bison -o MinicBison.cpp --header=MinicBison.h -d minic.y
```

请注意 bison 的--header 在某些平台上可能是--defines，要根据情况调整指定。

### 1.7.2. Antlr 4.12.0

要确认java15 以上版本的 JDK，否则编译不会通过。默认已经安装了JDK 17的版本。

编写 g4 文件然后通过 antlr 生成 C++代码，用 Visitor 模式。

```shell
java -jar tools/antlr-4.12.0-complete.jar -Dlanguage=Cpp -no-listener -visitor -o frontend/antlr4 frontend/antlr4/minic.g4
```

C++使用 antlr 时需要使用 antlr 的头文件和库，默认的环境已经安装。

### 1.7.3. Graphviz

借助该工具提供的C语言API实现抽象语法树的绘制。

### 1.7.4. doxygen

借助该工具分析代码中的注释，产生详细分析的文档。这要求注释要满足一定的格式。具体可参考实验文档。

### 1.7.5. texlive

把doxygen生成的文档转换成pdf格式。

## 1.8. 根据注释生成文档

请按照实验的文档要求编写注释，可通过doxygen工具生成网页版的文档，借助latex可生成pdf格式的文档。

请在本实验以及后续的实验按照格式进行注释。

执行的下面的命令后会在doc文件夹下生成html和latex文件夹，通过打开index.html可浏览。

```shell
doxygen Doxygen.config
```

在安装texlive等latex工具后，可通过执行的下面的命令产生refman.pdf文件。

```shell
cd doc/latex
make
```

## 1.9. 实验运行

tests 目录下存放了一些简单的测试用例。

由于 qemu 的用户模式在 Window 系统下不支持，因此要么在真实的开发板上运行，或者用 Linux 系统下的 qemu 来运行。

### 1.9.1. 调试运行

由于默认的gdb或者lldb调试器对C++的STL模版库提供的类如string、map等的显示不够友好，
因此请大家确保安装vadimcn.vscode-lldb插件，也可以更新最新的代码后vscode会提示安装推荐插件后自动安装。

如安装不上请手动下载后安装，网址如下：
<https://github.com/vadimcn/codelldb/releases/>

调试运行配置可参考.vscode/launch.json中的配置。

### 1.9.2. 生成中间IR(DragonIR)与运行

前提需要下载并安装IRCompiler工具。

```shell
# 翻译 test1-1.c 成 ARM32 汇编
./build/minic -S -I -o tests/test1-1.ir tests/test1-1.txt
./IRCompiler -R tests/test1-1.ir
```

第一条指令通过minic编译器来生成的汇编test1-1.ir
第二条指令借助IRCompiler工具实现对生成IR的解释执行。

### 1.9.3. 生成 ARM32 的汇编

```shell
# 翻译 test1-1.c 成 ARM32 汇编
./build/minic -S -o tests/test1-1.s tests/test1-1.c
# 把 test1-1.c 通过 arm 版的交叉编译器 gcc 翻译成汇编
arm-linux-gnueabihf-gcc -S -o tests/test1-1-1.s tests/test1-1.c
```

第一条命令通过minic编译器来生成的汇编test1-1.s
第二条指令是通过arm-linux-gnueabihf-gcc编译器生成的汇编语言test1-1-1.s。

在调试运行时可通过对比检查所实现编译器的问题。

### 1.9.4. 生成可执行程序

通过 gcc 的 arm 交叉编译器对生成的汇编进行编译，生成可执行程序。

```shell
# 通过 ARM gcc 编译器把汇编程序翻译成可执行程序，目标平台 ARM32
arm-linux-gnueabihf-gcc -static -g -o tests/test1-1 tests/test1-1.s
# 通过 ARM gcc 编译器把汇编程序翻译成可执行程序，目标平台 ARM32
arm-linux-gnueabihf-gcc -static -g -o tests/test1-1-1 tests/test1-1-1.s
```

有以下几个点需要注意：

1. 这里必须用-static 进行静态编译，不依赖动态库，否则后续通过 qemu-arm-static 运行时会提示动态库找不到的错误
2. 可通过网址<https://godbolt.org/>输入 C 语言源代码后查看各种目标后端的汇编。下图是选择 ARM GCC 11.4.0 的源代码与汇编对应。

![godbolt 效果图](./doc/figures/godbolt-test1-1-arm32-gcc.png)

### 1.9.5. 运行可执行程序

借助用户模式的 qemu 来运行，arm 架构可使用 qemu-arm-static 命令。

```shell
qemu-arm-static tests/test1-1
echo $?
qemu-arm-static tests/test1-1-1
echo $?
```

这里可比较运行的结果(即通过指令echo $?获取main函数的返回值，注意截断8位的无符号整数)，如果两者不一致，则编写的编译器程序有问题。

如果测试用例源文件程序需要输入，假定输入的内容在文件A.in中，则可通过以下方式运行。

```shell
qemu-arm-static tests/test1-1 < A.in
echo $?
qemu-arm-static tests/test1-1-1 < A.in
echo $?
```

如果想把输出的内容写到文件中，可通过重定向符号>来实现，假定输入到B.out文件中。

```shell
qemu-arm-static tests/test1-1 < A.in > A.out
echo $?
qemu-arm-static tests/test1-1-1 < A.in > A.out
echo $?
```

## 1.10. qemu 的用户模式

qemu 的用户模式下可直接运行交叉编译的用户态程序。这种模式只在 Linux 和 BSD 系统下支持，Windows 下不支持。
因此，为便于后端开发与调试，请用 Linux 系统进行程序的模拟运行与调试。

## 1.11. qemu 用户程序调试

### 1.11.1. 安装 gdb 调试器

该软件 gdb-multiarch 在前面工具安装时已经安装。如没有，则通过下面的命令进行安装。

```shell
sudo apt-get install -y gdb-multiarch
```

### 1.11.2. 启动具有 gdbserver 功能的 qemu

假定通过交叉编译出的程序为 tests/test1-1，执行的命令如下：

```shell
# 启动 gdb server，监视的端口号为 1234
qemu-arm-static -g 1234 tests/test1-1
```

其中-g 指定远程调试的端口，这里指定端口号为 1234，这样 qemu 会开启 gdb 的远程调试服务。

### 1.11.3. 启动 gdb 作为客户端远程调试

建议通过 vscode 的调试，选择 Qemu Debug 进行调试，可开启图形化调试界面。

可根据需要修改相关的配置，如 miDebuggerServerAddress、program 等选项。

也可以在命令行终端上启动 gdb 进行远程调试，需要指定远程机器的主机与端口。

注意这里的 gdb 要支持目标 CPU 的 gdb-multiarch，而不是本地的 gdb。

```shell
gdb-multiarch tests/test1-1
# 输入如下的命令，远程连接 qemu 的 gdb server
target remote localhost:1234
# 在 main 函数入口设置断点
b main
# 继续程序的运行
c
# 之后可使用 gdb 的其它命令进行单步运行与调试
```

在调试完毕后前面启动的 qemu-arm-static 程序会自动退出。因此，要想重新调试，请启动第一步的 qemu-arm-static 程序。

## 1.12. 源程序打包

在执行前，请务必通过cmake进行build成功，这样会在build目录下生成CPackSourceConfig.cmake文件。

进入build目录下执行如下的命令可产生源代码压缩包，用于实验源代码的提交

```shell
cd build
cpack --config CPackSourceConfig.cmake
```

在build目录下默认会产生zip和tar.gz格式的文件。

可根据需要调整CMakeLists.txt文件的CPACK_SOURCE_IGNORE_FILES用于忽略源代码文件夹下的某些文件夹或者文件。

## 1.13. 二进制程序打包

可在VScode页面下的状态栏上单击Run Cpack即可在build产生zip和tar.gz格式的压缩包，里面包含编译出的可执行程序。

## 1.14 IR的类型组织图

如下图所示，描述的是Value、User、Use、Instruction等的类图。

![IR的类图](doc/figures/Value-User-Use.svg)

有关类型的类图如下图所示。

![Type的类图](./doc/figures/Type类.png)

## 1.15 VSCode中使用Antlr4

具体可阅读[Antlr4使用](doc/Antlr4.md)。

