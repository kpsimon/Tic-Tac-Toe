#include <iostream>
#include <sstream>
#include <limits>
#include <set>
#include <math.h>

using namespace std;

class ArrayTest
{
    int arr[5];

    public:
        ArrayTest()
        {
            for(int i = 0; i < 5; ++i)
            {
                arr[i] = i+3;
            }
        }

        ArrayTest(int _arr[])
        {
            for(int i = 0; i < 5; ++i)
            {
                arr[i] = _arr[i];
            }
        }

        int* get_arr()
        {
            return arr;
        }

        void print_arr()
        {
            for(int i = 0; i < 5; ++i)
            {
                cout << arr[i];
            }
            cout << endl;
        }
};

void print_arr(int arr[], int len)
{
    int copy_arr[9];
    for(int i = 0; i < len; ++i)
    {
        cout << arr[i];
    }
    cout << endl;
}

int main()
{
    // int test_arr[9] = {0,0,0,0,0,0,0,0,0};
    // print_arr(test_arr, 9);

    // for(int i = 0; i < 9; ++i)
    // {
    //     cout << test_arr[i];
    // }
    // cout << endl;


    int nums[5] = {1,2,3,4,5};
    ArrayTest test_arr(nums);
    test_arr.print_arr();

    set<int> test_set;
    for(int i = 0; i < 5; ++i)
    {
        test_set.insert(i);
    }

    for(auto e : test_set)
    {
        cout << e;
    }
    cout << endl;

    set<int> test_set2 = test_set;
    for(auto e : test_set2)
    {
        cout << e;
    }
    cout << endl;

    cout << "ACCESS ARR VAL INDIVIDUALLY: " << test_arr.arr[2] << endl;

}
