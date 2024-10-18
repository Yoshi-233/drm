

# 变量定义
CC = gcc                     # 编译器
CFLAGS = -Wall              # 编译选项
TARGET = page_flip               # 可执行文件名称
SOURCES = *.c            # 源文件
OBJECTS = $(SOURCES:.c=.o)  # 生成的目标文件


# 默认目标
all: prepare $(TARGET) 

prepare:
	mkdir -p build

# 链接生成可执行文件
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ -L/usr/lib/x86_64-linux-gnu/ -ldrm
	mv $(TARGET) build/

# 编译源文件为目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I/usr/include/drm

# 清理目标
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean prepare  # 声明伪目标:
