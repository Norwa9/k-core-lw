//
// Created by 罗威 on 2021/3/1.
//

#include "graph.h"

graph::graph(string filepath) {
    ifstream input_file;
    input_file.open(filepath.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file "<< filepath << endl;
    }
    int u,v;
    for(int index = 0;!input_file.eof();index++){
        input_file >> u >> v;
        edges.insert(pair<int,int>(u,v));
        edges.insert(pair<int,int>(v,u));
    }
    input_file.close();
}

void graph::find_adjs() {
    int n = 3;
    auto n_adjs = edges.equal_range(n);//查找n的所有邻点
    if(n_adjs.first != end(edges)){
        for(auto iter = n_adjs.first; iter!=n_adjs.second;++iter){
            cout << iter->first <<"-"<<iter->second<<endl;
        }
    }else{
        cout<<"顶点"<< n <<"无边";
    }
}

void graph::del_adj() {
    int n =3;
    edges.erase(3);

    find_adjs();
}
