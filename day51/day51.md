2022.11.06



## 文件输入输出
头文件fstream定义了三个类型来支持文件IO：ifstream可以从一个给定文件读取数据，ofstream向一个给定文件写入数据，以及fstream可以读写给定文件。

这些类型提供的操作操作与我们之前使用过的对象cin和cout的操作一样。特别是，我们可以用IO运算符(<<和>>)来读写文件，可以用getline从一个ifstream读取数据。

除了继承自iostream类型的行为之外，fstream中定义的类型还增加了一些新的成员来管理与流关联的文件。我们可以对fstream、ifstream和ofstream对象调用这些操作，但不能对其他IO类型调用这些操作。

fstream特有的操作：

fstream fstrm;  创建一个未绑定的文件流。

fstream fstrm(s);  创建一个fstream，并打开名为s的文件。s可以是string类型，或者是一个指向C风格字符串的指针。这些构造函数都是explicit的。默认的文件模式mode依赖于fstream的类型

fstream fstrm(s, mode);  与前一个构造函数类似，但按指定mode打开文件。

fstrm.open(s)  打开名为s的文件，并将文件与fstrm绑定。s可以是一个string或一个指向C风格字符串。默认的文件mode依赖于fstream的类型。返回void。

fstrm.close()  关闭与fstrm绑定的文件。返回void

fstrm.is_open()  返回一个bool值，指出与fstrm关联的文件是否成功打开且尚未关闭

### 使用文件流对象
当我们想要读写一个文件时，可以定义成一个文件流对象，并将对象与文件关联起来。每个文件流类都定义了一个名为open的成员函数，它完成一些系统相关的操作，来定位给定的文件，并视情况打开为读或写模式.

创建文件流对象时，我们可以提供文件名(可选的)。如果是提供了一个文件名，则open会自动被调用:

```c++
ifstream in(ifile);  //构造一个ifstream并打开给定文件
ofstream out;  //输出文件流未关联到任何文件
```

这段代码定义了一个输入流in，它被初始化为从文件读取数据，文件名为string类型的参数ifile指定。第二条语句定义了一个输出流out，未与任何文件关联。在新C++标准中，文件名既可以是库类型string对象，也可以是C风格字符数组。旧版本的标准库只允许C风格字符数组。

### 用fstream代替iostream&
在要求使用基类型对象的地方，我们可以用继承类型的对象来替代。这意味着，接受一个iostream类型引用(或指针)参数的函数可以用一个对应的fstream(或sstream)类型来调用。也就是说，如果有一个函数接受一个ostream&参数，我们在调用这个函数时，可以传递给它一个ofstream对象，对istream&和ifstream也是类似的。

例如，我们可以用read和print函数来读写命名文件。我们假定输入和输出文件的名字是通过传递给main函数的参数来指定的:

```c++
ifstream input(argv[1]);   // 打开销售记录文件
ofstream output(argv[2]);  // 打开输出文件
Sales_data total;          // 保存销售总额的变量
if (read(input, total)) {  // 读取第一天销售记录
    Sales_data trans;      // 保存下一条销售记录的变量
    while(read(input, trans)) {           // 读取剩余记录
        if (total.isbn() == trans.isbd()) // 检查isbn
            total.combine(trans);         // 更新销售总额
        else {
            print (output, total) << endl;  // 打印结果
            total = trans;                  // 处理下一本书
        }
    }
    print(output, total) << endl;           // 打印最后一本书的销售额
} else {                   //w 文件中无输入数据
    cerr << "No data?!" << endl;
}
```

虽然两个函数定义时指定的形参分别是istream&和ostream&，但我们可以向它们传递fstream对象。

### 成员函数open和close
如果我们定义了一个空文件流对象，可以随后调用open来将它与文件关联起来：

```c++
ifstream in(ifile);  // 构筑一个ifstream并打开给定文件
ofstream out;        // 输出文件流未与任何文件相关联
out.open(ifile + ".copy");  // 打开指定文件
```

如果调用open失败，failbit会被置位。因为调用open可能失败，进行open是否成功的检测通常是一个好习惯：

```c++
if (out)  // 检查open是否成功
          // open成功，我们可以使用文件了
```

这个条件判断与我们之前将cin用作条件相似。如果open失败，条件会为假，我们就不会去使用out了。

一旦一个文件流已经打开，他就保持与对应文件的关联。实际上，对一个已经打开的文件流调用open会失败，并会导致failbit被置位。随后的试图使用文件流的操作都会失败。为了将文件流关联到另外一个文件，必须首先关闭已经关联的文件。一旦文件成功关闭，我们可以打开新的文件:

```c++
in.close();  // 关闭文件
in.open(ifile + "2"); // 打开另一个文件
```

如果open成功，则open会设置流的状态，使得good()为true;

### 自动构造和析构
考虑这样一个程序，它的main函数接受一个要处理的文件列表。这种程序可能会有如下的循环：

```c++
// 对每个传递给程序的文件执行循环操作
for (auto p = argv + 1; p != argv + argc; ++p) {
    ifstream input(*p);  // 创建输出流并打开文件
    if (input) {         // 如果文件打开成功，"处理"此文件
        process(input);
    } else {
        cerr << "couldn't open:" + string(*p);
    }
}  // 每个循环步input都会离开作用域，因此会被销毁
```

每个循环步构造一个新的名为input的ifstream对象，并打开它来读取给定的文件。像之前一样，我们检查open是否成功。如果成功，将文件传递给一个函数，该函数负责读取并处理输入数据。如果open失败，打印一条错误信息并继续处理下一个文件。

因为input是while循环的局部变量，它在每个循环步中都要创建和销毁一次。当一个fstream对象离开其作用域时，与之关联的文件会自动关闭。在下一步循环中，input会再次被创建。

Note:

当一个fstream对象被销毁时，close会自动被调用。

