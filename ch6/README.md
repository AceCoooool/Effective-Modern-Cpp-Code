# ch6. lambda表达式

lambda式涉及的术语：

- lambda表达式，是表达式的一种。它是源代码组成部分
- 闭包是lambda式创建的**运行期**对象，根据不同的捕获模式，闭包会持有数据的副本或引用
- 闭包类就是实例化闭包的类。每个lambda式都会触发编译器生成一个独一无二的闭包类。而闭包中的语句会变成它的闭包类成员函数的可执行指令

> lambda式和闭包类存在于**编译期**，闭包存在于**运行期**

## 条款31：避免默认捕获模式

- 按引用的默认捕获会导致空悬指针的问题

  > 按引用捕获会导致闭包包含指涉到局部变量的引用，或者指涉到定义lambda式的作用域内的形参的引用。一旦由lambda式所创建的闭包越过了该局部变量或形参的声明期，那么闭包内的引用就会空悬
- 按值的默认捕获极易受空悬指针影响（尤其是this），并会误导地表面lambda是独立的

  > 按值捕获一个指针后，在lambda式创建的闭包中持有的是这个指针的副本，但你并无办法阻止lambda式之外的代码去对该指针实施delete操作所导致的指针副本空悬

> ① 捕获的[]里参数的含义
>
> - [] Capture nothing (or, a scorched earth strategy?) --- 不捕获任何变量
> - [&] Capture any referenced variable by reference --- 引用捕获
> - [=] Capture any referenced variable by making a copy --- 按值捕获
> - [=, &foo] Capture any referenced variable by making a copy, but capture variable foo by reference --- 拷贝与引用混合
> - [bar] Capture bar by making a copy; don’t copy anything else --- 指定引用或拷贝
> - [this] Capture the this pointer of the enclosing class --- 捕获this指针
>
> ② 显式地列出lambda式所依赖的局部变量或形参是更好的软件工程实践
>
> ③ 捕获只能针对在创建lambda式的作用域内**可见**的**非静态局部变量**（包括形参）
>
> ④ C++14中引入了"广义lambda捕获"：`[a=b](){...}`（也叫"初始化捕获"）
>
> ⑤ 静态存储期对象定义在全局或名字空间作用域中，又或在类中，在函数中，在文件中以static修饰词声明，这样的对象可以在lambda内使用，但是它们不能被捕获。

## 条款32：使用初始化捕获将对象移入闭包

- 使用C++14的**初始化捕获**将对象移入闭包
- 在C++11中，经由手工实现的类或std::bind去模拟初始化捕获


> ① 使用初始化捕获，你可以指定：
>
> 1. 由lambda生成的闭包类中的成员变量的名字
> 2. 一个表达式，用以初始化该成员变量
>
> ② 初始化捕获：`[pw=move(pw)](){xxx}`：其中"="左侧是你所指定的闭包类成员变量的名字，"="右侧的则是其初始化表达式（"="左右两侧的位于不同的作用域）
>
> ③ 在C++11中按移动捕获可以采用下述方式进行模拟：
>
> 1. 把需要捕获的对象移动到std::bind产生的函数对象中
> 2. 给到lambda式一个指涉到欲"捕获"对象的引用
>
> ④ 一些基础知识
>
> - 移动构造一个对象进入C++11闭包是不可能实现的，但移动构造一个对象进入绑定对象则是可能实现的
> - 欲在C++11中模拟移动捕获包括以下步骤：先移动构造一个对象进入绑定对象，然后按引用把该移动构造所得的对象传递给lambda式
> - 因为绑定对象的生命期和闭包相同，所以针对绑定对象中的对象和闭包里的对象可以采用同样手法加以处置

## 条款33：对auto&&类型的形参使用decltype，并用std::forward将其传给其他函数

- 对`auto&&`类型的形参使用`decltype`，并采用`std::forward`将其传给其他函数

> 例如：
>
> ```cpp
> auto f=[](auto&& param){ return func(normalize(std::forward<decltype(param)>(param))); }
> ```

> ① lambda可以在形参规格中使用auto：即闭包类中的`operator()`采用模板实现

## 条款34：优先选用lambda式，而非std::bind

- lambda式比起使用std::bind而言，可读性更好，表达能力更强，可能运行效率也更高
- 仅在C++11中，std::bind在实现移动捕获，或者绑定到具体模板化的函数调用运算符的对象的场合中，可能尚有余热可以发挥（但C++14中，std::bind已经彻底失去了用武之地）

> ① 绑定(bind)对象的所有实参都是按引用传递的，因此此种对象的函数调用运算符利用了完美转发