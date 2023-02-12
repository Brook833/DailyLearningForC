/*
我们需要将给定Folder指针添加到当前Message的folders集合中。
这样，参数类型就不能是Folder，必须是引用类型。否则，调用save时会将实参拷贝给形参。
其次，我们需要调用addMsg将当前Message的指针添加到Folder的message集合中，
这意味着我们修改了Folder的内容，因此不能是const的。
*/