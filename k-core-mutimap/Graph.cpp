//
// Created by 罗威 on 2021/3/2.
//

#include "Graph.h"
Graph::Graph(string filePathOfLocs, string filePathOfEdges) {
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


vector<Person> Graph::returnPeopleVector() const {
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
}




