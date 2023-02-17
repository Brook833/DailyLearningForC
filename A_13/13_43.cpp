/*
for_each(elements, first_free, [this](std::string &rhs){ alloc.destroy(&rhs); });
这个版本更好,这个版本只需要指出范围，和元素执行什么操作即可。

而for版本还需要控制指针的增减。
*/
