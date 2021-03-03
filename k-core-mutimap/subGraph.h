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
    void initSubgraph(const Graph &G,Store &store);

    void generateEdgesFromGraph(const Graph &G,Store &store);

    void updateSubGraph(const Graph &G,Store &store);
    void clearEdgesOfV(int v);

};


#endif //K_CORE_MUTIMAP_SUBGRAPH_H
