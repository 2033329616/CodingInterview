/* 
题目：数组长度为n+1，元素属于[1,n]，存在至少一个重复元素，不修改输入数组的情况下，找到重复元素
思路：
    1. 创建一个新的数组，使用(3)中修改数组的方法来找到任意的重复元素；  空间o(n)，时间o(n)
    2. 设如果前m个元素无重复数字，则小于等于m的元素最多有m个，使用二分法将1~n分成两个部分[1,m]与[m+1,n]，
       比较[1,m]范围内数字出现次数大于m，则重复元素在该范围，否则在[m+1,n]中； 空间o(1) 时间o(nlogn)
存在问题：
    只能发现任意的重复数字，无法找到所有的重复数字，如{2,3,5,4,3,2,6,7}只能找到3为重复数字，找不到2，
    可以使用哈希表统计各个元素的次数来发现重复数字
*/

#include "cstdio"
#include "iostream"
using namespace std;

// 统计在[start,end]范围内元素出现的次数
int countRange(const int array[], int length, int start, int end)
{
    if (array == nullptr || length <= 0)
        return 0;
    int count = 0;
    for (int i = 0; i < length; i++)                       // 需要遍历整个数组来进行次数统计
    {
        if (array[i] >= start && array[i] <= end)          // 统计特点范围的元素
            count++;
    }
    return count;
}

// 找到任意重复的元素并返回
int getDuplication(const int* array, int length)      // 数组作为参数，使用int* array或int array[]一样，都是指针的形式传入
{
    if (array == nullptr || length <= 0)
        return -1;
    int start = 1;
    int end = length - 1;
    while (start <= end)
    {
        int middle = (start + end) / 2;                           // 二分法求中间值
        // int middle = ((end - start) >> 1) + start;             // 同上
        int count = countRange(array, length, start, middle);     // 求[start,middle]内元素的出现次数

        if (start == end)                                         // 统计某一个数字
        {
            if (count > 1)
                return start;
            else
            {
                break;                                            // 没有找到重复数字
                // return -1;     
            } 
        }

        if (count > (middle - start + 1))                        // 不加括号也可以, '>'优先级小于算术运算符
            end = middle;
        else
            start = middle + 1;
    }
    return -1;                                                    // 循环结束还没有找到重复数字
}


// ====================测试代码====================
void test(const char* testName, int* numbers, int length, int* duplications, int dupLength)
{
    int result = getDuplication(numbers, length);
    for(int i = 0; i < dupLength; ++i)
    {
        if(result == duplications[i])
        {
            std::cout << testName << " passed." << std::endl;
            return;
        }
    }
    std::cout << testName << " FAILED." << std::endl;
}

// 多个重复的数字
void test1()
{
    int numbers[] = { 2, 3, 5, 4, 3, 2, 6, 7 };
    int duplications[] = { 2, 3 };
    test("test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个重复的数字
void test2()
{
    int numbers[] = { 3, 2, 1, 4, 4, 5, 6, 7 };
    int duplications[] = { 4 };
    test("test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最小的数字
void test3()
{
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 1, 8 };
    int duplications[] = { 1 };
    test("test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字是数组中最大的数字
void test4()
{
    int numbers[] = { 1, 7, 3, 4, 5, 6, 8, 2, 8 };
    int duplications[] = { 8 };
    test("test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 数组中只有两个数字
void test5()
{
    int numbers[] = { 1, 1 };
    int duplications[] = { 1 };
    test("test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 重复的数字位于数组当中
void test6()
{
    int numbers[] = { 3, 2, 1, 3, 4, 5, 6, 7 };
    int duplications[] = { 3 };
    test("test6", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 多个重复的数字
void test7()
{
    int numbers[] = { 1, 2, 2, 6, 4, 5, 6 };
    int duplications[] = { 2, 6 };
    test("test7", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 一个数字重复三次
void test8()
{
    int numbers[] = { 1, 2, 2, 6, 4, 5, 2 };
    int duplications[] = { 2 };
    test("test8", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 没有重复的数字
void test9()
{
    int numbers[] = { 1, 2, 6, 4, 5, 3 };
    int duplications[] = { -1 };
    test("test9", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}

// 无效的输入
void test10()
{
    int* numbers = nullptr;
    int duplications[] = { -1 };
    test("test10", numbers, 0, duplications, sizeof(duplications) / sizeof(int));
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    return 0;
}