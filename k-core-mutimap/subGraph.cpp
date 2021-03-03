//
// Created by 罗威 on 2021/3/2.
//

#include "subGraph.h"
void subGraph::initSubgraph(const Graph &G, Store &store) {
    //初始化edges
    generateEdgesFromGraph(G,store);
}


void subGraph::generateEdgesFromGraph(const Graph &G, Store &store) {
    //对于V(g)中的每一个顶点v（v必属于V(G)），遍历v的边集edges[v]，如果某个终点u也在V(g)中，则子图边集添加(u,v)。
    vector<int>peopleOfSubgraph;
    peopleOfSubgraph = store.returnPeopleInScope();//V(g)

    int testCount = 0;
    vector<int>::iterator v;
    for (v = peopleOfSubgraph.begin(); v != peopleOfSubgraph.end() ; ++v) {
        //result是*v的所有边
        auto result = G.returnEdges().equal_range(*v);
        if(result.first != end(G.returnEdges()))
        {
            //遍历*v的所有邻点u=edge->second，查找u=edge->second是否在V(g)
            for (auto edge = result.first ; edge != result.second; ++edge){
                auto findPerson = find(peopleOfSubgraph.begin(),peopleOfSubgraph.end(),edge->second);
                if(findPerson!=peopleOfSubgraph.end()){
                    edges.insert(pair<int,int>(*v,edge->second));//子图中添加(v,u)
                }
            }
        }
    }
}

void subGraph::updateSubGraph(const Graph &G, Store &store) {

}



