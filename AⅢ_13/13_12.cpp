// return item1.isbn() != item2.isbn();

// 有三次析构函数调用

// 函数结束时，item1, item2, accum生命期均结束了，均被销毁，调用Sales_data的析构函数

// 函数结束时，trans的生命期也结束了，但它是Sales_data的指针，并不是它指向的Sales_data对象的生命期结束(只有delete指针时，指向的动态对象的生命期才结束)，所以不会引起析构函数的调用。