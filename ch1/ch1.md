# 1. 类型推导

## 条款1：模板类型推导

```cpp
template<typename T>
void f(ParamType param);   // ParamType往往是T加上一些修饰符

f(expr)   // 调用---通过expr推导T的类型
```

主要理解`T`会被推到成什么类型（和`ParamType`上的修饰符相关），主要分为下述三类：

① `ParamType`是**指针或引用**（但不是万能指针）：若`expr`具有引用类型，则先将引用部分忽略。再对`expr`的类型和`ParamType`的类型进行模式匹配来决定`T`的类型（即让`expr`的类型和`ParamType`的一致）

② `ParamType`是**万能指针**：如果`expr`是个左值，`T`和`ParamType`会被推导为左值引用；如果`expr`是个右值，和上述①中采用相同的策略

③ `ParamType`**既不是指针也不是引用**（按值传递）：若`expr`具有引用类型，忽略引用部分；若忽略`expr`的引用性之后，`expr`是个const或volatie对象，也将其忽略

> 额外需要记住的点：
>
> 在模板类型推导过程中，数组或函数类型的实参会退化成对应的指针，除非他们被用来初始化引用

## 条款2：auto类型推导

**模板类型推导和`auto`类型推导可以建立一一映射关系**（是指概念上等价）：`auto`扮演模板中`T`的角色，而变量的类型修饰符则扮演`ParamType`的角色（当你是在想不通`auto`的类型时，采用这种等价的思考方式来推导）

所以`auto`类型推导也存在下述三种情况：（推导结果完全同条款1的情况）

① 类型修饰符是指针或引用，但不是万能指针

② 类型修饰符是万能指针

③ 类型修饰符既不是指针也不是引用

> 额外需记住的点：
>
> - auto类型推导会假定用大括号初始化表达式代表的是`std::initializer_list`，但模板类型推导不会（即`auto a={1, 2, 3}`推导的`auto`为`std::initializer_list`）
> - 在返回值或lambda形式的形参中使用auto，则会采用模板类型推导而非auto类型推导的规则（即不能采用大括号形式）--- C++14

## 条款3：decltype

绝大多数情况下，`decltype`会得到变量或者表达式的类型而不做任何修改（即鹦鹉学舌般返回给定名字或表达式的确切类型）

对于类型为`T`的左值表达式，除非该表达式仅有一个名字（例如`int x=0; decltype(x)`获得的是`int`），否则`decltype`总是得到为`T &`的类型（例如`int x=0; decltype((x))`获得的是`int &`）

> C++14支持`decltype(auto)`，和`auto`一样，它会从其初始化表达式出发来推导类型，但是它的类型推导使用的是decltype的规则

## 条款4：查看类型推导结果

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

