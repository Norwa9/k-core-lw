//
// Created by 罗威 on 2020/12/18.
//

#ifndef INC_20201218_GRAPH_H
#define INC_20201218_GRAPH_H
//using namespace std;

class Graph {
protected:
    int V;//顶点个数（缺陷：行人序号必须是连续地整数）
    list<int> *adj;    //邻接表
public:
    //*添加边(u,v)
    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //*返回图G的顶点个数
    int returnV() const{
        return V;
    }

    //*k-core分解(递归法)
    //原理：①：遍历v的每个邻居，如果自己的度小于k，则其邻居的度就-1；②：重复以上步骤，递归处理其每个邻居。
    //输入：行人序号v，所有顶点度信息的向量vDegree
    //输出：vDegree
    void DFS(int v, vector<bool> &visited, vector<int> &vDegree, int k);

    //*输出k-cores
    //描述：使用递归函数DFS来处理图G，得到vDegree。然后根据vDegree求得result
    //输入：参数k
    //输出：多维向量result
    vector<vector<int> > outputKCores(int k);

    //*输出当前图范围内的k-cores
    //输入：指定的商店store、参数k、查询集QueryNodes
    void printKCores(int k,vector<int> QueryNodes);

    //*根据store，从G中生成子图
    //输入：指定的Store类对象
    //输出：根据store包含的顶点子集，由G诱导生成的子图
    list<int> *generateSubEdge(const Store &store);

    //*初始化图G以及进行第一次分配
    //（读取边集的同时进行计算，分配，采用矩阵乘法来加速计算？）
    //输入：所有行人的初始坐标集文件、初始边集文件
    //输出：初始化完成的①图G、②people向量、③store向量
    void initGraphAndFirstDistribution(string filePathOfLocs, string filePathOfEdges);

    //*更新新时刻下的分配关系
    //输入：发生变动的行人及其坐标的数据集文件
    //输出：新时刻下行人与商店的分配关系
    void updateDistribution(string filePathOfUpdatedLocs);


//    void addPerson();
//    void personMove(int index,double x,double y);
};

void Graph::DFS(int v, vector<bool> &visited, vector<int> &vDegree, int k) {
    //处理顶点v：
    visited[v] = true;
    list<int>::iterator i;

    //遍历v的所有邻居
    for(i = adj[v].begin(); i != adj[v].end(); ++i){
        if(vDegree[v] < k){//如果v的度＜k，则它的邻居的度需要-1
            vDegree[*i] -= 1;
        }
        if(!visited[*i]){
            DFS(*i,visited,vDegree,k);
        }
    }
    return ;
}

vector<vector<int> > Graph::outputKCores(int k) {
    vector<bool> visited(V, false);
    const int resultMaxSize = 100;                  //定义一个输出k-core数量的上限
    vector<vector<int> > Result(resultMaxSize);     //分配多维向量内存，大小：100
    int minDeg =INT_MAX;
    vector<int> vDegree(V);

    //为什么V(g)要等于V(G)，否者有bug？假设移远两个顶点1、2，若认为g为7个顶点即V=7，然而adj[]还是有9个list。
    //vDegree[i] = adj[i].size();下标对应不上

    //初始化每个顶点的度
    for(int i = 0; i<V; i++){
        vDegree[i] = adj[i].size();
    }

    //输出处理前的所有顶点的度：
    cout<<"处理后每个顶点的度："<<endl;
    for(int i=0;i<V;i++){
        cout<<"i="<<i<<"："<<vDegree[i]<<",";
    }

    //确保图G中的所有可能连通分量都被递归处理
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            DFS(i,visited,vDegree,k);
            //
        }
    }

    //输出处理后的所有顶点的度：
    cout<<"\n处理后每个顶点的度："<<endl;
    for(int i=0;i<V;i++){
        cout<<"i="<<i<<"："<<vDegree[i]<<",";
    }

    //根据向量vDgree输出所有k-core，最后存到多维向量Result中去。
    int Num = 0;//总的结果数

    for(int v=0;v<V;v++){
        //只考虑那些在DFS处理过后，度仍然>=k的顶点
        if(vDegree[v] >= k){
            Result[Num].push_back(v);
            list<int>::iterator itr;
            //遍历v的邻点，将所有与v相邻的，且度≥k的邻点算作一个k-core
            for(itr = adj[v].begin(); itr != adj[v].end(); ++itr){
                auto rep = find(Result[Num].begin(),Result[Num].end(),*itr);//如果当前结果已经有这个点，不再保存
                if(vDegree[*itr] >= k && rep==Result[Num].end())
                    Result[Num].push_back(*itr);
            }
            if (Result[Num].size() > k){//至少k+1个顶点才算一个k-core
                //cout<<Result[Num].size()<<endl;
                Num++;
                if(Num > resultMaxSize)//最多存储resultMaxSize个k-core
                    break;
            }else{
                Result[Num].clear();
            }
        }
    }
    return Result;
}

void Graph::printKCores(int k,vector<int> QueryNodes) {
    //outputKCores(k)根据当前的图G查询k-cores并返回，结果存于Result。
    vector<vector<int> > Result = outputKCores(k);
    int kcoresNum = 0;
    for(auto &p:Result){
        if(!p.empty()){
            kcoresNum++;
        } else
        {
            break;
        }
    }

    //遍历每个k-core并输出含有Q的k-core：
    int No=0;
    for(int i =0;i<kcoresNum;++i){
        int count=0;
        //检查当前k-core是否包含Q
        for(int j=0; j<QueryNodes.size(); j++){
            auto iter = find(Result[i].begin(),Result[i].end(),QueryNodes[j]);
            if (iter != Result[i].end())
                count++;
        }
        if(count < QueryNodes.size())   //如果当前k-core不包含Q，进行下一轮循环：即检查Result里的下一个k-core
            continue;
        else{                           //当前结果集包含Q，可作为查询结果，将它输出。
            cout <<"No"<<++No<<":"<<Result[i][0]<< "->";
            for(int itr = 1;itr<Result[i].size(); itr++){
                if(itr != Result[i].size()-1)
                    cout << Result[i][itr] << "->";
                else
                    cout <<Result[i][itr] << endl;
            }
        }
    }
}

list<int>* Graph::generateSubEdge(const Store &store) {
    //哈希unorder map
    list<int> *adj_sub;
    adj_sub = new list<int>[V];
    vector<int>verticesOfSubGraph = store.returnPeopleInScope();

    //V(G)：主图G的顶点集。
    //v(g)：子图g的顶点集(verticesOfSubGraph)
    //adj：主图G的边表
    //遍历V(G)，①如果某个顶点v不在V(g)中，什么也不做；
    //②如果v在V(g)中，如果在g中存在adj[v,u]的终点u，就可以加入边(v,u)到子图去。
    for(int v=0;v<V;v++){
        vector<int>::iterator p;
        for(p=verticesOfSubGraph.begin();p!=verticesOfSubGraph.end();++p){
            //如果子图V(g)中存在v
            if(*p==v){
                //遍历adj[v]与subGraph一一匹配，
                list<int>::iterator u1;
                for(u1=adj[v].begin();u1!=adj[v].end();++u1){
                    //如果V(g)中存在u，添加sub_adj[v][u]和[u][v],break;
                    vector<int>::iterator u2;
                    for(u2=verticesOfSubGraph.begin();u2!=verticesOfSubGraph.end();++u2){
                        if(*u2==*u1){
                            adj_sub[*u2].push_back(v);
                            break;
                        }
                    }
                }
            }else{
                //如果子图V(g)中不存在v，啥也不干
            }
        }
    }
    return  adj_sub;
}

void Graph::initGraphAndFirstDistribution(string filePathOfLocs, string filePathOfEdges) {
    //1、初始化商店
    int numOfStores = 3;
    double sX,sY;
//    x = rand () / double (RAND_MAX) * 10; //0-10的随机数
//    y = rand () / double (RAND_MAX) * 10; //0-10的随机数
    sX = 0;
    sY = 0;
    for(int index =0;index<numOfStores;index++){
        stores.push_back(Store(index,sX,sY));
    }

    //2、读取坐标数据集，初始化行人坐标。同时对行人进行分配。此外，初始化图G的顶点集。
    int personIndex;
    double pX, pY;

    //读取txt的每行数据，获取index和x，y的代码：
    ifstream input_file;
    input_file.open(filePathOfLocs.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file" << filePathOfLocs << endl;
    }
    //cout<< "test personIndex:"<<endl;
    for(int index = 0;!input_file.eof();index++){
        input_file >> personIndex >>pX >> pY;
        //cout<<personIndex<<pX<<pY<<",";
        Person person(personIndex, pX, pY);
        for (int storeIndex = 0; storeIndex < numOfStores; storeIndex++) {
            if (isInScope(pX, pY, stores[storeIndex].returnStoreX(), stores[storeIndex].returnStoreY())) {
                person.addStoreBelonged(storeIndex);
                stores[storeIndex].addPersonToScope(personIndex);
            }
        }
        people.push_back(person);
    }
    //cout<<"test:people.size="<<people.size()<<endl;
    V = personIndex+1;
    adj = new list<int>[V];
    input_file.close();

    //3、读取边集数据集，初始化图G的边集
    int u, v;
    //读取txt的每行数据，获取边(u,v)
    input_file.open(filePathOfEdges.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file" << filePathOfEdges << endl;
    }
    //cout<< "\ntest edge:"<<endl;
    for(int edgeNum = 0;!input_file.eof();edgeNum++) {
        input_file >> u >> v;
        //cout<< u<<","<<v<<",";
        addEdge(u, v);
    }
    input_file.close();
    //cout<<"test1";

}

void Graph::updateDistribution(string filePathOfUpdatedLocs) {
    //读取每一行，更新对应序号的行人的位置
    int personIndex;
    double pNewX,pNewY;
    //读取新时刻的坐标数据集：获取personIndex、pNewX、pNewY
    ifstream input_file;
    input_file.open(filePathOfUpdatedLocs.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file" << filePathOfUpdatedLocs << endl;
    }
    for(int i =0; !input_file.eof();i++) {
        input_file >> personIndex >> pNewX >> pNewY;
        //1.更新该行人坐标
        people[personIndex].setPersonNewPosition(pNewX, pNewY);
        //2.准备重新分配该行人：清空该行人的storeBelonged、更新所有商店的peopleInScope。
        vector<Store>::iterator s;
        for (s = stores.begin(); s != stores.end(); ++s) {
            (*s).delPersonFromScope(personIndex);
        }
        people[personIndex].clearStoreBelonged();
        //3.重新分配该行人：更新该行人的stroeBelonged向量和各商店的peopleInScope向量
        for (int storeIndex = 0; storeIndex < stores.size(); storeIndex++) {
            if (isInScope(pNewX, pNewY, stores[storeIndex].returnStoreX(), stores[storeIndex].returnStoreY())) {
                people[personIndex].addStoreBelonged(storeIndex);
                stores[storeIndex].addPersonToScope(personIndex);
            }
        }
    }
}



#endif //INC_20201218_GRAPH_H
