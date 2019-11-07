#include "iostream"
using namespace std;

int main(int argc, char* argv[])
{
    // Test1();
    // Test2();
    // Test3();
    int a[]={1,8,9,0};
    cout << a <<endl;
    cout << &a[0] << endl;
    cout << &a << endl;            // 数组的名称取地址是其本身!!!
    cout << sizeof(a)<<endl;

    int i=0;
    int *p = &i;
    cout << p << endl;
    cout << &p << endl;


    return 0;
}