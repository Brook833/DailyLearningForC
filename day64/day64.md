2022.11.20



## 9.6 容器适配器
除了顺序容器以外，标准库还定义了三个顺序容器适配器:stack、queue和priority_queue。适配器是标准库中的一个通用概念。容器、迭代器和函数都有适配器。本质上，一个适配器是一种机制，能使某种事物的行为看起来另外一种事物一样。一个容器适配器接受一种已有的容器类型，使其行为看起来像一种不同的类型。例如，stack适配器接受一个顺序容器(除array或forward_list外)，并使其操作起来像一个stack一样。表9.17列出了所有容器适配器都支持的操作和类型。

| **表9.17: 所有容器适配器都支持的操作和类型** |  |
|:- |:- |
| size_type | 一种类型，足以保存当前类型的最大对象的大小 |
| value_type | 元素类型 |
| container_type | 实现适配器的底层容器类型 |
| A a; | 创建一个名为a的空适配器 |
| A a(c); | 创建一个名为a的适配器，带有容器c的一个拷贝 |
| 关系运算符 | 每个适配器都支持所有关系运算符: ==、!=、<、<=、>和>= |
| a.empty() | 若a中包含任何元素，返回false,否则返回true |
| a.size() | 返回a中的元素数目 |
| swap(a, b) 或 a.swap(b) | 交换a和b的内容，a和b必须有相同类型，包括底层容器类型也必须相同 |

### 定义一个适配器
每个适配器都定义两个构造函数:默认构造函数创建一个空对象，接受一个容器的构造函数拷贝该容器来初始化适配器。例如，假定deq是一个deque<int>，我们可以用deq来初始化一个新的stack，如下所示:

```c++
stack<int> stk(deq);  // 从deq拷贝元素到stk
```

默认情况下，stack和queue是基于deque实现的，priority_queue是在vector之上实现的。我们可以在创建一个适配器时将一个命名的顺序容器作为第二个类型参数，来重载默认容器类型。

```c++
stack<string, vector<string>> str_stk;  // 在vector上实现的空栈
stack<string, vector<string>> str_stk2(svec);  // str_stk2在vector上实现，初始化时保存svec的拷贝
```

对于一个给定的适配器，可以哪些容器是有限制的。所有适配器都要求容器具有添加和删除元素的能力。因此，适配器不能构造在array之上。类似的，我们也不能用forward_list来构造适配器，因为所有适配器都要求容器具有添加、删除以及访问尾元素的能力。stack只要求push_back、pop_back和back操作，因此可以使用除array和forward_list之外的任何容器类型来构造stack。queue适配器要求back、push_back、front和push_front，因此它可以构造于list或deque之上，但不能基于vector构造。priority_queue除了front、push_back和pop_bakc之外还要求随机访问的能力，因此它可以构造与vector或deque之上，但不能基于list构造。

### 栈适配器
stack类型定义在stack头文件中。表9.18列出了stack所支持的操作。下面的程序展示了如何使用stack:

```c++
stack<int> intStack;  // 空栈
// 填满栈
for (size_t ix = 0; ix != 10; ++ix) {
    intStack.push(ix);  // intStack保存0到9十个数
}
while (!intStack.empty()) {  // intStack中有值就继续循环
    int Value = intStack.top();
    // 使用栈顶值的代码
    intStack.pop();  // 弹出栈顶元素，继续循环
}
```

其中声明语句

```c++
stack<int> intStack;  // 空栈
```

定义了一个保存整型元素的栈intStack，初始时为空。for循环将10个元素添加到栈中，这些元素被初始化为从0开始连续的整数。whileu循环遍历整个stack，获取top值，将其从栈中弹出，直至栈空。

| **9.18: 表9.17未列出的栈操作** |  |
|:- |:- |
| 栈默认基于deque实现，也可以在list或vector之上实现 |  |
| s.pop() | 删除栈顶元素，但不返回该元素值 |
| s.push(item) 或 s.emplace(args) | 创建一个新元素压入栈顶，该元素通过拷贝或移动item而来，或者由argss构造 |
| s.top() | 返回栈顶元素，但不将元素弹出栈 |

每个容器适配器都基于底层容器类型的操作定义了自己的特殊操作。我们只可以使用适配器操作，而不能使用底层容器类型的操作。例如:

```c++
intStack.push(ix);  // intStack保存0-9十个数
```

此语句试图在intStack的底层deque对象上调用push_back。虽然stack是基于deque实现的，但不能直接使用deque操作。不能再一个stack上调用push_back，而必须使用stack自己的操作————push。

### 队列适配器
queue和priority_queue适配器定义在queue头文件中。表9.19列出了它们所支持的操作:

| **表9.19: 表9.17未列出的queue和priority_queue操作** |  |
|:- |:- |
| queue默认基于deque实现，priority_queue默认基于vector实现; |  |
| queue也可以用list或vector，priority_queue也可以用deque实现。 |  |
| q.pop() | 返回queue的首元素或priority_queue的最高优先级的元素，但不删除此元素 |
| q.front() | 返回首元素或尾元素但不删除此元素 |
| q.back() | 只适用于queue |
| q.top() | 返回最高优先级元素，但不删除此元素 |
| q.push(item) 或 q.emplace(args) | 在queue末尾或priority_queue中恰当的位置创建一个元素，其值为item，或由args构造 |

标准库queue使用一种先进先出的存储和访问策略。进入队列的对象被放置到队尾，而离开队列的对象则从队首删除。饭店按客人到达的顺序来为它们安排座位，就是一个先进先出队列的例子。

priority_queue允许我们为队列中的元素建立优先级。新加入的元素会排在所有优先级比他低的已有元素之前。饭店按照客人预定时间而不是到来时间的早晚来为它们安排座位，就是一个优先队列的例子。默认情况下，标准库在元素类型上使用 < 运算符来确定相对优先级。