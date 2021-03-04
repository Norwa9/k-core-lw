#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

//注意：C++11才开始支持括号初始化
unordered_multimap<int, int> myMap={{ 1, 3 },{ 6, 3 }};//使用{}赋值

void print(){
    //遍历输出+迭代器的使用
    auto iter1 = myMap.begin();//auto自动识别为迭代器类型unordered_map<int,string>::iterator
    while (iter1!= myMap.end())
    {
        cout << iter1->first << "," << iter1->second << endl;
        ++iter1;
    }
}

void find(){
    //查找元素并输出+迭代器的使用
    auto iter2 = myMap.find(1);//find()返回一个指向2的迭代器
    if (iter2 != myMap.end())
        cout << endl<< iter2->first << "," << iter2->second << endl;
    else
        cout << "没有找到与参数匹配的元素";
}

void insert(){
    //使用insert和pair插入
    myMap.insert(pair<int, int>(3, 1));
    myMap.insert(pair<int, int>(3, 2));
    myMap.insert(pair<int, int>(3, 3));
    myMap.insert(pair<int, int>(3, 4));
    myMap.insert(pair<int, int>(3, 5));
}

void del(){
    //删除元素：例如删除两个对：31和13
    auto result = myMap.equal_range(3);//equal_range(参数)返回一个迭代器，指向第一个大于等于参数的元素
    //auto keyVlaue = unordered_multimap<int, string>::iterator keyValue
    auto keyValue = result.first;
    while (keyValue != result.second) {
        if (keyValue->second == 1) {
            //1.删除3-1
            keyValue = myMap.erase(keyValue);
            //2.删除1-3
            auto result2 = myMap.equal_range(1);
            if (result2.first != end(myMap)) {
                for (auto keyVlaue2 = result2.first; keyVlaue2 != result2.second; ++keyVlaue2) {
                    if (keyVlaue2->second == 3) {
                        myMap.erase(keyVlaue2);
                        break;//important!
                    }
                }
            }
            continue;
        } else {
            keyValue++;
        }
    }
}


int main()
{
//    insert();
//    //数据集为7对数字：31,32,33,34,35,13,63
//    del();
//    print();
    find();
}

