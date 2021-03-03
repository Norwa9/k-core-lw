//
// Created by 罗威 on 2020/12/18.
//

#ifndef INC_20201218_SUBGRAPH_H
#define INC_20201218_SUBGRAPH_H


class subGraph: public Graph{
public:
    void initSubGraph(Graph &G,Store store){
        //初始化子图顶点集（子图和主图的顶点数设置为一致）
        V = G.returnV();
        //初始化子图边集（list由G负责生成）
        adj = G.generateSubEdge(store);
    }
};




#endif //INC_20201218_SUBGRAPH_H
