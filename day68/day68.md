2022.11.24



## 重排容器元素的算法
某些算法会重排容器中元素的顺序，一个明显的例子是sort。调用sort会重排输入序列中的元素，使之有序，它是利用元素类型的<运算符来实现排序的。

例如，假定我们想分析一系列儿童故事中所用的词汇。假定已有一个vector，保存了多个故事的文本。我们希望化简这个vector，使得每个单词只出现一次，而不管单词在任意给定文档中到此出现了多少次。

为了便于说明问题，我们将使用下面简单的故事作为输入:

```c++
the quick red fox jumps over the slow red turtle
```

给定此输入，我们的程序应该生成如下vector:

```c++
fox jumps over quick red slow the turtle
```

### 消除重复单词
为了消除重复单词，首先将vector排序，使得重复的单词都相邻出现。一旦vector排序完毕，我们就可以使用另一个称为unique的标准算法来重排vector，使得不重复的元素出现在vector的开始部分。由于算法不能执行容器的操作，我们将使用vector的erase成员来完成真正的删除操作:

```c++
void elimDups(vector<string> &words) {
    // 按字典序排序words，以便查找重复单词
    sort(words.begin(), words.end());
    // unique重排输入范围，使得每个单词只出现一次
    // 排列在范围的前部，返回指向不重复区域之后一个位置的迭代器
    auto end_unique = unique(words.begin(), words.end());
    // 使用向量操作erase删除重复单词
    words.erase(end_unique, words.end());
}
```

sort算法接受两个迭代器，表示要排序的元素范围。在此例中，我们排序整个vector。完成sort后，words的顺序如下所示:

```c++
fox jumps over quick red red slow the the turtle
```

注意，单词red和the各出现了两次。

### 使用unique
words排序完毕后，我们希望将每个单词都只保存一次。unique算法重排输入序列，将相邻的重复项"消除"，并返回一个指向不重复值末尾的迭代器。调用unique后，vector将变为:

```c++
fox jumps over quick red slow the turtle ??? ???
```

words的大小并未改变，他仍有10个元素。但这些元素的顺序被改变了————相邻的重复元素被"删除"了。我们将删除打引号是因为unique并不真的删除任何元素，它只是覆盖相邻的重复元素，使得不重复元素出现在序列开始部分。unique返回的迭代器指向最后一个不重复元素之后的位置。此位置之后的元素仍然存在，但我们不知道它们的值是什么。

**Note: 标准库算法对迭代器而不是容器进行操作。因此，算法不能(直接)添加或删除元素。**

### 使用容器操作删除元素
为了真正地删除无用元素，我们必须使用容器操作，本例中使用erase。我们删除从end_unique开始直至words末尾的范围内地所有元素。这个调用之后，words包含来自输入的8个不重复的单词。

值得注意的是，即使words中没有重复单词，这样调用erase也是安全的。在此情况下，unique会返回words.end()。因此，传递给erase的两个参数具有相同的值:words.end()。迭代器相等意味着传递给erase的元素范围为空。删除一个空范围没有什么不良后果，因此程序即使在输入中无重复元素的情况下也是正确的。