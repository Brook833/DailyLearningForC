2022.10.29


### 成员定义中的普通块作用域的名字查找
成员函数中使用的名字按照如下方式解析：

首先，在成员函数内查找该名字的声明。和前面一样，只有在函数使用之前出现的声明才被考虑。

如果在成员函数内没有找到，则在类内继续查找，这时类的所有成员都可以被考虑。

如果类内也没有找到该名字的声明，在成员函数定义之前的作用域内继续查找。

一般来说，不建议使用其他成员的名字作为某个成员函数的参数。

```c++
int height; //定义了一个名字，稍后将在Screen中使用
class Screen {
public:
    typedef std::string::size_type;
    void dummy_fcn(pro height) {
        cursor = width * height;
    }
private:
    pos cursor = 0;
    pos height = 0, width = 0;
};
```

当编译器处理dummy_fcn中的乘法表达式时，它首先在函数作用域内查找表达式中用到的名字。函数的参数位于函数作用域内，因此dummy_fcn函数体内用到的名字height指的是参数声明。

```c++
//不建议的写法：成员函数中的名字不应该隐藏同名的成员
void Screen:dummu_fcn(pos height) {
    cursor = width * this->height; //成员height
    //另外一种表示该成员的方式
    cursor = width * Screen::height; //成员height
}
```

Note:

尽管类的成员被隐藏了，但我们仍然可以可以通过加上类的名字或显式的 使用this指针来强制访问成员。

其实最好的确保我们使用height成员的方法是给参数起个其他名字。

```c++
//建议的写法：不要把成员名字作为参数或其他局部变量使用
void Screen::dummy_fcn(pos ht) {
    cursor = width * height; //成员height
}
```

在此例中，当编译器查找名字height时，显然在dummy_fcn函数内部是找不到的。编译器接着会在Screen内查找匹配的声明，即使height的声明出现在dummy_fcn使用它之后，编译器也能正确的解析函数使用的是名为height的成员。

### 类作用域之后，在外围的作用域中查找
如果编译器在函数和类的作用域中都没有找到名字，它将接着在外围的作用域中查找。在我们的例子中，名字Height定义在外层作用域中，且位于Screen的定义之前。然而，外层作用域中的对象被名为height的成员隐藏掉了。因此，如果我们需要的是外层作用域中的名字，可以显式的通过作用域运算符来进行请求：

```c++
//不建议的写法：不要隐藏外层作用域中可能被用到的名字
void Screen::dummy_fcn(pos height) {
    cursor = width * ::height; //全局的height
}
```

Note:

尽管外层的对象被隐藏掉了，但我们仍然可以用作用域运算符访问它。

### 在文件中名字的出现处对其进行解析
当成员定义在类的外部时，名字查找的第三步不仅要考虑类定义之前的全局作用域中的声明，还需要考虑在成员函数定义之前的全局做哟关于中的声明。例如：

```c++
int height; //定义了一个名字，稍后将在Screen中使用
class Screen {
public:
    typedef std::string::size_type pos;
    void setHeight(pos);
    pos height = 0; //隐藏了外层作用域中的height
};
Screen::pos verify(Screen::pos);
void Screen::setHeight(pos var) {
    //var:参数
    //height: 类的成员
    //verify:全局函数
    height = verify(var);
}
```


请注意，全局函数verify的声明在Screen类的定义之前是不可见的。然而，名字查找的第三步包括了成员函数出现之前的全局作用域。在此例中，veriufy的声明位于setHetght的定义之前，因此可以被正常使用。

