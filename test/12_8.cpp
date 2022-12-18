// 从程序片段看，可以猜测程序员的意图是通过new返回的指针值来区分内存分配成功或失败————成功返回一个合法指针，转换为整形是一个非0值，即true。p得到nullptr，其整型值为0，可转换为false。
// 但普通new调用在分配失败时抛出一个异常bad_alloc，而不是返回nullptr。
// 可将new int 改为 new (nothrow) int 来令new在分配失败时不抛出异常，而是返回nullptr。
// 但这仍然不是一个好办法，应该通过捕获异常或是判断返回的指针来返回true或false。