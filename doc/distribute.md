## 架构
### 概念分析
- 软件定义：有关软件整体架构和组件的抽象描述，用于指导大型软件系统方面的设计；软件架构包括软件组件、组件之间的关系，组件特性以及组件关系的特性；
- 在UML中，架构被认为是系统的组织结构和相关行为。
  - 架构可以被分解为通过接口互相关联的部分，以及相互作用；
  - 通过接口互相作用的部分包括类、组件和子系统；这样可以通过uml的各种架构图来描述这些对象和关系，从而表达清楚一个系统的结构；
- 概念：
```
模式：uml解释，对普遍问题的普遍解决方案；
库：工具箱；
框架：一套通用的解决方案；
架构：高度抽象的需求，是系统中的不变量；
平台：所有可能做的事的集合；
模块：系统或者业务按照特定维度的一种切分；订单模块，服务管理模块
组件：一组可以复用的业务功能的集合，包含一些对象及其行为；粒度小于模块，注册中心组件；
服务：一组对外提供业务能力的功能，需要明确的接口方式，rest，grpc；
```
- 问题：
1. 模块和组件的区别？从模块划分角度，注册中心插件，属于服务管理模块的一部分，注册中心客户端、注册中心服务端共同构成服务管理模块；注册中心服务端属于服务管理模块的一个服务端组件；
- 引用：
https://www.jianshu.com/p/df295f92fb52
- 其他
编程语言的演进，架构的演进，目的是让软件拥抱变化，让软件在封装性（高内聚）和模块化（低耦合）两个方向同时演进；
### 架构风格vs架构模式vs设计模式
- 对比分析
- 架构风格是最高抽象级别的应用设计；
  - 基于组件
  - 单体应用
  - 分层
  - 管道和过滤器
  - 事件驱动
  - 发布订阅
  - 插件
  - 客户端服务器
  - 面向服务 SOA
- 架构模式是实现架构风格的一种方式；
解决仿佛出现问题的常见方案就是模式；
  - 三层架构
  - 微内核
  - MVC
  - MVVM
- 设计模式是解决局部问题的方法；
- 总结
  - 架构风格可以有多种实现方式，拥有特定的技术环境以及特定的策略、工具和实践；
  - 模式既可以用作指定对象的架构模式也可以用作它的设计模式，还是根据我们使用它的范围而定。
- 引用文章
1. https://docs.microsoft.com/en-us/previous-versions/msp-n-p/ee658117(v=pandp.10)?redirectedfrom=MSDN
2. https://stackoverflow.com/questions/3958316/whats-the-difference-between-architectural-patterns-and-architectural-styles
3. https://en.wikipedia.org/wiki/List_of_software_architecture_styles_and_patterns
4. https://www.jianshu.com/p/d8dce27f279f
5. [微内核架构]（https://cloud.tencent.com/developer/article/1768675）
6. [微内核架构]（https://xiaojun90.github.io/blog/architecture/1030.html#%E7%AE%80%E4%BB%8B）
### 发展历程
  单体架构
  分层架构
  SOA
  微服务
  mesh

### 单体架构

#### 简单单体架构

#### MVC架构及其变种
- 一般的MVC架构
- MVP
- MVVM

分布式架构

SOA

AOP

分布式核心技术

服务运维

容器

kubernetes


## 参看文档
- https://zh.m.wikipedia.org/zh/%E8%BD%AF%E4%BB%B6%E6%9E%B6%E6%9E%84
- [软件架构编年史](https://www.jianshu.com/p/b477b2cc6cfa)
- https://herbertograca.com/2017/07/03/the-software-architecture-chronicles/