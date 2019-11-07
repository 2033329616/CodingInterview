#include "iostream"
#include "cstring"

using namespace std;

// 定义类实现赋值运算符函数，使用字符指针来初始化
class CMyString
{
private:                                   // 如果不加标识符，默认是private
    char* m_pData;                         // m_pData是指针、地址(4个字节)，*m_pData是字符变量(1个字节)
public:          
    CMyString(char* pData=nullptr);        // 构造函数
    CMyString(const CMyString& str);       // 复制构造函数，传入地址&var表示引用 与 传入*var指针表地址(指针指向引用的对象)
    ~CMyString();                          // 析构函数

    CMyString& operator = (const CMyString& str);
    void Print();
};

CMyString::CMyString(char* pData)
{
    if(pData == nullptr)
    {
        m_pData = new char[1];             // m_pData指向字符数组的第一个元素
        m_pData[0] = '\0';                 // '\0'一般表示字符串的末尾
    }
    else
    {
        // 字符数组与字符串可以相互转换
        int length = strlen(pData);        // strlen()不包含'\0'; sizeof()包含'\0'
        m_pData = new char[length+1];      // 指针在复制操作前要开辟对应大小的空间！！！,+1为'\0'留位置
        strcpy(m_pData, pData);            // 该函数的参数均为指针，其中(char* dst, const char* src)
    }
    
}

CMyString::CMyString(const CMyString &str)
{
    int length = strlen(str.m_pData);       // m_pData至少占用1个空间
    m_pData = new char[length+1];           // new返回的是对象的指针
    strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString()
{
    delete[] m_pData;                      //delete[]可以多次调用析构函数，类中最特殊，删除对象数组
}

// 没有考虑异常安全性，无内存时new char会得到空指针，再次赋值会使程序崩溃
// CMyString& CMyString::operator = (const CMyString& str)               //参数和返回值全是引用
// {
//     if (this == &str)                     // 判断是否自己赋值自己 
//         return *this;                     // 使用*号提取该类的对象，然后返回引用
//     delete [] m_pData;                    // 删除之前的内存防止内存泄漏
//     m_pData = nullptr;                    // 不初始化空指针可以吗？？？
    
//     m_pData = new char[strlen(str.m_pData)+1];
//     strcpy(m_pData, str.m_pData);
//     return *this;
// }

// 考虑异常安全性
CMyString& CMyString::operator= (const CMyString& str)  // 异常安全的原理？？？
{
    if (this != &str)
    {
        CMyString strTemp(str);              // 创建临时的对象，if语句结束后调用析构函数释放内存
        char* pTemp = strTemp.m_pData;
        strTemp.m_pData = m_pData;           // strTemp指向m_pData，释放内存时会删除m_pData
        m_pData = pTemp;
    }
    return *this;
}  

void CMyString::Print()
{
    printf("%s", m_pData);
}
// int main()
// {
//     // char *p1 = new char;          //先开辟空间才能复制，nullptr不能赋值
    // char test = 'b';
    // const char* p2 = &test;
    // strcpy(p1, p2);
    // cout << *p1 << endl;

    // char *p3 = new char[2];         //p3指向字符数组的第一个元素
    // p3 = &test;
    // cout << *p3 << endl;          //字符数组可以通过 array[i]的形式访问
    
    // 用字符串初始化字符数组
    // char* p4[] = {"abc", "efd"};    // 有警告
    // cout << p4 <<" " << strlen(p4[0]);

    // char* p4 = (char*)"abc";           // 下面的无警告
    // // const char *p4 = "abc";
    // // char const *p4 = "abc";
//     // cout << p4 <<" " << strlen(p4);
//     cout << 23 <<endl;
//     return 0;
// }

// ====================测试代码====================
void Test1()
{
    printf("Test1 begins:\n");

    char* text = (char*)"Hello world";

    CMyString str1(text);
    CMyString str2;
    str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");
}

// 赋值给自己
void Test2()
{
    printf("Test2 begins:\n");

    char* text = (char*)"Hello world";

    CMyString str1(text);
    str1 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str1.Print();
    printf(".\n");
}

// 连续赋值
void Test3()
{
    printf("Test3 begins:\n");

    char* text = (char*)"Hello world";

    CMyString str1(text);
    CMyString str2, str3;
    str3 = str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str3.Print();
    printf(".\n");
}     

int main(int argc, char* argv[])
{
    
    Test1();
    Test2();
    Test3();
    return 0;
}