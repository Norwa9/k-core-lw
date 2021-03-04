#include <time.h>
#include "Person.h"
#include "Store.h"
vector<Store> stores;       //存放所有的商店
vector<Person> updatedPeople; //存放发生移动的行人
double const d = 100;//商店辐射半径
#include "Graph.h"
#include "subGraph.h"

int main() {
//    int k = 3;
//    vector<int> queryNodes;
//    queryNodes.push_back(3);
//
//    Graph G;
//    subGraph g;
//
//    //初始化
//    G.initGraphAndFirstDistribution("../data/locs_demo.txt","../data/edges_demo.txt");
//    g.initSubgraph(G,stores[0]);
//    cout << "初始时刻k-core查询："<<endl;
//    g.printKCores(k,queryNodes);
//
//    //更新
//    G.updateDistribution("../data/updatedLocs_demo.txt");
//    g.updateSubGraph(G,stores[0]);
//    cout << "0时刻k-core查询："<<endl;
//    g.printKCores(k,queryNodes);


    int k = 20;
    vector<int> queryNodes;
    clock_t start_time,end_time;
    Graph G;
    subGraph g;

    //初始化
    start_time = clock();
    G.initGraphAndFirstDistribution("../data/Brightkite_locs.txt","../data/Brightkite_edges.txt");
    g.initSubgraph(G,stores[0]);
    end_time = clock();
    cout << "初始化耗时："<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;

    //时刻0
    start_time = clock();
    G.updateDistribution("../data/Brightkite_locs0_500.txt");
    g.updateSubGraph(G,stores[0]);
    cout << "0时刻k-core查询："<<endl;
    g.printKCores(k,queryNodes);
    end_time = clock();
    cout << "时刻0更新耗时："<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;

    //时刻1
    start_time = clock();
    G.updateDistribution("../data/Brightkite_locs1_500.txt");
    g.updateSubGraph(G,stores[0]);
    cout << "1时刻k-core查询："<<endl;
    g.printKCores(k,queryNodes);
    end_time = clock();
    cout << "时刻1更新耗时："<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;

    //时刻2
    start_time = clock();
    G.updateDistribution("../data/Brightkite_locs2_1600.txt");
    g.updateSubGraph(G,stores[0]);
    cout << "2时刻k-core查询："<<endl;
    g.printKCores(k,queryNodes);
    end_time = clock();
    cout << "时刻2更新耗时："<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;

    //时刻3
    start_time = clock();
    G.updateDistribution("../data/Brightkite_locs3_500.txt");
    g.updateSubGraph(G,stores[0]);
    cout << "3时刻k-core查询："<<endl;
    g.printKCores(k,queryNodes);
    end_time = clock();
    cout << "时刻3更新耗时："<<double(end_time-start_time) / CLOCKS_PER_SEC <<"s" << endl;


}
