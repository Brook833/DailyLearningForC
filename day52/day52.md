2022.11.07



## 文件模式
每个流都有一个关联的文件模式(file mode)，用来指出如何使用文件。

in   以读的方式打开

out  以写的方式打开

app  每次写操作前均定位到文件末尾

ate  打开文件后立即定位到文件末尾

trunc  截断文件

binary  以二进制方式进行IO

无论用哪种方式打开文件，我们都可以指定文件模式，调用open打开文件时可以，用一个文件名初始化流来隐式打开文件时也可以。制定文件模式有如下限制：

只可以对ofstream或fstream对象设定out模式。

只可以对ifstream货fstream对象设定in模式。

只有当out也被设定时才可设定trunc模式。

只要trunc没被设定，就可以设定app模式。在app模式下，及时没有显式指定out模式，文件也总是以输出方式被打开。

只要trunc没被设定，就可以设定app模式。在app模式下，及时没有显式指定out模式，文件也总是以输出方式被打开。

默认情况下，即使我们没有指定trunc，以out模式打开的文件也会被阶段。为了保留以out模式打开的文件内容，我们必须同时指定app模式，这样只会将数据追加写到文件末尾；或者同时指定in模式，几打开文件的同时进行读写操作。

ate和binary模式可用于任何类型的文件流对象，且可以与其他任何文件模式组合使用。

每个文件流类型都定义了一个默认的文件模式，当我们未指定文件模式时，就使用此默认模式。与ifstream关联的文件默认以in模式打开；与ofstream关联的文件默认以out模式打开；与fstream关联的文件默认以in和out模式打开。

### 以out模式打开文件会丢失已有数据
默认情况下，当我们打开一个ofstream时，文件的内容会被丢弃。组织一个ofstream清空给定文件内容的方法是同时指定app模式：

```c++
//在这几条语句中，file1都被截断
ofstream out("file1");  // 隐式以输出模式打开文件并截断文件
ofstream out2("file1", ofstream::out);  // 隐式的截断文件
ofstream out3("file1", ofstream::out | ofstream::trunc);
//为了保留文件内容，我们必须显式指定app模式
ofstream app("file2", ofstream::app);  // 隐含为输出模式
ofstream app("file2", ofstream::out | ofsteam::app);
```

保留被ofstream打开的文件中已有数据的唯一方法是显式指定app或in模式。

### 每次调用open时都会确定文件模式
对于一个给定流，每当打开文件时，都可以改变其文件模式。

```c++
ofstream out;  // 未指定文件打开模式。
out.open("scratchpad");  // 模式隐含设置为输出和截断
out.close();  // 关闭out,以便我们将其用于其他文件。
out.open("precious", ofstream::app);  // 模式为输出和追加
out.close();
```

第一个open调用未显式指定输出模式，文件隐式地以out模式打开。通常情况下，out模式意味着同时使用trunc模式。因此，当前目录下名为scratchpad的文件的内容将被清空。当打开名为precious的文件时，我们指定了append模式。文件中已有的数据都得以保留，所有写操作都在文件末尾进行。

Note:

在每次打开文件时，都要设置文件模式，可能是显式设置，也可能是隐式设置。当程序未指定模式时，就是用默认值。

## string流
sstream头文件定义了三个类型来支持内存IO，这些类型可以向string写入数据，从string读取数据，就像string是一个IO流一样。

istringstream从string读取数据，ostringstream向string写入数据，而头文件stringsstream既可以从string读数据也可以向string写数据。与fstream类型类似，头文件sstream中定义的类型都继承自iostream头文件中定义的类型。出了继承得来的操作，sstream定义的类型还增加了一些成员来管理与流相关联的string。可以对stringstream对象调用这些操作，但不能对其他IO类型调用这些操作。

sstream strm;  strm是一个未绑定的stringstream对象。

sstream strm(s);  strm收哦呵sstream对象，保存string s的一个拷贝。

strm.str()  返回strm所保存的string的拷贝

strm.str(s)  将string s拷贝到strm中，返回void

### 使用istringstream
当我们的某些工作是对整行文本进行处理，而其他一些工作是处理行内的单个单词时，通常可以使用istringstream。

考虑这样一个例子，假定有一个文件，列出了一些人和他们的电话号码。某些人只有一个号码，而另一些人则由多个家庭电话、工作电话、移动电话等。我们的输入文件看起来可能是这样的：

```
morgan 2015552368 8625550123
drew 9735550130
lee 6095550132 2015550175 8005550000
```

文件中每条记录都以一个人名开始，后面跟随一个或多个电话号码。我们首先定义一个简单的类来描述输入数据：

```c++
//成员默认共有
struct PersonInfo {
    string name;
    vector<string> phones;
};
```
类型PersonInfo的对象会有一个成员来表示人名，还有一个vector来保存此人的所有电话号码。

我们的程序会读取数据文件，并创建一个PersonInfo的vector。vector中每个元素对应文件中的一条记录。我们在一个循环中处理输入数据，每个循环步读取一条记录，提取出一个人名和若干电话号码：

```c++
string line, word;  //分别保存来自输入的一行和单词
vector<PersonInfo> people;  // 保存来自输入的所有记录
//逐行从输入读取数据，直至cin遇到文件尾(或其他错误)
while (getline(cin, line)) {
    PersonInfo info;  // 创建一个保存此记录数据的对象
    istringstream record(line);  // 将记录绑定到刚读入的行
    record >> info.name;  // 读取名字
    while (record >> word) {  // 读取电话号码
        info.phones.push_back(word);  // 保持它们
    }
    people.push_back(info);  //  将此纪录追加到people末尾
}
```

这里我们用getline从标准输入读取整条记录。如果getline调用成功，那么line中将保存这从输入文件而来的一条记录。在while中，我们定义了一个局部PersonInfo对象，来保存当前记录中的数据。

接下来我们将一个istringstream与刚刚读取的文本行进行绑定，这样就可以在此istringstream上使用输入运算符来读取当前记录中的每个元素。我们首先读取人名，随后用一个whileu循环来读取此人的电话号码。

当读取完line中所有数据后，内层while循环就结束了。此循环的工作方式与前面章节中读取cin的循环很相似，不同之处是，此循环是从一个string而不是标准输入读取数据。当string中的数据全部读出后，同样会触发“文件结束”信号，在record上的下一个输入操作会失败。

我们将刚刚处理好的PersonInfo追加到vector中，外层while循环的一个循环步就随之结束了。外层while循环会继续执行，直至遇到cin的文件结束标识。

