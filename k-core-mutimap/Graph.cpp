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


}
