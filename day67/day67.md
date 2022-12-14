2022.11.23



## 10.2.2 写容器元素的算法
一些算法将新值赋予序列中的元素。当我们使用这类算法时，必须注意确保序列元大小至少步小于我们要求算法写入的元素的数目。记住，算法不会执行容器操作，因此它们自身不可能改变容器的大小。

一些算法会自己向输入范围写入元素。这些算法本质上并不危险，它们最多写入与给定序列一样多的元素。

例如，算法fill接受一对迭代器表示一个范围，还接受一个值作为第三个参数。fill将给定的这个值赋予输入序列中的每个元素。

```c++
fill(vec.begin(), vec.end(), 0);  // 将每个元素重置为0
// 将容器的椅子子序列设置为10
fill(vec.begin(), vec.begin() + vec.size() / 2, 10);
```

由于fill向给定输入序列中写入数据，因此，只要我们传递了一个有效的输入序列，写入操作就是安全的。

### 算法不检查写操作
一些算法接受一个迭代器来指出一个单独的目的位置。这些算法将新值赋予一个序列中的元素，该序列从目的位置迭代器指向的元素开始。例如，函数fill_n接受一个单迭代器、一个计数值和一个值。他将给定值赋予迭代器指向的元素开始的指定个元素。我们可以用fill_n将一个新值赋予vector中的元素:

```c++
vector<int> vec;  // 空vector
// 使用vec,赋予它不同值
fill_n(vec.begin(), vec.size(), 0);  // 将所有与元素重置为0
```

函数fill_n假定写入指定个元素是安全的。即，如下形式的调用

```c++
fill_n(deest, n, val);
```

fill_n假定dest指向一个元素，而从dest开始的序列至少包含n个元素。

一个初学者非常容易犯的错误是在一个空容器上调用fill_n(或类似的写元素的算法):

```c++
vector<int> vec;  // 空vector
// 灾难；修改vec中的10个(不存在)的元素
fill_n(vec.begin(), 10, 0);
```

这个调用是一场灾难。我们指定了要写入10个元素，但vector中并没有元素————它是空的。这条语句是未定义的。

### 介绍back_inserter
一种保证算法有足够元素空间来容纳输出数据的方法是使用插入迭代器(insert iterator)。插入迭代器是一种向容器中添加元素的迭代器。通常情况，当我们通过一个迭代器向容器元素赋值时，值被赋予迭代器指向的元素。而当我们通过一个插入迭代器赋值时，一个与赋值号右侧相等的元素被添加到容器中。

为了展示如何用算法向容器写入数据，我们现在将使用back_inserter，它是定义在头文件iterator中的一个函数。

back_inserter接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。当我们通过此迭代器赋值时，赋值运算符会调用push_back将一个具有给定值的元素添加到容器中:

```c++
vector<int> vec;  // 空向量
auto it = back_inserter(vec);  // 通过它赋值会将元素添加到vec中。
*it = 42;  // vec中现在有一个元素，值为42
```

我们常常使用back_inserter来创建一个迭代器，作为算法的目的位置来使用。例如:

```c++
vector<int> vec;  // 空向量
// 正确；back_inserter创建一个插入迭代器，可用来向vec添加元素
fill_n(back_inserter(vec), 10, 0);  // 添加10个元素到vec
```

在每步迭代中，fill_n向给定序列的一个元素赋值。由于我们传递的参数是一个back_inserter返回的迭代器，因此每次赋值都会在vec上调用push_back。最终，这条fill_n调用语句向vec的末尾添加了10个均为0的元素。

### 拷贝算法
拷贝算法是另一个向目的位置迭代器指向的输出序列中的元素写入数据的算法。此算法接受三个迭代器，前两个表示一个输入范围，死三个表示目的序列的起始位置。此算法将输入范围中的元素拷贝到目的序列中。传递给copy的目的序列至少要包含与输入序列一样多的元素，这一点很重要。

我们可以用copy实现内置数组的拷贝，如下面代码所示:

```c++
int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int a2[sizeof(a1)/sizeof(*a1)];  // a2与a1大小一样。
// ret指向拷贝到a2尾元素之后的位置
auto ret = copy(begin(a1), end(a1), a2);  // 把a1的内容拷贝给a2
```

此例中我们定义了一个名为a2的数组，并使用sizeof确保a2与数组a1包含同样多的元素。接下来我们调用copy完成从a1到a2的拷贝。在调用copy后，两个数组中的元素具有相同的值。

copy返回的是其目的位置迭代器(递增后)的值。即，ret恰好指向a2的尾元素之后的位置。

多个算法都提供所谓的"拷贝"版本。这些算法计算新元素的值，但不会将他们放置在输入序列的末尾，而是创建一个新序列保存这些结果。

例如，replace算法读入一个序列，并将其中所有等于给定值的元素都改为另一个值。此算法接受4个参数，前两个是迭代器，表示输入序列，后两个一个是要搜索的值，另一个是新值。他将所有等于要所搜的值替换为新值:

```c++
// 将所有为0的元素改为42
replace(ilst.begin(), ilst.end(), 0, 42);
```

此调用将序列中所有的0都替换为42。如果我们希望原序列不变，可以调用replace_copy。此算法接受额外第三个迭代器参数，指出挑中后序列的保存位置:

```c++
// 使用back_insterer按需要增长目标序列
replace_copy(ilst.cbegin(), ilst.cend(), back_inserter(ivec), 0, 42);
```

此调用后，ilst并未改变，ivec包含ilst的一份拷贝，不过原来ilst中值为0的元素在ivec中都变为42。
