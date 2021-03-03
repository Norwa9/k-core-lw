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
    int v;
    int s;
    vector<int>peopeleInScope = store.returnPeopleInScope();
    //cout<<"updatedPeople.size()"<<updatedPeople.size()<<endl;

    vector<Person>::iterator p;
    //遍历所有发生移动的行人v
    for (p=updatedPeople.begin();p!=updatedPeople.end();++p){
        v = (*p).returnPersonIndex();//行人序号
        s = store.returnStoreIndex();//商店序号

        //行人v发生移动，其storeBelonged已经更新，商店的PeopleInScope在接下来更新：
        vector<int>storeBelonged = G.peopleVector()[v].returnStoreBelonged();

        //v旧时刻是否属于商店store
        bool wasPersonInStore = store.hasPerson(v);
        //v新时刻是否属于商店store
        bool isPersonInStore = G.peopleVector()[v].isInStore(s);

        if(wasPersonInStore){                   //1、在旧时刻该商店范围内有该行人v
            if(isPersonInStore){                //1.1、在旧时刻该商店范围内有该行人&&在新时刻该行人处于商店范围内（无需更新store的PeopleInScope）
                auto resultVedges = edges.equal_range(v);//获取v的所有出边
                auto edgeV = resultVedges.first;//令edgeV指向v的第一条出边
                //遍历v的所有边v->u。
                while(edgeV != resultVedges.second){//resultVedges.second表示v的最后一条出边
                    int u = edgeV->second;
                    if(!G.peopleVector()[u].isInStore(s)){
                        //在新时刻，如果u不在商店s范围内，删除u,v之间的双向边。
                        //1.删除v->u
                        edgeV = edges.erase(edgeV);
                        //2.删除u->v
                        delEdge(u,v);
                        //3.删除u<->v成功，继续while循环
                        continue;
                    }else{
                        edgeV++;//不满足if条件，遍历v的下一条出边
                    }
                }
            }else{                              //1.2、在旧时刻该商店范围内有该行人&&在新时刻该行人不在商店范围内（需要更新store的PeopleInScope）
                store.delPersonFromScope(v);
                auto resultVedges = edges.equal_range(v);//获取v的所有出边
                auto edgeV = resultVedges.first;//令edgeV指向v的第一条出边
                //删除v的所有入边u->v。
                while(edgeV != resultVedges.second){
                    int u = edgeV->second;
                    delEdge(u,v);//删除u->v(delEdge:先找出u的所有出边，然后遍历之。定位并删除u->v)
                }
                edges.erase(v);//删除v的所有出边v->x
            }
        } else{                                 //2.在旧时刻该商店范围内没有该行人v
            if(isPersonInStore){                //2.1、在旧时刻该商店范围内没有该行人&&在新时刻该行人处于商店范围内
                store.addPersonToScope(v);
                //重新计算子图g中v的边集
                adj[v] = G.returnEdgesOfV(v);//g的adj[v]为空，需要从G获取v的邻居信息
                list<int> temp = adj[v];
                list<int>::iterator u;
                //遍历adj[v]得到v所有的邻居u，如果u新时刻下不在范围内了，需要删除(v,u)
                for(u=temp.begin();u!=temp.end();u++) {
                    if (!people[(*u)].isInStore(s)) {
                        //cout<<v<<"删除："<<*u<<endl;
                        adj[v].remove((*u));
                        adj[(*u)].remove(v);
                    }else{
                        adj[*u].push_back(v);
                    }
                }
            }else{                             //2.2、在旧时刻该商店范围内没有该行人&&在新时刻该行人不在商店范围内
                //do nothing
            }
        }
    }
}



