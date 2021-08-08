

# c++动态加载
## 前提
### 静态链接和动态链接的区别
- 静态链接
  - 假如采用静态链接，两个进程proc1和proc2分别包含proc1.o和proc2.o，都依赖模块add.o；
  - 当两个进程运行时，内存里和物理磁盘里都有两份add.o；结构如下：
  ```plantuml
  @startuml
  database "memory" {
    folder "proc1_mem" {
      [proc1.o]
      [add.o]
    }
    folder "proc2_mem" {
      [proc2.o]
      [ add.o]
    }
  }
  component "physical" {
    folder "proc1_phy" {
      [ proc1.o]
      [  add.o]
    }
    folder "proc2_phy" {
      [ proc2.o]
      [   add.o]
    }
  }
  [add.o] ..> [  add.o]
  [ add.o] ..> [   add.o]
  @enduml
  ```
- 动态链接
  - 假如两个进程采用动态链接，两个进程proc1和proc2分别包含proc1.o和proc2.o，都依赖模块add.o
  - 当两个进程运行时，内存和物理磁盘里都只有一份add.o，结构如下：
  ```plantuml
  @startuml
  database "memory" {
    folder "proc1_mem" {
      [proc1.o]
    }
    folder "proc2_mem" {
      [proc2.o]
    }
    folder "libAdd.so" {
      [add.o]
    }
  }
  component "physical" {
    folder "proc1_phy" {
      [ proc1.o]
    }
    folder "proc2_phy" {
      [ proc2.o]
    }
    folder "libAdd.so_phy" {
      [ add.o]
    }
  }
  [proc1.o] ..> [ proc1.o]
  [proc2.o] ..> [ proc2.o]
  [add.o] ..> [ add.o]
  @enduml
  ```

### 动态库好处和问题
- 节约了内存和磁盘空间，多进程可以复用同一个共享库，只占一份内存和磁盘空间【对于全局变量和静态变量，每个进程都保存了一个副本】
- 依据动态库的特性，制作插件
- 提供了跨平台的兼容性能力，保证接口一致，在不同的平台链接不同动态即可，动态链接能力，相当于在程序和操作系统之间添加了一个中间层，消除依赖差异
- 问题，当程序依赖的模块更新后，导致了新老版本不兼容问题，导致core dump；【缺少动态库的版本管理机制】

## 动态链接流程
- 例子
```plantuml
@startuml
(*) --> add.cpp
add.cpp -->[compiler] add.o
"C/C++ runtime library（libc.so/libstdc++.so）" -> Linker
add.o --> Linker
Linker --> add.so

main.cpp ->[compiler] main.o
main.o-> linker
add.so --> linker
linker -> process(run_time)
@enduml
```
- 流程分析
  - 将add.cpp编译生成add.o
  - 将依赖的c/c++运行时库链接进来，生成`add.so`
  - main.cpp编译生成main.o
  - main函数依赖add.o，将add.so链接进来生成可执行文件
- 问题
  - 为什么可执行文件，在链接时要依赖add.so呢？
    - 将main.cpp编译成main.o时，编译器还不知道函数Add的地址
    - 将main.o链接成可执行文件时，链接器必须确定函数Add的性质
      - 如果是静态，则main.o需要将对Add的地址引用进行重定位
      - 如果是动态共享对象中的函数，则只是将函数标记为动态链接的符号
    - add.so中保存了完整的信息，链接器可以从中获取函数Add是一个动态符号
### 动态库运行时空间分布
#### 动态库运行时分布
```
cat /proc/5560/maps
7fb9715b0000-7fb9715b3000 rw-p 00000000 00:00 0
7fb9715c0000-7fb9715c2000 rw-p 00000000 00:00 0
7fb9715d1000-7fb9715e0000 r--p 00000000 00:00 382267             /usr/lib/x86_64-linux-gnu/libm-2.31.so
7fb9715e0000-7fb971687000 r-xp 0000f000 00:00 382267             /usr/lib/x86_64-linux-gnu/libm-2.31.so
7fb971687000-7fb97171e000 r--p 000b6000 00:00 382267             /usr/lib/x86_64-linux-gnu/libm-2.31.so
7fb97171e000-7fb97171f000 r--p 0014c000 00:00 382267             /usr/lib/x86_64-linux-gnu/libm-2.31.so
7fb97171f000-7fb971720000 rw-p 0014d000 00:00 382267             /usr/lib/x86_64-linux-gnu/libm-2.31.so
7fb971720000-7fb971745000 r--p 00000000 00:00 382032             /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fb971745000-7fb9718bd000 r-xp 00025000 00:00 382032             /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fb9718bd000-7fb971907000 r--p 0019d000 00:00 382032             /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fb971907000-7fb971908000 ---p 001e7000 00:00 382032             /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fb971908000-7fb97190b000 r--p 001e7000 00:00 382032             /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fb97190b000-7fb97190e000 rw-p 001ea000 00:00 382032             /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fb97190e000-7fb971912000 rw-p 00000000 00:00 0
7fb971920000-7fb971923000 r--p 00000000 00:00 382142             /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7fb971923000-7fb971935000 r-xp 00003000 00:00 382142             /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7fb971935000-7fb971939000 r--p 00015000 00:00 382142             /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7fb971939000-7fb97193a000 r--p 00018000 00:00 382142             /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7fb97193a000-7fb97193b000 rw-p 00019000 00:00 382142             /usr/lib/x86_64-linux-gnu/libgcc_s.so.1
7fb971940000-7fb9719d6000 r--p 00000000 00:00 382441             /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fb9719d6000-7fb971ac6000 r-xp 00096000 00:00 382441             /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fb971ac6000-7fb971b0f000 r--p 00186000 00:00 382441             /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fb971b0f000-7fb971b10000 ---p 001cf000 00:00 382441             /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fb971b10000-7fb971b1b000 r--p 001cf000 00:00 382441             /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fb971b1b000-7fb971b1e000 rw-p 001da000 00:00 382441             /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fb971b1e000-7fb971b21000 rw-p 00000000 00:00 0
7fb971b30000-7fb971b31000 r--p 00000000 00:00 381915             /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fb971b31000-7fb971b53000 r-xp 00001000 00:00 381915             /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fb971b53000-7fb971b54000 r-xp 00023000 00:00 381915             /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fb971b54000-7fb971b5b000 r--p 00024000 00:00 381915             /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fb971b5b000-7fb971b5c000 r--p 0002b000 00:00 381915             /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fb971b5d000-7fb971b5e000 r--p 0002c000 00:00 381915             /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fb971b5e000-7fb971b5f000 rw-p 0002d000 00:00 381915             /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fb971b5f000-7fb971b62000 rw-p 00000000 00:00 0
7fb971b68000-7fb971b69000 r--p 00000000 00:00 38686              /mnt/d/code/code_hub/plugin_loader/build/lib/libadd.so
7fb971b69000-7fb971b6a000 r-xp 00001000 00:00 38686              /mnt/d/code/code_hub/plugin_loader/build/lib/libadd.so
7fb971b6a000-7fb971b6b000 r--p 00002000 00:00 38686              /mnt/d/code/code_hub/plugin_loader/build/lib/libadd.so
7fb971b6b000-7fb971b6c000 r--p 00002000 00:00 38686              /mnt/d/code/code_hub/plugin_loader/build/lib/libadd.so
7fb971b6c000-7fb971b6d000 rw-p 00003000 00:00 38686              /mnt/d/code/code_hub/plugin_loader/build/lib/libadd.so
7fb971b6d000-7fb971b6e000 r--p 00000000 00:00 38699              /mnt/d/code/code_hub/plugin_loader/build/bin/run_test
7fb971b6e000-7fb971b6f000 r-xp 00001000 00:00 38699              /mnt/d/code/code_hub/plugin_loader/build/bin/run_test
7fb971b6f000-7fb971b70000 r-xp 00002000 00:00 38699              /mnt/d/code/code_hub/plugin_loader/build/bin/run_test
7fb971b70000-7fb971b71000 r--p 00003000 00:00 38699              /mnt/d/code/code_hub/plugin_loader/build/bin/run_test
7fb971b72000-7fb971b73000 r--p 00004000 00:00 38699              /mnt/d/code/code_hub/plugin_loader/build/bin/run_test
7fb971b73000-7fb971b74000 rw-p 00005000 00:00 38699              /mnt/d/code/code_hub/plugin_loader/build/bin/run_test
7fffe6d7b000-7fffe6d9c000 rw-p 00000000 00:00 0                  [heap]
7fffeeb2a000-7fffef32a000 rw-p 00000000 00:00 0                  [stack]
7fffef5e7000-7fffef5e8000 r-xp 00000000 00:00 0                  [vdso]
```
- 分析
  - 进程的虚拟地址空间中，多了几个文件映射
  - 依赖的c语言运行时库libc.so和c++运行时库libstdc++.so
  - ld.so，动态链接器，程序启动时，由于依赖了Add.so等动态库，还无法直接执行，需要先将控制权交给链接器链接
  - 当依赖的库全部加载完成后，则将控制权交给run_time程序执行入口

#### 动态库结构
- 查看头信息，其中`[Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]`为链接器地址
```
readelf -l ../bin/run_test

Elf file type is DYN (Shared object file)
Entry point 0x11e0
There are 13 program headers, starting at offset 64

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  PHDR           0x0000000000000040 0x0000000000000040 0x0000000000000040
                 0x00000000000002d8 0x00000000000002d8  R      0x8
  INTERP         0x0000000000000318 0x0000000000000318 0x0000000000000318
                 0x000000000000001c 0x000000000000001c  R      0x1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000b58 0x0000000000000b58  R      0x1000
  LOAD           0x0000000000001000 0x0000000000001000 0x0000000000001000
                 0x00000000000013e5 0x00000000000013e5  R E    0x1000
  LOAD           0x0000000000003000 0x0000000000003000 0x0000000000003000
                 0x0000000000000e43 0x0000000000000e43  R      0x1000
  LOAD           0x0000000000004cf8 0x0000000000005cf8 0x0000000000005cf8
                 0x0000000000000320 0x0000000000000328  RW     0x1000
  DYNAMIC        0x0000000000004d18 0x0000000000005d18 0x0000000000005d18
                 0x0000000000000230 0x0000000000000230  RW     0x8
  NOTE           0x0000000000000338 0x0000000000000338 0x0000000000000338
                 0x0000000000000020 0x0000000000000020  R      0x8
  NOTE           0x0000000000000358 0x0000000000000358 0x0000000000000358
                 0x0000000000000044 0x0000000000000044  R      0x4
  GNU_PROPERTY   0x0000000000000338 0x0000000000000338 0x0000000000000338
                 0x0000000000000020 0x0000000000000020  R      0x8
  GNU_EH_FRAME   0x0000000000003054 0x0000000000003054 0x0000000000003054
                 0x00000000000002b4 0x00000000000002b4  R      0x4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     0x10
  GNU_RELRO      0x0000000000004cf8 0x0000000000005cf8 0x0000000000005cf8
                 0x0000000000000308 0x0000000000000308  R      0x1
```


## 动态库加载流程
### 自举
### 装载
### 重定位和初始化
#### 重定位
- GOT表
- PLT
- 问题
  - 共享模块的全局变量问题
    - 多进程，共享数据段，共享内存
    - 多线程，访问不同的全局变量副本，thread_local
### 打开动态库dlopen

  - 装载
  - 重定位
  - 加载模块时，会执行`.init`段代码，完成模块的初始化工作

### 查找符号dlsym

- 基本操作
  - 如果是函数，返回函数的地址
    - 如果是变量，返回变量的地址
    - 如果是常量，返回常量的值
  - 查看符号
    - objdump -t
- 符号优先级
  - 装载优先(dlopen)：当多个同名符合冲突时，先装入的符号优先
  - 依赖序列(dlsym)：进行符号查找时，以dlopen打开的对象为根节点，进行广度优先遍历，直到找到符号位置

- 

### 错误处理

### 关闭动态库





## 原理



