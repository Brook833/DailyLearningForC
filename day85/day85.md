2022.12.11



## 11.3.5 访问元素
关联容器提供多种查找一个指定元素的方法，如表11.7所示。应该使用哪个操作依赖于我们要解决什么问题。如果我们所关心的只不过是一个特定元素是否已在容器中，可能find是最佳选择。对于不允许重复关键字的容器，可能使用find还是count没什么区别。但对于允许重复关键字的容器，count还会做更多的工作:如果元素在容器中，它还会统计有多少个元素有相同的关键字。如果不需要奇数，最好使用find:

```c++
set<int> iset = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
iset.find(1);  // 返回一个迭代器，指向key == 1的元素
iset.find(11);  // 返回一个迭代器，指向iset.end()
iset.count(1);  // 返回1
iset.count(11);  // 返回0
```

| **表11.7: 在一个关联容器中查找元素的操作** |  |
|:- |:- |
| lower_bond和upper_bound不适用于无序容器 |  |
| 下标和at操作只适用于非const的map和unordered_map |  |
| c.find(k) | 返回一个迭代器，指向第一个关键字为k的元素，若k不在容器中，则返回尾后迭代器 |
| c.count(k) | 返回关键字等于k的元素的数量。对于不允许重复关键字的容器，返回值永远是0或1 |
| c.lower_bound(k) | 返回一个迭代器，指向第一个关键字不小于k的元素 |
| c.upper_bound(k) | 返回一个迭代器，指向第一个关键字大于kd的元素 |
| c.equal_range(k) | 返回一个迭代器pair，表示关键字等于k的元素的范围。若k不存在，pair的两个成员均等于c.end() |

### 对map使用find操作代替下标操作
对map和unordered_map类型，下标运算符提供了最简单的提取元素的方法。但是，如我们所见，使用下标操作有一个严重的副作用:如果关键字还未在map中，下标操作会插入一个具有给定关键字的元素。这种行为是否正确完全依赖于我们的预期是什么。例如，单词计数程序依赖于这样一个特性:使用一个不存在的关键字作为下标，会插入一个新元素，其关键字为给定关键字，其值为0。也就是说，下标操作的行为符合我们的预期。

但有时，我们只是想知道一个给定关键字是否在map中，而不想改变map。这样就不能使用下标运算符来检查一个元素是否存在，因为如果关键字不存在的话，下标运算符会插入一个新元素。在这种情况下，应该使用find:

```c++
if (word_count.find("foobar") == word_count.end()) {
    cout << "foobar is not in the map" << endl;
}
```

### 在multimap或multiset中查找元素
在一个不允许重复关键字的关联容器中查找一个元素是一件很简单的事情————元素要么在容器中，要么不在。但对于允许重复关键字的容器来说，过程就更为复杂:在容器中可能有很多元素具有给定的关键字。如果一个multimap或multiset中有多个元素具有给定关键字，则这些元素在容器中会相邻存储。

例如，给定一个从作者到著作题目的映射，我们可能想打印一个特定作者的所有著作。可以用三种不同方法来解决这个问题。最直观的方法是使用find和count:

```c++
string search_item("Alain de Botton");  // 要查找的作者
auto entries = authors.count(search_item);  // 元素的数量
auto iter = authors.find(serach_item);  // 此作者的第一本书
// 用一个循环查找此作者的所有著作
while(entries) {
    cout << iter->second << endl;  // 打印著作名
    ++iter;  // 前进到下一本书
    --entries;  // 记录已经打印了多少本书
}
```

首先调用count确定此作者共有多少本著作，并调用find获得一个迭代器，指向第一个关键字为此作者的元素。for循环的迭代次数依赖于count的返回值。特别是，如果count返回0,则循环一次也不执行。

**Note: 当我们遍历一个multimap或multiset时，保证可以得到序列中所有具有给定关键字的元素**

### 一种不同的，面向迭代器的解决方法
我们还可以用lower_bound和upper_bound来解决此问题。这两个操作都接受一个关键字，返回一个迭代器。如果关键字在容器中,lower_bound返回的迭代器将指向第一个具有给定关键字的元素，而upper_bound返回的迭代器则指向最后一个匹配给定关键字的元素之后的位置。如果元素不在multimap中，则lower_bound和upper_bound会返回相等的迭代器——————指向一个不影响排序的关键字插入位置。因此，用相同的关键字调用lower_bound和upper_bound会得到一个迭代器范围，表示所有具有该关键字的元素的返回。

当然，这两个操作返回的迭代器可能是容器的尾后迭代器。如果我们查找的元素具有容器中最大的关键字，则此关键字的upper_bound返回尾后迭代器。如果关键字不存在，且大于容器中任何关键字，则lower_bound返回的也是尾后迭代器。

**Note:low_bound返回的迭代器可能指向一个具有给定关键字的元素，但也可能不指向。如果关键字不在容器中，则lower_bound会返回关键字的第一个安全插入点————不影响容器中元素顺序的插入位置。**

使用这两个操作，我们可以重写前面的程序:

```c++
// authors和search_item定义与之前一样。
// beg和end表示对应此作者的元素的范围
for (auto beg = authors.lower_bound(search_item), end = authors.upper_bound(search_item); beg != end; ++beg) {
    cout << beg->second << endl;
}
```

此程序与使用count和find的版本完成相同的工作，但更直接。对lower_bound的调用将beg定位到第一个与search_item的元素，有可能是尾后迭代器。upper_bound调用将end指向最后一个匹配指定关键字的元素之后的元素。这两个操作并不报告关键字是否存在，重要的是它们的返回值可作为一个迭代器范围。

如果没有元素与给定的关键字匹配，则lower_bound和upper_bound会返回相等的迭代器————都指向给定关键字的插入点，能保持容器中元素顺序的插入位置。

假定有多个元素与给定关键字匹配，beg将指向其中第一个元素。我们可以通过递增beg来遍历这些元素。end中的迭代器绘制出何时完成遍历————dang beg等于end时，就表明已经遍历了所有匹配给定关键字的元素了。

由于这两个迭代器构成一个范围，我们可以用一个for循环来遍历这个范围。循环可能执行零次，如果存在给定作者的话，就会执行多次，打印出该作者的所有作品。如果给定作者不存在，beg和end相等，循环就一次也不会执行。否则，我们知道递增beg最终会使它到达end，在此过程中我们就会打印出与此作者关联的每条记录。

**Note: 如果lower_bound和upper_bound返回相同的迭代器，则给定关键字不在容器中。**

### equal_range函数
解决此问题的最后一种方法时三种方法中最直接的:不必再调用upper_bound和lower_bound，直接调用equla_range即可。此函数接受一个关键字，返回一个迭代器pair。如果关键字存在，则第一个迭代器指向第一个与关键字匹配的元素，第二个迭代器指向最后一个匹配元素之后的位置。若未找到该元素，则两个迭代器都指向关键字可以插入的位置。

可以用equal_range来再次修改我们的程序:

```c++
// authors和search_item定义与之前一样。
// pos保存迭代器对，表示与关键字匹配的元素范围
for(auto pos = authors.equal_range(search_item); pos.first != pos.second; ++pos.first) {
    cout << pos.first->second << endl;
}
```

此程序本质上与前一个使用lower_bound和upper_bound的成v是一样的。不同之处就是，没有用局部变量beg和end来保存元素范围，而是使用了equal_range返回的pair。此pair的first成员保存的迭代器与lower_bound返回的迭代器是一样的，second保存的迭代器与upper_bound的返回值是一样的。因此，pos.first等价于beg，pos.second等价于end。
