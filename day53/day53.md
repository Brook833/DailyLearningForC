2022.11.08



### 使用ostringstream
当我们逐步构造输出，希望最后一起打印时，ostringstream是很有用的。例如，我们可能想逐个验证电话号码并改变格式。如果所有号码都是有效的，我们希望输出一个新的文件，包含改变格式后的号码。对于那些无效号码，我们不会将他们输出到新文件中，而是打印一条包含人名和无效号码的错误信息。

由于我们不希望输出有无效电话号码的人，因此对每个人，直到验证完所有电话号码后才可以进行输出操作。但是，我们可以先将输出内容“写入到”一个内存ostringstream中：

```c++
for (const auto &entry : people) { // 对people中每一项
    ostringstream formatted, badNums;  // 每个循环步创建的对象
    for (const auto &nums : entry.phones) {  // 对每个数
        if (!valid(nums)) {
            badNums << " " << nums;  // 将数的字符串形式存入badNums
        } else // 将格式化的字符串"写入"formatted
        formatted << " " << format(nums);
    }
    if (badNums.str().empty()) { // 没有错误的数
        os << entry.name << " " << formatted.str() << endl;  // 打印名字和格式化数
    } else { // 否则，打印名字和错误的数
        cerr << "input error: " << entry.name << " invalid number(s) " << badNums.str() << endl;
    }
}
```

在此程序中，我们假定已有两个函数，valid和format，分别完成电话号码验证和改变格式的功能。程序最有趣的部分是对字符串流formatted和badNums的使用。我们使用标准的输出运算符(<<)向这些对象写入数据，但这些写入操作，实际上转换为string操作，分别向formatted和badNums中的string对象添加字符。