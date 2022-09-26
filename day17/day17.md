2022.9.26
学习C++primer  4.11类型转换


## 类型转换

### 命名的强制类型转换
一个命名的强制类型转换具有如下形式：

cast-name<type>(expression);

type时转换的目标类型;expression时要转换的值。

如果type时引用类型，则结果是左值。

cast-name是static_cast、dynamic_cast、const_cast和reinterpret_cast中的一种。

dynamic_cast支持运行时类型识别。

### static_cast
任何具有明确定义的类型转换，只要不包含底层cost，都可以使用static_cast。

当需要把一个较大的算术类型赋值给较小的类型时，static_cast非常有用。

强制类型转换告诉程序的读者和编译器，我们并不在乎精度损失。

static_cast对于编译器无法自动执行的类型转换也非常有用。

```
void *p = &d;
double *dp = static_cast<double *>(p); //将void*转换回初始的指针类型。
```

### const_cast
const_cast只能改变运算对象的底层const。

```
const char *pc;
char *p = const_cast<char *>(pc); //正确，但是通过*P改写值，是未定义的行为。
```

只有const_cast能改变表达式的常量属性。

不能用const_cast改变表达式的类型。

### reinterpert_cast
reinterpert_cast通常为运算对象的位模式提供较低层次上的重新解释。

reinterpert_cast本质上依赖于机器，要想安全的使用reinterpret_cast必须对涉及的类型和编译器实现转换的过程都非常了解。
