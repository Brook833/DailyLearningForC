2022.10.27



### 类类型
每个类定义了唯一的类型。对于两个类来说，即使他们的成员完全一样，这两个类也是两个不同的类型。

```c++
struct First {
    int memi;
    int getMem();
};
struct Second {
    int memi;
    int getMem();
};
First obj1;
Second obj2 = obj1; //错误，obj1和obj2类型不同。
```

即使两个类的成员列表完全一致，他们也是不同的类型。

我们可以把类名作为类型的名字使用，从而直接指向类类型，或者，我们也可以把类名跟在class和struct后面：

```c++
Sales_data item1; //默认初始化Sales_data类型的对象。
class Sales_data item1; //等价的生命
```

### 类的声明
就像可以把函数的声明和定义分离开一样，我们也能仅声明类而暂时不定义它：
``` c++
class Screen; //Screen类的声明
```

这种声明有时被称作前向声明，它向程序中引入了名字Screen并且致命Screen是一种类类型。对于类型Screen来说，在声明之后定义之前是一个不完全类型，也就是说，此时我们已知Screen是一个类类型，但是不清楚它到底包含哪些成员。

不完全类型只能在非常有限的情景下使用：可以定义指向这种类型的指针或引用，也可以声明以不完全类型作为参数或者返回类型的函数。

对于一个类来说，在我们创建他的对象之前该类必须被定义过，而不能仅仅被声明。否则，编译器就无法了解这样的对象需要多少存储空间。类似的，类也必须首先被定义，然后才能用引用或者指针访问其成员。毕竟，如果类尚未定义，编译器也就不清楚该类到底有哪些成员。

直到类被定义之后数据成员才能被声明成这种类类型。换句话说，我们必须首先完成类的定义，然后编译器才能知道存储该数据成员需要多少空间。因为只有当类全部完成后，类才算被定义，所以一个类的成员类型不能是该类自己。

然而，一旦一个类的名字出现后，他就被认为是声明过了(但尚未定义)，因此类允许包含指向它自身类型的引用或指针：

```c++
class Link_screen {
    Screen window;
    Link_screen *next;
    Link_screen *prev;
};
```

## 友元再探
类还可以把其他的类定义成友元，也可以把其他类的成员函数定义成友元。此外，友元函数能定义在类的内部，这样的函数是隐式内联的。

### 类之间的友元关系
举个友元类的例子，我们Window_mgr类的某些成员可能需要访问它管理的Screen类的内部数据。例如，假设我们需要为Window_mgr添加一个名为clear的成员，它负责把一个指定的Screen的内容都设为空白。为了完成这一任务，clear需要访问Screen的私有成员：而想要这种访问合法，Screen需要把Window_mgr指定成它的友元：

```c++
class Screen {
    //Window_mgr的成员可以访问Screen类的私有部分。
    friend class Window_mgr;
    //Screen类的剩余部分。
};
```

如果一个类指定了友元类，则友元类的陈冠函数可以访问此类包括非公有成员在内的所有成员。通过上面的声明，Window_mg r被指定为Screen的友元，因此我们可以将Window_mgr的clear成员写成如下的形式：

```c++
class Window_mgr {
public:
    //窗口中每个屏幕的编号
    using ScreenIndex = std::vector<Screen>::size_type;
    //按照编号将指定的Screen重置为空白
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens{Screen(24,80,' ')};
};

void Window_mgr::clear(ScreenIndex i) {
    //s是一个ScreeeN的引用，指向我们想清空的那个屏幕
    Screen &s = screens[i];
    //将选定的那个Screen重置为空白
    s.contents = string(s.height * s.width, ' ');
}
```
