# ch3. 转向现代C++

## 条款7. 在创建对象时注意区分()和{}

- 大括号初始化可以应用的语境最为宽泛，且可以阻止隐式窄化类型转换（宽化不阻止）。还对解析语法免疫（指的是函数声明还是创建对象可能引起的歧义）
- 在构造函数重载期间，只要有任何可能，大括号初始化就会与`std::initializer_list`类型的形参相匹配，即使其他重载版本有着更加匹配的形参表。（**这点请多留意**）
- 使用小括号还是大括号，会造成大相径庭结果的例子为：使用连个实参来创建`vector<int>`对象 --- `vector<int> a(3, 2)`: 对应3个元素，每个均为2； `vector<int> a{3, 2}`: 对应2个元素，分别为3和2。（说实话，这些在文档里面都写得很清楚了，一般不会出错）
- 在用模板内容进行对象创建时，到底应该使用小括号还是大括号会成为一个棘手问题。

> 作者给出的建议是：选择()或{}并坚持下去

## 条款8. 优先选用nullptr，而非0或NULL

其实可以说的更绝对一点：不要用0或NULL代表空指针，请用nullptr

- 0和NULL都不具备指针类型（因此不能作为指针参数）
- 避免在整型和指针类型之间重载（如：`void func(int)`和`void func(void *)` --- 其实都是为了照顾0或NULL的情况）

> nullptr实际类型为`nullptr_t`，且类型`nullptr_t`可以隐式转换到所有的裸指针类型！

## 条款9. 优先选用别名声明(using)，而非typedef

- `typedef`不支持模板化，但别名声明(`using`)支持（`typedef`需要封装到类中来实现模板化）
- 别名模板可以让人避免写`::type`后缀，并且在模板内，对于内嵌`typedef`的引用经常要求加上`typename`前缀（这是因为依赖名导致的---可以详见[typename](http://feihu.me/blog/2014/the-origin-and-usage-of-typename/))）

> 在C++11中很多模板别名还是利用`typedef`获得的，因此经常需要加上`typename`。（C++14都有对应的别名模板了），但可以对C++11中的情况采用下述方式：
>
> ```cpp
> template<class T>
> using remove_const_t = typename remove_const<T>::type
> ```

## 条款10. 优先选用限定作用域的枚举类型，而非不限作用域的枚举类型

> 还是坚持只用限定作用域的枚举类型吧，主要优点：
>
> - 降低命名空间污染
> - 强类型的
> - 可以进行前置声明

限定作用域的枚举类型：`enum class Color{black, white, red};`

不限定作用域的枚举类型：`enum Color{black, white, red};`

- C++98风格的枚举类型，现在称为不限定范围的枚举类型
- 限定作用域的枚举类型仅在枚举类内可见。它们只能通过强制类型转换转换到其他类型
- 限定作用域的枚举类型和不限定范围的枚举类型都支持底层类型指定（例如：`enum Class Status: uint32_t`或者`enum Status: uint32_t`）。限定作用域的枚举类型的默认底层类型是int，而不限范围的枚举类型没有默认底层类型
- 限定作用域的枚举类型总是可以进行前置声明，而不限范围的枚举类型却只有在指定了默认底层类型的前提下才可以进行前置声明

## 条款11. 优先选用删除函数(=delete)，而非private未定义函数

- 优先选用删除函数（`=delete`），而非private来未定义函数
- 任何函数都可以删除，包括非成员函数和模板实现

> 反正请都使用=delete吧，忘了private的方式～

## 条款12. 为需要"改写"的函数添加override声明

- 为需要改写的函数添加override声明

- 成员函数引用修饰词使得对于左值和右值对象(*this)的处理能够区分开来

  ```cpp
  class Widget{
  public:
      void dowork() &;   // 左值对象
      void dowork() &&;  // 右值对象
  }
  ```

> 改写(override)需要满足的条件：
>
> - 基类中的函数必须是虚函数
> - 基类和派生类中的函数名字必须完全相同（析构函数除外）
> - 基类和派生类中的函数形参类型必须完全相同
> - 基类和派生类中的函数常量性必须完全相同
> - 基类和派生类中的函数返回值和异常规格必须兼容
> - 基类和派生类中的函数**引用修饰词**必须完全相同（C++11）--- 带有引用修饰词的成员函数，不必是虚函数
>
> 将final应用于虚函数，会阻止它在派生类中被改写。final也可以被应用于一个类，在这种情况下，该类会被禁止作为基类

## 条款13. 优先选用const_iterator，而非iterator

- 优先选用const_iterator，而非iterator
- 在最通用的代码中，优先选用非成员函数版本的begin，end和rbegin等，而非成员函数版本（主要是因为一些类似容器的数据结构会以非成员函数的方式提供begin和end等---如string）

> 注意：const_iterator指的是"指针"所指的对象具有常量性，而不是指针本身具有常量性

## 条款14. 未完待续



## 条款15. 只要有可能使用constexpr，就使用它

- constexpr对象都具备const属性，并由编译期已知的值完成初始化

- constexpr函数在调用时若传入的实参值是编译期已知的，则会产出编译期结果

  > 1. constexpr函数可以用在要求编译期常量的语境中。在这样的语境中，若你传给一个constexpr函数的实参值是在编译期已知的，则结果也会在编译期间计算出来。
  > 2. 在调用constexpr函数时，若传入的值有一个或多个在编译期未知，则它的运作方式和普通函数无异，即它也是在运行期执行结果的计算
  > 3. constexpr函数的形式有限制：一般只包含一条return语句（C++14中适当放宽了）

- 比起非constexpr对象或constexpr函数而言，constexpr对象或是constexpr函数可以用在一个作用域更广的语境中

其他关于constexpr的优势：

1. constexpr用于对象时，其实就是加强版的const（constexpr对象都是const对象，而并非所有的const对象都是constexpr对象）
2. 编译期确定往往效率更高，应用语境更广（类似作为数组长度等等）

## 条款16. 保证const成员函数的线程安全性

- 保证const成员函数的线程安全性，除非可以确信它们不会用在并发语境中
- 运用`std::atomic`类型的变量会比运用互斥量提供更好的性能，但前者仅适用对单个变量或内存区域的操作

> 其他内容：
>
> 1. `mutable`修饰词：使得const成员函数能够修改`mutable`修饰的数据成员（详见[mutable](https://www.zhihu.com/question/64969053/answer/226383958)）
>
> 2. `mutex`：在头文件`<mutex>`中，主要起"增加+解除"互斥量。一般简答的用法（详细的介绍见：[mutex](https://stackoverflow.com/questions/4989451/mutex-example-tutorial)，[mutex](https://blog.poxiao.me/p/multi-threading-in-cpp11-part-2-mutex-and-lock/)）
>
>    ```cpp
>    mutex m;
>    lock_guard<mutex> g(m)
>    ```
>
> 3. `atomic`：在头文件`<atomic>`中，主要起原子操作。（详见：[atomic](https://stackoverflow.com/questions/31978324/what-exactly-is-stdatomic)）

