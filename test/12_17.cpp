// a:错误,unique_ptr需要用一个指针初始化，而不是int
// b:可以编译通过，但是执行报错。智能指针和内置类型结合使用，当p1超出作用域时，智能指针会调用delete，但该对象不是new分配的。
// c:可以编译通过，但是执行报错。当p2超出作用域时，会释放掉内存。导致pi2变为悬空指针
// d:同b
// e:正确
// f:错误，不能使用get()的返回值初始化或赋值