#include "iostream"

using namespace std;

class A
{
private:
    int value;
public:
    A(int n) {value=n;}                                // 构造函数
    A(const A& other) {value=other.value;}             // 复制构造函数，形参必须是对象的引用

    void Print() {std::cout<<value<<std::endl;}
};

int main(int argc, char *argv[])
{
    A a(10);           // a = 10;也可以初始化
    A b = a;
    b.Print();
    for (int i=0;i<10;i++)
    {
        // std::cout<<i<<std::endl;
        cout<<i<<endl;
    }
    return 0;

}