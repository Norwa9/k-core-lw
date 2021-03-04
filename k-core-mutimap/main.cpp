#include "Person.h"
#include "Store.h"
vector<Store> stores;       //存放所有的商店
vector<Person> updatedPeople; //存放发生移动的行人
double const d = 10;//商店辐射半径
#include "Graph.h"
#include "subGraph.h"

int main() {
    int k = 3;
    vector<int> queryNodes;
    queryNodes.push_back(3);

    Graph G;
    subGraph g;

    //初始化
    G.initGraphAndFirstDistribution("../data/locs_demo.txt","../data/edges_demo.txt");
    g.initSubgraph(G,stores[0]);
    cout << "初始时刻k-core查询："<<endl;
    g.printKCores(k,queryNodes);

    //时刻0
    G.updateDistribution("../data/updatedLocs_demo.txt");
//    cout << G.peopleVector()[7].returnStoreBelonged().size();
    g.updateSubGraph(G,stores[0]);
    cout << "0时刻k-core查询："<<endl;
    g.printKCores(k,queryNodes);

}
