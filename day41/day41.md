2022.10.26


### 从const成员函数返回*this
接下来，我们继续添加一个名为display的操作，它负责打印Screen的内容。我们希望这个函数能和move以及set出现在同意序列中，因此类似于move和set，display函数也应该返回执行它的对象的引用。

从逻辑上来说，显示一个Screen并不需要改变它的内容，因此我们令display为一个const成员，此时，this将是一个指向const的指针而*this是const对象。由此推断，display的返回类型应该是const Sales_data&。然而，如果真的令display返回一个const引用，则我们将不能把display嵌入到一组动作的序列中去：

```c++
Screen myScreen;
//如果display返回敞亮引用，则调用set将引发错误
myScreen.display(cout).set('*');
```

即使myScreen是个非常量对象，对set的调用也无法通过编译。问题在于display的const版本返回的是常量引用，而我们显然无权set一个常量对象。

一个const成员函数如果以引用的形式返回*this，那么它的返回类型将是常量引用。

### 基于const的重载
通过区分成员函数是否是const的，我们可以对其进行重载，其原因与我们之前根据指针参数是否指向const而重载的函数原因差不多。

在下面的例子中，将定义一个名为do_display的私有成员，由它负责打印Screen的实际工作。所有的display将调用这个函数，然后返回执行操作的对象。

```c++
class Screen{
public:
    //根据对象是否是const重载了display函数
    Screen &display(std::ostrean &os) { do_display(os); return *this; }
    const Screen &display(std::ostream &ob) const { do_display(os); return *this; }
private:
    //该函数负责显示Screen的内容
    void do_display(std::ostream &os) const {os << contents;}
    ...
};
```

和之前学的一样，当一个成员调用另外一个成员时，this指针在其中隐式地传递。因此当display调用do_display时，它的this指针隐式的传递给do_display。而当display的非常量版本调用do_distplay时，它的this指针将隐式的从指向非常量 的指针转换成指向常量的指针。

当do_display完成后，display函数各自返回解引用this所得的对象。在非常量版本中，this指向一个非常量对象，因此display返回一个普通的引用；而const成员则返回一个常量引用。

```c++
Screen myScreen(5, 3);
const Screen blank(5, 3);
myScreen.set('#').display(cout); //调用非常量版本
blank.display(cout);    //调用常量版本
```

建议：对于公共代码使用私有功能函数

定义一个单独的do_display函数原因：一个基本的愿望是避免在多处使用同样的代码；我们预期随着类的规模发展，display函数有可能变得更加复杂，此时，把相应的操作写在一处而非两处的作用就比较明显了；我们很可能在开发过程中给do_display函数添加某些调试信息，而这些信息将在代码的最终产品版本中去掉。显然，只在do_display一处添加或删除这些信息要更容易一些；这个额外的函数调用不会增加任何开销。因为我们在类内部定义了do_display，所以它隐式的被声明成内联函数。这样的话，调用do_display就不会带来任何额外的运行时开销。

在实践中，设计良好的C++代码常常包含大量类似于do_display的小函数，通过调用这些函数，可以完成一组其他函数的“实际”工作。
