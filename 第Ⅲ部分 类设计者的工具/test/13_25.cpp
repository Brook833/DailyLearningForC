/*
由于希望StrBlob的行为像值一样，因此我们应该将数据string的vector拷贝一份，使得两个StrBlob对象指向各自的数据，而不是简单得拷贝shared_ptr使得两个StrBlob指向同一个vector
*/

/*
StrBlob不需要析构函数的原因是，他管理的全部资源就是stirng的vector，二者是由shared_ptr负责管理的。
当一个StrBlob需要销毁时，会调用shared_ptr的析构函数，shared_ptr保证了资源分配，释放的正确性，StrBlob就不必进行相应的处理了
*/