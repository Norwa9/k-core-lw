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
//extern vector<Person> people;
extern vector<Store> stores;       //存放所有的商店
extern vector<Person> updatedPeople; //存放发生移动的行人
using namespace std;

class Graph {
protected:
    vector<Person>people;//存放图内所有的行人序号
    unordered_multimap<int,int>edges;//存放图内所有的边
public:
    void initGraphAndFirstDistribution(string filePathOfLocs, string filePathOfEdges);

    void addEdge(int u,int v);

    vector<Person> peopleVector()const;

    void updateDistribution(string filePathOfUpdatedLocs);

    void delEdge(int u,int v);

    const unordered_multimap<int,int>& returnEdges()const;

    void DFS(int v, vector<bool> &visited, vector<int> &vDegree, int k);

    void printKCores(int k,vector<int> QueryNodes);


};


#endif //K_CORE_MUTIMAP_GRAPH_H
