# ch1. 类型推导

主要关于模板类型推导，auto的类型推导如何构建在模板类型推导规则之上，以及delctype独特的类型推导规则

## 条款1. 模板类型推导

- 在模板类型推导过程中，具有引用类型的实参会被当成非引用类型来处理。换言之，其引用性会被忽略
- 对万能引用形参进行推导时，左值实参会进行特殊处理
- 对按值传递的形参进行推导时，若实参类型中带有const或volatile修饰词，则它们还是会被当做不带const或volatile修饰词的类型来处理
- 在模板类型推导过程中，数组或函数类型的实参会退化成对应的指针，除非它们被用来初始化引用

```cpp
template<typename T>
void f(ParamType param);   // ParamType往往是T加上一些修饰符

f(expr)   // 调用---通过expr推导T的类型
```

主要理解`T`会被推到成什么类型（和`ParamType`上的修饰符相关），主要分为下述三类：

① `ParamType`是**指针或引用**（但不是万能指针）：若`expr`具有引用类型，则先将引用部分忽略。再对`expr`的类型和`ParamType`的类型进行模式匹配来决定`T`的类型（即让`expr`的类型和`ParamType`的一致）

② `ParamType`是**万能指针**：如果`expr`是个左值，`T`和`ParamType`会被推导为左值引用；如果`expr`是个右值，和上述①中采用相同的策略（`ParamType`是万能指针时不能给其加上const等修饰词）

③ `ParamType`**既不是指针也不是引用**（按值传递）：若`expr`具有引用类型，忽略引用部分；若忽略`expr`的引用性之后，`expr`是个const或volatile对象，也将其忽略

> 额外需要记住的点：
>
> 1. 在模板类型推导过程中，数组或函数类型的实参会退化成对应的指针，除非他们被用来初始化引用
>
>    ```cpp
>    // 情况1
>    template<typename T>
>    void f(T param);
>    // 情况2
>    template<typename T>
>    void f2(T &param);
>
>    const char name[]="J. P. Briggs";
>    f(name);    // T会被推导成const char *
>    f2(name);   // T会被推导成const char [13]
>    ```
>
> 2. 上述规则的记忆方式：按值去引用去修饰，万能保左，指针或引用常规匹配

## 条款2. auto类型推导

- 在一般情况下，auto类型推导和模板类型推导是一模一样的，但是auto类型推导会假定用大括号括起来的初始化表达式代表一个`std::initializer_list`，但模板类型推导却不会

  ```cpp
  // 情况1
  auto x = {27};  // auto为std::initializer_list<int>
  // 情况2
  template<typename T> void f(T param);
  f({11, 23, 9});   // 错误！无法推导出T的类型
  // 情况3
  template<typename T> void f2(std::initializer_list<T> param);
  f2({11, 23, 9});  // OK!
  ```

- 在函数返回值或lambda式的形参中使用auto，此时是使用模板类型推导而非auto类型推导（C++14）

  ```cpp
  // 情况1
  auto f(){ return 1; }    // 此时auto会被推到成int
  // 情况2
  vector<int> v;
  auto f2 = [&v](const auto& newValue){ v = newValue; };   // 根据输入推导auto
  ```

> **模板类型推导和`auto`类型推导可以建立一一映射关系**（是指概念上等价）：`auto`扮演模板中`T`的角色，而变量的类型修饰符则扮演`ParamType`的角色（当你实在想不通`auto`的类型时，采用这种等价的思考方式来推导）
>
> 所以`auto`类型推导也存在下述三种情况：（类型修饰词代替了ParamType，推导结果完全同条款1的情况）
>
> ① 类型修饰符是指针或引用，但不是万能指针
>
> ② 类型修饰符是万能指针
>
> ③ 类型修饰符既不是指针也不是引用

## 条款3. decltype

- 绝大多数情况下，`decltype`会得到变量或者表达式的类型而不做任何修改（即鹦鹉学舌般返回给定名字或表达式的确切类型）
- 对于类型为`T`的左值表达式，除非该表达式仅有一个名字（例如`int x=0; decltype(x)`获得的是`int`），否则`decltype`总是得到为`T &`的类型（例如`int x=0; decltype((x))`获得的是`int &`）
- C++14支持`decltype(auto)`，和`auto`一样，它会从其初始化表达式出发来推导类型，但是它的类型推导使用的是decltype的规则

> decltype主要用途在于声明那些返回值类型依赖于形参类型的函数模板！
>
> ```cpp
> // 情况1（下述只是demo, 更好的写法见书）
> template<typename Container, typename Index>
> auto f(Container &c, Index i){
>     return c[i];
> }
> std::vector<int> v{1, 2, 3, 4};
> f(v, 2) = 4;      // 错误！f(v, 2)返回的是右值！
> // 情况2
> template<typename Container, typename Index>
> decltype(auto) f2(Container &c, Index i){
>     return c[i];
> }
> f2(v, 2) = 4;      // 正确
> ```

## 条款4. 查看类型推导结果

- 利用IDE编辑器，编译期错误信息和Boost.TypeIndex库常常能够查看到推导而得的类型
- 有些工具产生的结果可能会无用，或者不准确。所有，理解C++类型推导规则是必要的

> 这个条款可以视为debug的方法

只给出"最靠谱"的方案：利用`Boost`的`TypeIndex`库：

主要利用`type_id_with_cvr<T>().pretty_name() `和`type_id_with_cvr<decltype(param)>().pretty_name() `两条语句。

```cpp
#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

// 采用下述函数进行debugs
template<typename T>
void f2(const T &param) {
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param=" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo3(){
    vector<int> vec{1, 2, 3, 5};
    const auto vw = vec;
    if (!vw.empty())
        f2(&vw[0]);
}
```

