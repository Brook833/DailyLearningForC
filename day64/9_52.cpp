#include <stack>
using std::stack;

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

int main() {
    string expr = "This is (Mooophy(awesome)((((wooooooooo))))) and (ocxs) over";
    char repl = '#';
    int seen = 0;

    stack<char> stk;

    for (int i = 0; i < expr.length(); ++i) {   // 不包含字符串结束符 '\0'
        stk.push(expr[i]);
        if (expr[i] == '(')
            ++seen;                             // 左括号计数
        if (seen && expr[i] == ')') {           // 若左括号计数非零且当前字符是右括号
            while (stk.top() != '(')            // 判断栈顶字符是否是左括号
                stk.pop();                      // 若不是左括号字符，循环删除栈顶字符

            stk.pop();                          // 删除栈顶的左括号
            stk.push(repl);                     // 替换字符 '#' 入栈
            --seen;                             // 左括号计数减 1
        }
    }

    // 测试
    string str;                                 // 定义空串，用于存放栈中字符
    while (!stk.empty()) {
        // top 函数返回栈顶元素，但不将元素弹出栈
        str.insert(str.begin(), stk.top());
        // pop 函数删除栈顶元素，但不返回该元素值
        stk.pop();
    }

    
    cout << str << endl;

    system("pause");
    return 0;
}
