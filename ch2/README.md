# ch2. auto

auto的优点：

1. 少打字！
2. 阻止手动指定类型所带来的潜在错误和性能问题

## 条款5. 优先选用auto，而非显示类型声明

- auto变量必须初始化，基本上对会导致兼容性和效率问题的类型不匹配现象免疫，还可以简化重构流程，通常也比显示指定类型少打一些字
- auto类型的变量都有着**条款2**和**条款6**中所描述的毛病

> 1. 通过`std::function`来调用闭包几乎必然会比通过使用`auto`声明的变量来调用同一闭包要来得慢（此处`auto`声明的变量往往表示一个lambda表达式）：主要在于内存及编译期两个层面
>
> 2. 显式指定类型可能导致你既不想要，也没想到的隐式类型转换
>
>    ```cpp
>    std::vector<int> v;
>    auto sz = v.size();    // sz的类型为vector<int>::size_type
>    ```
> 3. auto是一个可选项，而不是必选项。如果你的代码在使用显式类型声明的前提下更清晰，更易维护，当然可以采用显式声明

## 条款6. 当auto推导的类型不符合要求时，采用带显示类别的初始化（强制类型转换）

- "隐形"的代理类型可以导致auto根据初始化表达式推导出"错误的"类型（注：代理类是指为了模拟或增广其他类型的类）。例如

  ```cpp
  vector<bool> tmp{true, false, true};
  auto a = tmp[0];    // auto类型为vector<bool>::reference!!!而不是bool
  ```

- 解决auto被判断成代理类型的方案：强制进行另一次类型转换（强制类型转换）

> `auto`存在的问题：
>
> 1. 条款2中所说的`{}`初始化存在的问题
> 2. "隐形"的代理类型会导致`auto`根据初始化表达式推导出"错误"的类型（比如`vector<bool> a; a[2]`返回的就是`vector<bool>::reference`，以及`valarray<int> v1, v2; v1+v2`的结果并不是`valarray<int>`类型---更多关于"隐形"代理需要实践中去发现）：解决方案---采用带显示类型初始化来强制`auto`推导出想要的结果（例如：`vector<bool> f{true, false}; auto v=static_cast<bool>(f[0]);`）
>
> "如何发现"代理类：① 文档说明  ② 头文件(函数签名)
