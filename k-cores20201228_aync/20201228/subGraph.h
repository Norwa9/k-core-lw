//
// Created by 罗威 on 2020/12/18.
//

#ifndef INC_20201218_SUBGRAPH_H
#define INC_20201218_SUBGRAPH_H


class subGraph: public Graph{

public:
    void initSubGraph(const Graph &G,Store &store){
        //初始化子图顶点集（子图和主图的顶点数设置为一致）
        V = G.returnV();
        //初始化子图边集（list由G负责生成）
        adj = G.generateSubEdge(store);
    }

    //清空子图上v号顶点的边表
    void clearEdgesOfV(int v){
        adj[v].clear();
    }

    void updateSubGraph(const Graph &G,Store &store);

    void printEdges(){
        for(int i =0;i<V;i++){
            cout<<i<<":"<<adj[i].size()<<endl;
        }
    }


};

void subGraph::updateSubGraph(const Graph &G,Store &store){
    int v;
    int s;
    vector<int>peopeleInScope = store.returnPeopleInScope();
    //cout<<"updatedPeople.size()"<<updatedPeople.size()<<endl;

    vector<Person>::iterator p;
    //遍历所有发生移动的行人updatedPeople
    for (p=updatedPeople.begin();p!=updatedPeople.end();++p){
        v = (*p).returnPersonIndex();
        s = store.returnStoreIndex();

        //行人v发生移动，其storeBelonged已经更新，商店的PeopleInScope在接下来更新：
        vector<int>storeBelonged = people[v].returnStoreBelonged();

        bool wasPersonInStore = store.hasPerson(v);
        bool isPersonInStore = people[v].isInStore(s);

        if(wasPersonInStore){                   //1、在旧时刻该商店范围内有该行人v
            if(isPersonInStore){                //1.1、在旧时刻该商店范围内有该行人&&在新时刻该行人处于商店范围内
                list<int>::iterator u;
                //遍历adj[v]得到所有邻居u。在新时刻，如果u不在商店s范围内，删除u,v之间的边。
                list<int> temp = adj[v];
                for(u=temp.begin();u!=temp.end();u++){
                    if(!people[(*u)].isInStore(s)){
                        //新时刻下u不在商店s范围内
                        adj[v].remove((*u));
                        adj[(*u)].remove(v);
                    }else{
                        //do nothing
                    }
                }
            }else{                              //1.2、在旧时刻该商店范围内有该行人&&在新时刻该行人不在商店范围内
                store.delPersonFromScope(v);
                list<int>::iterator u;
                list<int> temp = adj[v];
                for(u=temp.begin();u!=temp.end();u++){
                    //cout<<v<<"删除："<<(*u)<<endl;
                    //邻居u在新时刻下，不在商店s的范围内
                    if(!people[(*u)].isInStore(s)){
                        //如果邻居u在新时刻也移出范围，只删除单向边(v,u)，防止遍历到u时进行重复删除操作。
                        adj[v].remove((*u));
                    }else{
                        adj[v].remove((*u));
                        adj[(*u)].remove(v);
                    }
                }
                //cout<<adj[v].size()<<endl;
                //cout<<"clearEdgesOfV(v)"<<endl;
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
};


#endif //INC_20201218_SUBGRAPH_H
