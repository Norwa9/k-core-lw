//
// Created by 罗威 on 2021/3/1.
//

#ifndef INC_20210113UNORDERED_MAP_GRAPH_H
#define INC_20210113UNORDERED_MAP_GRAPH_H
#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <istream>
#include <fstream>
using namespace std;
class graph {
private:
    int V;
    unordered_multimap<int,int>edges;
public:
    graph(string filepath);
    void find_adjs();
    void del_adj();
};


#endif //INC_20210113UNORDERED_MAP_GRAPH_H
