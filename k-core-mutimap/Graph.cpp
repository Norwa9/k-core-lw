//
// Created by 罗威 on 2021/3/2.
//

#include "Graph.h"
void Graph::initGraphAndFirstDistribution(string filePathOfLocs, string filePathOfEdges) {
//1、设置3个商店
    int storesNum = 3;
    double s_X,s_Y;
    s_X=0,s_Y=0;
    for (int i = 0; i < storesNum; ++i) {
        stores.push_back(Store(i,s_X,s_Y));
    }

    //2、初始化行人信息
    int personIndex;
    double p_X,p_Y;

    ifstream input_file;
    input_file.open(filePathOfLocs.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file" << filePathOfLocs << endl;
    }
    for(int index = 0;!input_file.eof();index++){
        input_file >> personIndex >>p_X >> p_Y;
        Person person(personIndex, p_X, p_Y);
        for (int storeIndex = 0; storeIndex < storesNum; storeIndex++) {
            if (stores[storeIndex].isInScope(p_X,p_Y)) {
                person.addStoreBelonged(storeIndex);
                stores[storeIndex].addPersonToScope(personIndex);
            }
        }
        people.push_back(person);
    }
    input_file.close();

    //3、初始化边集
    int u,v;
    input_file.open(filePathOfEdges.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file" << filePathOfEdges << endl;
    }
    for(int edgeNum = 0;!input_file.eof();edgeNum++) {
        input_file >> u >> v;
        addEdge(u,v);
    }
    input_file.close();


    cout<<"initGraphAndFirstDistribution Done!"<<endl;
}

vector<Person> Graph::peopleVector() const {
    return people;
}

const unordered_multimap<int, int> &Graph::returnEdges() const {
    return edges;
}

void Graph::addEdge(int u,int v) {
    edges.insert(pair<int,int>(u,v));
    edges.insert(pair<int,int>(v,u));
}

void Graph::updateDistribution(string filePathOfUpdatedLocs) {
    updatedPeople.clear();

    int personIndex;
    double new_pX,new_pY;
    ifstream input_file;
    input_file.open(filePathOfUpdatedLocs.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file" << filePathOfUpdatedLocs << endl;
    }
    for(int i =0; !input_file.eof();i++) {
        input_file >> personIndex >> new_pX >> new_pY;

        updatedPeople.push_back(Person(personIndex,new_pX,new_pY));//读取移动过的行人信息到向量中保存

        //1.更新该行人坐标
        people[personIndex].setPersonNewPosition(new_pX, new_pY);//是否可以删除？

        //2.清空该行人的storeBelonged并重新分配该行人：更新该行人的stroeBelonged向量和各商店的peopleInScope向量
        people[personIndex].clearStoreBelonged();
        for (int storeIndex = 0; storeIndex < stores.size(); storeIndex++) {
            if (stores[storeIndex].isInScope(new_pX,new_pY)) {
                people[personIndex].addStoreBelonged(storeIndex);
            }
        }
    }
    cout << "updateDistribution Done!"<<endl;
}

void Graph::delEdge(int u, int v) {
    auto resultUedges = edges.equal_range(u);//resultU是u的所有出边
    if(resultUedges.first != end(edges)){
        //edgeU:u->v
        for (auto edgeU = resultUedges.first ; edgeU != resultUedges.second; ++edgeU){
            if(edgeU->second == v){
                edges.erase(edgeU);
                break;//运行到这里，表示u-v双向边已被删除，可直接退出for循环不必再遍历u的边
            }
        }
    }
}

void Graph::DFS(int v, vector<bool> &visited, vector<int> &vDegree, int k) {
    visited[v] = true;
    auto edgesV = edges.equal_range(v);
    for(auto edge = edgesV.first;edge != edgesV.second;++edge){
        int u =  edge->second;
        if(vDegree[v] < k){
            vDegree[u] -= 1;
        }
        if(!visited[u]){
            DFS(u,visited,vDegree,k);
        }
    }
}

void Graph::printKCores(int k, vector<int> QueryNodes) {
    int numV = people.size();
    vector<bool>visited(numV, false);
    vector<int> vDegree(numV);

    //初始化vDegree
    for(int v = 0 ;v < numV ;v++){
        vDegree[v] = edges.count(v);
    }

//    //查看vDegeree
//    for (int i = 0; i < numV; ++i) {
//        cout << "vDegree[" <<i<<"]"<<":"<<vDegree[i]<<endl;
//    }
//    cout <<endl;

    //DFS k-core分解，计算vDegree
    for (int v = 0; v < numV; ++v) {
        if(!visited[v]){
            DFS(v,visited,vDegree,k);
        }
    }

    //根据VDegree计算所有的k-core并存入向量resultKcores
    const int maxKcoreNum = 100;
    vector<vector<int> >resultKcores(maxKcoreNum);//二维向量：存放k-core的向量
    int kcoreNum = 0;
    for(int v=0;v<numV;v++){
        //只考虑那些在DFS处理过后，度仍然>=k的顶点
        if(vDegree[v] >= k){
            resultKcores[kcoreNum].push_back(v);
            //遍历v的邻点。将所有与v相邻的，且度≥k的邻点u算入一个k-core里
            auto edgesV = edges.equal_range(v);
            for(auto edge = edgesV.first;edge != edgesV.second;++edge) {
                int u = edge->second;
                auto find_u = find(resultKcores[kcoreNum].begin(),resultKcores[kcoreNum].end(),u);
                if(vDegree[u] >= k && find_u == resultKcores[kcoreNum].end())
                    resultKcores[kcoreNum].push_back(u);
            }
            if(resultKcores[kcoreNum].size() > k){
                kcoreNum++;
                if(kcoreNum >= maxKcoreNum)
                    break;
            }else{
                resultKcores[kcoreNum].clear();
            }
        }
    }

    //统计resultKcores中有效的k-core个数
    kcoreNum = 0;
    for(auto &p:resultKcores){
        if(!p.empty()){
            kcoreNum++;
        } else
        {
            break;
        }
    }


    //遍历resultKcores，输出含有Q全部元素的k-core
    int index = 0;
    for (int i = 0; i < kcoreNum; ++i) {
        int count_q = 0;//统计Q的元素出现次数
        for (int j = 0; j < QueryNodes.size(); ++j) {
            auto find_q = find(resultKcores[i].begin(),resultKcores[i].end(),QueryNodes[j]);
            if(find_q != resultKcores[i].end())
                count_q++;
        }

        if(count_q < QueryNodes.size()){
            continue;
        }else{
            cout <<"No"<<++index<<":"<<resultKcores[i][0]<<"->";
            for (int k = 1; k < resultKcores[i].size(); ++k) {
                if(k != resultKcores[i].size() - 1)
                    cout << resultKcores[i][k] << "->";
                else
                    cout << resultKcores[i][k] <<endl;
            }
        }
    }
    cout << "printKCores Done!"<<endl;
}






