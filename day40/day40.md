2022.10.25


### 重载成员函数
和非成员函数一样，成员函数也可以被重载，只要函数之间在参数的数量或类型上有所区别就行。成员函数的函数匹配过程同样与非成员函数非常类似。
```c++
Screen myscreen;
char ch = myscreen.get(); //调用Screen::get()
ch = myscreen.get(0,0); //调用Screen::get(pos, pos)
```

### 可变数据成员
有时(但并不频繁)，会发生这样一种情况，我们希望能够改变类的某个数据成员，即使是在一个const成员函数内。可以通过在变量的声明中加入mutable关键字做到这一点。

一个可变数据成员永远不会是const，即使它是const对象的成员。因此，一个const成员函数可以改变一个可变成员的值。举个例子，我们将给Screen添加一个名为access_ctr的可变成员，通过它我们可以追踪每个Screen的成员函数被调用了多少次；
```c++
class Screen {
public:
    void some_member() const;
private:
    mutable size_t access_ctr; //即使在一个const对象内也能被修改
}；
void Screen::some_member() const {
    ++access_ctr; //保存一个计数值，用于记录成员函数被调用的次数
}
```

尽管some_member是一个const成员函数，它仍然能够改变access_ctr的值。该成员是个可变成员，因此任何成员函数，包括const函数在内都能改变它的值。

### 类数据成员的初始值
在定义好Screen类之后，我们将继续定义一个窗口管理类并用它表示显示器上的一组Screen。这个类将包含一个Screen类型的vector，每个元素表示一个特定的SCreen。默认情况下，我们希望Window——mgr类开始时拥有一个默认初始化的Screen。在C++11中，最好的方式就是把这个默认值声明成一个类内初始值。
```c++
class Window_mgr {
private:
    //这个Window_mgr追踪的Screen
    //默认情况下，一个Window_mgr包含一个标准尺寸的空白Scren
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};
```

当我们初始化类类型的成员时，需要为构造函数传递一个符合成员类型的实参。在此例中，我们使用一个单独的元素值对vector成员执行了列表初始化，这个Screen的值被传递给vector<Screen>的构造函数，从而创建了一个单元素的vector对象。具体地说，Screen的构造函数接受两个尺寸参数和一个字符值，创建了一个给定大小的空白屏幕对象。

如我们之前所知的，雷内初始值必须使用=的初始化方式(初始化Screen的数据成员时所用的)或者花括号括起来的直接初始化形式(初始化Screens所用的)

当我们提供一个类内初始值时，必须以符号=或者花括号表示。

### 返回*this的成员函数
接下来我们继续添加一些函数，他们负责设置光标所在的位置的字符或者其他任意给定位置的字符:
```c++
class Screen {
public:
    Screen &set(char);
    Screeen &set(pos, pos, char);
    ...
};

inline Screen &Screen::set(char c) {
    contents[cursor] = c;  //设置当前光标所在位置的新值
    return *this;   //将this对象作为左值返回
}

inline Screen &Screen::set(pos r, pos col, char ch) {
    contents[r*width + col] = ch; //设置给定位置的新值
    return *this;   //将this对象作为坐直返回
}
```

和move操作一样，我们的set成员的返回值是调用set的对象的引用。

返回引用的函数时左值的，意味值这些函数返回的是对象本身而非对象的副本。

如果我们一系列这样的操作连接在一条表达式中的话：

```c++
//把光标移动到一个指定的位置，然后设置该位置的字符值。
myScreen.move(4, 0).set('#');
```

这些操作将在同一个对象上执行。在上面的表达式中，我们首先移动myScreen内的光标，然后设置myScreen的contents成员。也就是说，上述语句等价于：

```c++
myScreen.move(4, 0);
myScreen.set('#');
```

如果我们令move和set返回Screen而非Screen&，则上述语句的行为将大不相同。在此例中等价于：

```c++
//如果move返回Screen而非Screen&
Screen temp = myScreen.move(4, 0); //对返回值进行拷贝。
temp.set('#'); //不会改变myScreen的contents。
```

假如当初我们定义的返回类型不是引用，则move的返回值将是*this的副本，因此调用set只能改变临时副本，而不能改变myScreen的值。