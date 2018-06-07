# ch6. lambda表达式



## 条款31：避免默认捕获模式

- 按引用的默认捕获会导致空悬指针的问题
- 按值的默认捕获极易受空悬指针影响（尤其是this），并会误导地表面lambda是独立的

> - [] Capture nothing (or, a scorched earth strategy?) --- 不捕获任何变量
> - [&] Capture any referenced variable by reference --- 拷贝捕获
> - [=] Capture any referenced variable by making a copy --- 引用捕获
> - [=, &foo] Capture any referenced variable by making a copy, but capture variable foo by reference --- 拷贝与引用混合
> - [bar] Capture bar by making a copy; don’t copy anything else --- 指定引用或拷贝
> - [this] Capture the this pointer of the enclosing class --- 捕获this指针

## 条款32：使用初始化捕获将对象移入闭包

- 使用C++14的初始化捕获将对象移入闭包
- 在C++11中，经由手工实现的类或std::bind去模拟初始化捕获


## 条款33：对auto&&类型的形参使用decltype，并用std::forward将其传给其他函数

- 对`auto&&`类型的形参使用`decltype`，并采用`std::forward`将其传给其他函数

> 例如：
>
> ```cpp
> auto f=[](auto&& param){ return func(normalize(std::forward<decltype(param)>(param))); }
> ```

## 条款34：优先选用lambda式，而非std::bind

- lambda式比起使用std::bind而言，可读性更好，表达能力更强，可能运行效率也更高
- 仅在C++11中，std::bind在实现移动捕获，或者绑定到具体模板化的函数调用运算符的对象的场合中，可能尚有余热可以发挥（但C++14中，std::bind已经彻底失去了用武之地）