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

这种声明有时被称作前向声明，它向程序中引入了名字Screen并且指明Screen是一种类类型。对于类型Screen来说，在声明之后定义之前是一个不完全类型，也就是说，此时我们已知Screen是一个类类型，但是不清楚它到底包含哪些成员。

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

一开始，首先把s定义成screens vector中第i个位置上的Screen引用，随后利用Screen的htight和width成员计算出一个新的string对象，并令其含有若干个空白字符，最后我们把这个含有很多空白的字符串赋给contents成员。

如果clear不是Screen友元，上面的代码将无法通过编译，因此此时clear将不能访问Screen的height、width和contents成员。而当Screen将Window_mgr指定为其友元之后，Screen的所有成员对于Window_mgr就都变成可见的了。

必须要注意一点是，友元关系不存在传递性。也就是说，如果Window_mgr有它自己的友元，则这些友元并不能理所当然地具有访问Screen的特权

每个类负责控制自己的友元类或者友元函数。

### 令成员函数作为友元

除了令整个Window_mgr作为友元之外，Screen还可以只为clear提供访问权限。当把一个成员函数声明成友元时，必须明确指出该成员函数属于哪个类:

```c++
class Screen {
    //Window_mgr::clear必须在Screen类之前被声明
    friend void Window_mgr::clear(ScreenIndex);
    //Screen类的剩余部分
};
```

要想令某个成员函数作为友元，我们必须仔细组织程序的结构以满足声明和定义的彼此依赖关系。在这个例子中，我们必须按照如下方式设计程序：

首先定义Window_mgr类，其中声明clear函数，但是不能定义它。在clear使用Screen的成员之前必须先声明Screen。

接下来定义Screen，包括对于clear的友元声明。

最后定义clear，此时 它才可以使用Screen的成员。

### 函数重载和友元
尽管重载函数的名字相同，但他们仍然是不同的函数。因此，如果一个类想把一组重载函数声明成它的友元，它需要对这组函数中的每一个分别声明：

```c++
//重载的storeOn函数
extern std::ostream& storeOn(std::ostream &, Screen &);
extern BitMap& storeOn(BitMap &, Screen &);
class Screen {
    //storeOn的ostream版本能访问Screen对象的私有部分
    friend std::ostream& storeOn(std::ostream &, Screen &);
    //...
};
```

Screen类把接受ostream&的storeOn函数声明成它的友元，但是接受BitMap&作为参数的版本仍然不能访问Screen。

### 友元声明和作用域
类和非成员函数的声明不是必须在它们的友元声明之前。当一个名字第一次出现在一个友元声明中时，我们隐式的假定改名字在当前作用域是可见的，然而，友元本身不一定真的声明在当前作用域中。

甚至就算在类的内部定义该函数，我们也必须在类的外部提供相应的声明从而使得函数可见。换句话说，即使我们仅仅是用声明友元的类的成员调用该成员函数，它也必须是被声明过的：

```c++
struct X {
    friend void f() { /* 友元函数可以定义在类的内部 */ }
    X() {f();}  //错误，f还没有被声明
    void g();
    void h();
};
void X::g() { return f(); } //错误，f没有被声明
void f();   //声明f
void X::h() { return f(); } //正确，现在f的声明在作用域中了
```

注意，有的编译器并不强制执行上述关于友元的限定规则。