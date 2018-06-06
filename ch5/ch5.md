# ch5. 右值引用、移动语义和完美转发

- **移动语义**使得编译器得以使用不那么昂贵的移动操作来替换昂贵的复制操作。同复制构造函数、复制赋值运算符给予人们控制对象复制的具体意义的能力一样，移动构造函数和移动赋值运算符也给予人们控制对象移动语义的能力。移动语义也使得创建只移类型对象成为可能，这些类型包括std::unique_ptr，std::future和std::thread等
- **完美转发**使得人们可以撰写接受任意实参的函数模板，并将其转发到其他函数，目标函数会接受到与转发函数所接受的完全相同的实参

右值引用是将这两个风马牛不相及的语言特性胶合起来的底层语言机制，正是它使得移动语义和完美转发成为了可能。

> 形参总是左值，即使其类型是右值引用：如`void f(Widget && w)`中的w是左值

## 条款23：理解std::move和std::forward

- std::move实施的是无条件的向右值类型的**强制类型转换**。就其本身而言，它不会执行移动操作
- 仅当传入的实参被绑定到右值时，std::forward才针对该实参实施向右值类型的**强制类型转换**
- 在运行期，std::move和std::forward都不会做任何操作！
