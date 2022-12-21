// unique_ptr独占对象的所有权，不能拷贝和赋值。release操作是用来将对象的所有权转移给另一个unique_ptr的。
// 多个shared_ptr可以共享所有权。需要共享时，可以简单拷贝和赋值。因此，并不需要release这样的操作来转移所有权