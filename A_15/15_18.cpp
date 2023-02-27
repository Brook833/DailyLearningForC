/*
Base *p = &d1;  // 合法
p = &d2;        // 非法, 用户代码无法访问private
p = &d3;        // 非法, 用户代码无法访问protected
p = &dd1;       // 合法
p = &dd2;       // 非法
p = &dd3;       // 非法
*/