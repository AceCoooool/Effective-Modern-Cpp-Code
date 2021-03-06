# 番外篇

## Extra1：范围for

- 如果只希望遍历，而不希望修改，可以使用`for(const auto & a: arr)`来定义a的类型。这样对于复制负担比较大的容器元素可以"无损"遍历
- auto自动推导出的类型是容器中的value_type，而不是迭代器
- 对于基于范围for循环而言，冒号后面的表达式只会被执行一次
- 基于范围的循环倾向于在循环开始之前确定好迭代范围，而不是在每次迭代之前都去调用一次`arr.end()`（因此尽量不要在迭代过程中修改迭代的容器）

## Extra2：function和bind绑定器

- C++11通过`std::function`和`std::bind`统一了可调用对象的各种操作
- 当我们给`std::function`填入合适的函数签名（返回值+参数表）之后，它就变成了一个可以容纳所有这一类调用方式的"函数包装器"
- `std::bind`用来将可调用对象与其参数一起进行绑定。绑定后的结果可以使用`std::function`进行保存，并延迟调用到任何我们需要的时候

> ① 调用对象：
>
> 1. 是一个函数指针
> 2. 是一个具有`operator()`成员函数的类对象（仿函数）
> 3. 是一个可被转换为函数指针的类对象
> 4. 是一个类成员（函数）指针
>
> ② bind的两大作用
>
> 1. 将可调用对象**与其参数**一起绑定成一个仿函数
> 2. 将多元（参数个数为n，n>1）可调用对象转成一元或者(n-1)元可调用对象，即只绑定部分参数

## Extra3：tuple元组

- tuple元组是一个固定大小的不同类型值的集合，是泛化的`std::pair`
- 可以利用`make_tuple`，`tie`来创建tuple，利用`get<num>(tuple对象)`来获得元组的值；可以利用`forward_as_tuple`创建右值的引用元组方法
- 可以通过`tuple_cat`连接多个tuple