//
// Created by 罗威 on 2021/3/2.
//

#ifndef K_CORE_MUTIMAP_SUBGRAPH_H
#define K_CORE_MUTIMAP_SUBGRAPH_H
#include "Graph.h"
#include "Store.h"
#include "Person.h"
using namespace std;
class subGraph: public Graph{
public:
    void initSubGraph(const Graph &G,Store &store);
    void clearEdgesOfV(int v);
    void updateSubGraph(const Graph &G,Store &store);
};


#endif //K_CORE_MUTIMAP_SUBGRAPH_H
