#!/bin/bash

if [ $# -ne 2 ]; then
	echo "arm32-build-run.sh workspacefolder arm32filename"
	exit 1
fi

# 生成ARM32汇编语言
"$1/build/minic" -S -A -o "$1/tests/$2.s" "$1/tests/$2.c"

# 交叉编译程序成ARM32程序
arm-linux-gnueabihf-gcc -g -static --include "$1/tests/std.h" -o "$1/tests/$2" "tests/$2.s" "$1/tests/std.c"

echo "Now run gdb in another window"
echo "Now gdb start"

# 通过qemu运行，同时开启gdb server功能
qemu-arm-static -g 1145 "$1/tests/$2" < "$1/tests/test1-1.in"

echo
echo "Now gdb end"

exit 0