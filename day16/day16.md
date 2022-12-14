2022.9.24
学习C++primer  4.5递增和递减运算符  4.6成员访问运算符  4.7条件运算符  4.8位运算符  4.9sizeof运算符  4.10逗号运算符


## 递增和递减运算符
递增和递减运算符必须作用于左值运算对象。

除非必须，否则不用递增递减运算符的后置版本（i++）。

### 在一条语句中混用解引用和递增操作符
```
while (pbeg != v.end() && *beg >= 0) 
    cout << *pbeg++ << endl;
```
后置递增运算符的优先级高于解引用操作符，即等于*(pbeg++)。

pbeg++的结果仍为开始的pbeg。因此，这条语句输出pbeg开始指向的那个元素，并将指针向前移动一个位置。

### 运算对象可按任意顺序求值
大多数运算符都没有规定运算对象的求值顺序。

如果一条子表达式改变了某个运算对象的值，另一条子表达式又用到该值的话，运算对象的求值顺序就很重要了。

## 成员访问运算符
点运算符(.)和箭头运算符(->)都可用于访问成员。

箭头运算符作用于一个指针类型的运算对象，结果是一个左值。

点运算符，如果成员是左值，结果是左值；成员是右值，结果是右值。

点运算符获取类对象的一个成员。

箭头运算符与点运算符有关，表达式ptr->mem 等价于(*ptr).mem

因为解引用操作符的优先级低于点运算符，所以执行解引用运算的子表达式两端必须加上括号。

## 条件运算符
条件运算符(?:)满足右结合律

## 位运算符
bitset的标准库类型也可以表示任意大小的二进制位集合，位运算符同样可以用于bitset类型。

关于符号位如何处理没有明确的规定，所以强烈建议仅将位运算符用于无符号类型。

### 移位运算符满足左结合律

## sizeof位运算符
sizeof运算符返回一条表达式或一个类型名字所占的字节数。

sizeof运算符满足右结合律。

## 逗号运算符
逗号运算符含有两个运算对象，按照从左向右的顺序依次求值。(规定了运算顺序)

逗号运算符真正的结果是右侧表达式的值。