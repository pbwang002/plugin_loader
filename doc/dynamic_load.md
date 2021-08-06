<!--
 * @Author: your name
 * @Date: 2021-08-06 16:03:23
 * @LastEditTime: 2021-08-06 16:04:01
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \plugin_loader\doc\dynamic_load.md
-->
# c++动态加载

## 动态库结构


## 动态库加载流程

### 打开动态库dlopen

  - 装载
  - 映射
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



