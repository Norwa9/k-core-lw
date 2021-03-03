#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <time.h>
using namespace std;

#include "Person.h"
#include "Store.h"
vector<Person> people;      //存放所有的行人
vector<Store> stores;       //存放所有的商店
vector<Person> updatedPeople; //存放发生移动的行人

double d = 100;//商店辐射半径

//*计算行人是否在商店的辐射半径内
bool isInScope(double x1,double y1,double x2,double y2) {
    double dis;
    dis = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
    if (dis <= d)
        return true;
    return false;
}

#include "Graph.h"
#include "subGraph.h"


int main() {
    //查询集Q和k
    int k =20;
    vector<int> querynodes;
    clock_t start_time,end_time;
//    querynodes.push_back(3);
//    querynodes.push_back(2);
//    querynodes.push_back(5);
//    querynodes.push_back(6);

/*  *demo数据集测试*
    Graph G;
    //初始化people，store，G，同时进行第一次行人-商店分配。
    G.initGraphAndFirstDistribution("../data/locs_demo.txt","../data/edges_demo.txt");
//  G.initGraphAndFirstDistribution("../data/Brightkite_locs.txt","../data/Brightkite_edges.txt");
    cout<<"k="<<k<<endl;
    subGraph g;
    //初始时刻，初始化商店0的子图g：
    g.initSubGraph(G,stores[0]);
    cout<<"初始时刻0号商店对应的"<<"子图g的k-core分解结果："<<endl;
    g.printKCores(3,querynodes);
//    cout<<"初始时刻0号商店对应的"<<"子图g的边集："<<endl;
//    g.printEdges();

    //新时刻，发生行人移动，行人-商店的分配关系发生变化，更新分配，增量更新子图。
    G.updateDistribution("../data/updatedLocs_demo.txt");
    g.updateSubGraph(G,stores[0]);
    cout<<"0时刻"<<"0号商店对应的"<<"子图g的k-core分解结果："<<endl;
    g.printKCores(3,querynodes);
*/

///*
    //原理：先初始化整个场景G，然后再由G生成对应商店的子图。
    //参数：输出的k-core上限个数设置为了100个、商店辐射半径设置为50m、k=20、查询集Q=[]。
    Graph G;
    subGraph g;
    start_time = clock();

    G.initGraphAndFirstDistribution("../data/Brightkite_locs.txt","../data/Brightkite_edges.txt");
    cout<<"初始时刻:"<<endl;
    g.initSubGraph(G,stores[0]);
    end_time = clock();
    cout<<"\n↑初始化G和g的执行时间:"<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;


    cout<<"增量更新："<<endl;
    //某商店对应的子图g
    cout<<"\n0时刻:"<<endl;
    start_time = clock();
    G.updateDistribution("../data/Brightkite_locs0_500.txt");
    g.updateSubGraph(G,stores[0]);
    g.printKCores(k,querynodes);//bug：k=3,d=50时该函数不执行
    //cout<<"test"<<endl;
    end_time = clock();
    cout<<"\n↑查询0时刻的k-core的执行时间:"<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;

    cout<<"\n1时刻:"<<endl;
    start_time = clock();
    G.updateDistribution("../data/Brightkite_locs1_500.txt");
    g.updateSubGraph(G,stores[0]);
    g.printKCores(k,querynodes);
    end_time = clock();
    cout<<"\n↑查询1时刻的k-core的执行时间:"<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;

    cout<<"\n2时刻:"<<endl;
    start_time = clock();
    G.updateDistribution("../data/Brightkite_locs2_1600.txt");
    g.updateSubGraph(G,stores[0]);
    g.printKCores(k,querynodes);
    end_time = clock();
    cout<<"\n↑查询2时刻的k-core的执行时间:"<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;

    cout<<"\n3时刻:"<<endl;
    start_time = clock();
    G.updateDistribution("../data/Brightkite_locs3_500.txt");
    g.updateSubGraph(G,stores[0]);
    g.printKCores(k,querynodes);
    end_time = clock();
    cout<<"\n↑查询3时刻的k-core的执行时间:"<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;
//*/
}
