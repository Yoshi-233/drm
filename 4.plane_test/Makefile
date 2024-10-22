

# 变量定义
CC = gcc                     # 编译器
CFLAGS = -Wall              # 编译选项
TARGET = plane_test               # 可执行文件名称
# 定义变量SRCS，用来存放所有.c文件的文件名
SOURCES := $(wildcard *.c)

# 将SRCS中的.c后缀替换为空格，并赋值给变量OBJS
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))


# 默认目标
all: prepare $(TARGET) 

prepare:
	mkdir -p build

# 链接生成可执行文件
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ -L/usr/lib/x86_64-linux-gnu/ -ldrm
	mv $(TARGET) build/

# 编译源文件为目标文件
$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@ -I/usr/include/drm

# 清理目标
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean prepare  # 声明伪目标:
