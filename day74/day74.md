2022.11.30



## 10.4 再谈迭代器
除了为每个容器定义的迭代器之外，标准库在头文件iterator中还定义了额外几种迭代器。这些迭代器包括以下几种。
> + 插入迭代器(insert iterator):这些迭代器被绑定到一个容器上，可用来向容器插入元素。
> + 流迭代器(stream iterator):这些迭代器被绑定到输入或输出流上，可用来遍历所关联的IO流。
> + 反向迭代器(reverse iterator):这些迭代器向后而不是向前移动。出了forward_list之外的标准库容器都有反向迭代器。
> + 移动迭代器(move iterator):这些专用的迭代器不是拷贝其中的元素，而是移动它们。

### 10.4.1 插入迭代器
插入器是一种迭代器适配器，它接受一个容器，生成一个迭代器，能实现向给定容器添加元素。当我们通过一个插入迭代器进行赋值时，该迭代器调用容器操作来向给定容器的指定位置插入一个元素。表10.2列出了这种迭代器支持的操作。

| **表10.2:插入迭代器操作** |  |
|:- |:- |
| it = t | 在it指定的当前位置插入值t。假定c是it绑定的容器，依赖于插入迭代器的不同种类，此赋值依赖于插入迭代器的不同种类，此赋值会分别调用(c.push_back(t), c.push_front(t), c.insert(t))，其中p为传递给inserter的迭代器位置. |
| *it, ++it, it++ | 这些操作虽然存在，但不会对it做任何事情，每个操作都返回it |

插入器有三种类型，差异在于元素插入的位置:
> + back_inserter创建一个使用push_back的迭代器。
> + front_inserter创建一个使用push_front的迭代器。
> + inserter创建一个使用insert的迭代器。此函数接受第二个参数，这个参数必须是一个指向给定容器的迭代器。元素将被插入到给定迭代器所表示的元素之前

**Note: 只有在容器支持push_front的情况下，我们才可以使用front_inserter。类似的，只有在容器支持push_back的情况下，我们才能使用back_inserter。**

理解插入器的工作过程是很重要的:当调用inserter(c, iter)时，我们得到一个迭代器，接下来使用它时，会将元素插入到iter原来所指向的元素之前的位置。即，如果it是由inserter生成的迭代器，则下面的赋值语句:

```c++
*it = val;
```

其效果与下面代码一样:

```c++
it = c.insert(it, val);  // it 指向新加入的元素
++it;  // 递增it使它指向原来的元素。
```

front_inserter生成的迭代器的行为与inserter生成的迭代器完全不一样。当我们使用front_inserter时，元素总是插入到容器第一个元素之前。即使我们传递给inserter的位置指向原来第一个元素，只要我们在此元素之前插入一个新元素，此元素就不再是容器的首元素了:

```c++
list<int> 1st = {1, 2, 3, 4};
list<int> 2st, 3st;  // 空list
// 拷贝完成之后,2st包含4,3,2,1
copy(1st.cbegin(), 1st.end(), front_inserter(2st));
// 拷贝完成之后，3st包含1,2,3,4
copy(1st.cbegin(), 1st.end(), inserter_(3st, 3st.begin()));
```

当调用front_inserter(c)时，我们得到一个插入迭代器，接下来会调用push_front。当每个元素被插入到容器c中时，它变成c的新的首元素。因此，front_inserter生成的迭代器会将插入的元素序列的顺序颠倒过来，而inserter和back_inserter则不会。

