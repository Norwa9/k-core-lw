//
// Created by 罗威 on 2021/3/2.
//

#ifndef K_CORE_MUTIMAP_GRAPH_H
#define K_CORE_MUTIMAP_GRAPH_H
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <istream>
#include <fstream>

#include "Store.h"
#include "Person.h"
extern vector<Person> people;
extern vector<Store> stores;       //存放所有的商店
extern vector<Person> updatedPeople; //存放发生移动的行人
using namespace std;

class Graph {
protected:
    vector<int>people;//存放图内所有的行人序号
    unordered_multimap<int,int>edges;//存放图内所有的边
public:
    Graph(string filePathOfLocs, string filePathOfEdges);

    void addEdge();

    void returnPeopleVector()const;

    unordered_multimap<int,int> returnEdgesOfV(int v) const;

    void DFS(int v, vector<bool> &visited, vector<int> &vDegree, int k);

    void printKCores(int k,vector<int> QueryNodes);

    unordered_multimap<int,int> generateSubEdge(Store &store) const;

    void updateDistribution(string filePathOfUpdatedLocs);
};


#endif //K_CORE_MUTIMAP_GRAPH_H
