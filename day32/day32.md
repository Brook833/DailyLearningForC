2022.10.17
学习C++primer


## 函数匹配
在大多数情况下，我们容易确定某次调用应该选用哪个重载函数。然而，当几个重载函数的形参数量相等以及某些形参的类型可以由其他类型转换的来时，这项工作就不是那么容易了。 

### 确定候选函数和可行函数
函数匹配的第一步是选定本次调用对应的重载函数集，集合中的函数称为候选函数。候选函数具备两个特征：一是与被调用的函数函数同名，二是其声明在调用点可见。

第二步考察本次调用提供的实参，然后从候选函数中选出能被这组实参调用的函数，这些新选出的函数称为可行函数。可行函数也有两个特征：一是其形参数量与本次调用提供的实参数量相等，二是每个实参的类型与对应的形参类型相同，或者能转换成形参的类型。

如果函数含有默认实参，则我们在调用该函数时传入的实参数量可能少于它实际使用的实参数量。

在使用实参数量初步判别了候选函数后，接下来考察实参的类型是否与形参匹配。和一般的函数调用类似，实参与形参匹配的含义可能是他们具有相同的类型，也可能是实参类型和形参类型满足转换规则。

如果没找到可行函数，编译器将报告无匹配函数的错误。

### 寻找最佳匹配(如果有的话)
函数匹配的第三步是从可行函数中选择与本次调用最匹配的函数。在这一过程中，逐一检查函数调用提供的实参，寻找形参类型与实参类型最匹配的哪个可行函数。基本思想是，实参类型与形参类型越接近，匹配程度越高。

### 含有多个形参的函数匹配
当实参的数量有两个或更多时，函数匹配就比较复杂了。

该函数每个实参的匹配都不劣于其他可行函数需要的匹配。

至少有一个实参的匹配优于其他可行函数提供的匹配。

如果在检查了所有实参之后没有任何一个函数脱颖而出，则该调用是错误的。编译器将报告二义性调用的信息。

调用重载函数时应尽量避免强制类型转换。如果在实际应用中确实需要强制类型转换，则说明我们设计的形参集合不合理。

### 实参类型转换
为了确定最佳匹配，编译器将实参类型到形参类型的转换划分成几个等级，具体排序如下：

1：精确匹配：实参类型和形参类型相同；实参从数组类型或函数类型转换成对应的指针类型；向实参添加顶层const或从实参中删除顶层const。

2：通过const转换实现的匹配。

3：通过类型提升实现的匹配

4：通过算术类型转换或指针转换实现的匹配。

5：通过类类型转换实现的匹配

### 需要类型提升和算数类型转换的匹配
内置类型的提升和转换可能在函数匹配时产生意想不到的结果，但幸运的是，在设计良好的系统中函数很少会含有与下面例子类似的形参。

分析函数钱，我们应该知道小整形一般都会提升到int类型或更大的整数类型。

假设有两个函数，一个接受int，另一个接受short，则只有当调用提供的是short类型的值时才会选择short版本的函数。有时候，即使实参是一个很小的整数值，也会直接将它提升成int类型；此时short版本反而会导致类型转换。

所有算数类型的转换级别都一样。

### 函数匹配和const实参
如果重载函数的区别在于他们的应用类型的形参是否引用了const，或者指针类型的形参是否指向const，则当调用发生时编译器通过实参是否是常量来决定选择哪个函数。
