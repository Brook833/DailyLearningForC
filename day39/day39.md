2022.10.24
学习C++primer


## 友元
既然Sales_data的数据成员是private的，我们的read、print和add函数就无法正常编译，这是因为尽管这几个函数是类的接口的一部分，但他们不是类的成员。 

类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元。如果类想把一个函数作为它的友元，只需要增加一条friend关键字开始的函数声明语句即可。
```c++
class Salse_data {
    //为Sales_data的非成员函数所做的友元声明
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    ...
};
```

友元声明只能出现在类定义的内部，但是在类内出现的具体位置不限。

友元不是类的成员也不受它所在的区域访问控制级别的约束。

一般来说，最好在类定义的开始或结束前的位置集中声明友元。

### 封装的优点
确保用户代码不会无意间破坏封装对象的状态。

被封装的类的具体实现细节可以随时改变，而无需调整用户级别的代码。

### 友元的声明
友元的声明仅仅制定了访问的权限，而非一个通常意义上的函数声明。如果我们希望类的用户能够调用某个友元函数，那么我们就必须在友元声明之外再专门对函数进行有一次声明。

为了使友元对类的用户可见，我们通常把友元的声明与类本身放置在同一个头文件中(类的外部)。因此我们的Sales_data头文件应该为read、print和add提供独立的声明(除了类内部的友元声明之外)。

许多编译器并未强制限定友元函数必须在使用之前在类的外部声明。

一些编译器允许在尚无友元函数的初始声明的情况下就调用它。不过即使你的编译器支持这种行为，最好还是提供一个独立的函数声明。这样即使你更换了一个有这种强制要求的编译器，也不必改变代码。

### 定义一个类型成员
Screen表示显示器中的一个窗口。每个Screen包含一个用于保存Screen内容的string成员和三个string::size_type类型的成员，他是们分别表示光标的位置以及屏幕的高和宽。

除了定义数据成员和函数成员之外，类还可以自定义某种类型在类中的别名。由类定义的类型名字和其他成员一样存在访问限制，可以是public或者private中的一种：

```c++
class Screen {
public:
    typedef std::string::size_type pos;
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};
```

我们在Screen的public部分定义了pos，这样用户就可以使用这个名字。Screen的用户不应该知道Screen使用了一个string对象来存放它的数据，因此通过把pos定义成public成员可以隐藏Screen实现的细节。

关于pos的声明有两点需要注意。首先，我们使用了typedef，也可以等价的使用类型别名(using a = b)。其次，用来定义类型的成员必须先定义后使用，这一点与普通成员有所区别。因此，类型成员通常出现在类开始的地方。

### Screen类的成员函数
要是我们的类更加使用，还需要添加一个构造函数令用户能够定义屏幕的尺寸和内容，以及其他两个成员，分别负责移动光标和读取给定位置的字符。
```c++
class Screen {
public:
    typedef std::string::size_type pos;
    Screen() = default; //因为Screen有另外一个构造函数，所以该函数是必须的。
    //cursor被其类内初始值初始化为0
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht *wd, c) { }
    char get() const { return contents[cursor]; } //读取光标处的字符
    Screen &move(pos r, pos c);
private:
    pos cursor = 0;
    por height = 0, width = 0;
    std::string contents;
};
```