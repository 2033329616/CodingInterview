// 数组长度为n，元素属于[0,n-1]，存在重复元素

#include "iostream"
#include "cstdio"
using namespace std;

// 只能找到数组中任意一个重复的数字，无法找到全部重复的数字

bool duplicate(int array[], int length, int* duplication)
{
    // 先判断是否有边界值，如指针是否为空，数组长度是否为整数
    if (array == nullptr || length <= 0)
    {
        return false;
    }

    // 判断数组内的数组范围是否在[0,length-1]内
    for (int i=0; i<length; i++)
    {
        if (array[i]<0 || array[i]>length-1)
            return false;
    }

    // 开始判断有无重复的数字
    for (int i=0; i<length;i++)
    {
        while (array[i] != i)                      // ！！！当前的数字不等于下标时一直进行数字交换，直到两者相等后再i++
        {
            if (array[i] == array[array[i]])       // 索引为i的数字与索引为array[i]的数字相等，发现重复数字
               {
                    *duplication = array[i];       // 将重复的数字赋值给duplication指针指向的位置
                    return true;
               } 
            // 没有发现array[i]与i索引对应的值重复，交换array[i]与array[array[i]]的位置
            int temp = array[i];
            array[i] = array[temp];
            array[temp] = temp;
        }
    }
    return false;                                  // 遍历完数组后，并没有返回，因此无重复数字
}

// ====================测试代码====================
bool contains(int array[], int length, int number)
{
    for(int i = 0; i < length; ++i)
    {
        if(array[i] == number)
            return true;
    }

    return false;
}

void test(char* testName, int numbers[], int lengthNumbers, int expected[], int expectedExpected, bool validArgument)
{
    printf("%s begins: ", testName);

    int duplication;
    bool validInput = duplicate(numbers, lengthNumbers, &duplication);

    if(validArgument == validInput)
    {
        if(validArgument)
        {
            if(contains(expected, expectedExpected, duplication))
                printf("Passed.\n");
            else
                printf("FAILED.\n");
        }
        else
            printf("Passed.\n");
    }
    else
        printf("FAILED.\n");
}

// 重复的数字是数组中最小的数字
void test1()
{
    int numbers[] = { 2, 1, 3, 1, 4 };
    int duplications[] = { 1 };
    test((char*)"Test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 重复的数字是数组中最大的数字
void test2()
{
    int numbers[] = { 2, 4, 3, 1, 4 };
    int duplications[] = { 4 };
    test((char*)"Test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 数组中存在多个重复的数字
void test3()
{
    int numbers[] = { 2, 4, 2, 1, 4 };
    int duplications[] = { 2, 4 };
    test((char*)"Test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 没有重复的数字
void test4()
{
    int numbers[] = { 2, 1, 3, 0, 4 };
    int duplications[] = { -1 }; // not in use in the test function
    test((char*)"Test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}

// 没有重复的数字
void test5()
{
    int numbers[] = { 2, 1, 3, 5, 4 };
    int duplications[] = { -1 }; // not in use in the test function
    test((char*)"Test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}

// 无效的输入
void test6()
{
    int* numbers = nullptr;
    int duplications[] = { -1 }; // not in use in the test function
    test((char*)"Test6", numbers, 0, duplications, sizeof(duplications) / sizeof(int), false);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}