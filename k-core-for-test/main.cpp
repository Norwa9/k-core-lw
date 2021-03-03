//参考：https://www.geeksforgeeks.org/find-k-cores-graph/
//k-core分解的思想：删除度<k的顶点，然后更新其邻点的度，如果邻点的度<k也删除。
#include <iostream>]
#include<list>
#include<vector>

using namespace std;
class Graph{
    int V;
    list<int> *adj;//指针，指向存放图顶点的列表
public:
    Graph(int V);//构造函数

    void addEdge(int u,int v);

    //一个递归函数：用来进行打印从v开始的DFS序列
    void DFSUtil(int, vector<bool> &, vector<int> &, int k);

    void printKCores(int k);

};

Graph::Graph(int V) {
    this -> V = V;
    adj = new list<int>[V];//创建一个大小为V的列表，然后令adj指向它
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}
//k-core分解算法的核心：
//这是一个从v开始的DFS函数，它处理每一个点；
//如果v经过处理之后度＜k，它返回true。反之返回false。
void Graph::DFSUtil(int v, vector<bool> &visited, vector<int> &vDegree, int k) {
    visited[v] = true;
    //cout<<"访问了"<<v<<" ";
    list<int>::iterator i;//遍历存放图G顶点列表的迭代器i

    for(i = adj[v].begin(); i != adj[v].end(); ++i){
        //如果v的度＜k，则它的邻点的度需要-1
        if(vDegree[v] < k){
            ///还是用邻接表好：逻辑更清晰。递归处理后，再遍历一遍邻接表就可以计算顶点的度
            vDegree[*i]--;//改成adj[u][*i]=adj[*i][u]=0
            cout<<"i:"<<*i<<"-v:"<<v<<endl;
        }
        //如果v的邻点还未处理，处理它
        if(!visited[*i]){
            //cout<< *i <<endl;
            DFSUtil(*i,visited,vDegree,k);
        }
    }
    return ;
}

void Graph::printKCores(int k) {
    //初始化工作：将所有顶点设置为未访问
    vector<bool> visited(V, false);
    vector<bool> processed(V, false);
    int minDeg =INT_MAX;
    int startVertex;

    vector<int> vDegree(V);//声明一个大小为v的向量
    cout<<"处理前："<<endl;
    //存储所有顶点的度，并且将度最小的顶点设置为开始顶点
    for(int i = 0; i<V; i++){
        vDegree[i] = adj[i].size();
        cout<<i<<":"<<adj[i].size()<<", ";
        if(vDegree[i] < minDeg) {
            minDeg = vDegree[i];
            startVertex = i;
        }
    }
    putchar('\n');
    cout << "开始于"<<startVertex<<endl;

    //从startVertex开始，执行一遍算法，将获得处理后所有顶点的度vDegree[]
    DFSUtil(4,visited,vDegree,k);

    //确保其他的连通分量也得到遍历，在图结构中有多个连通分量的时候才用的上：
    /*
    for(int i = 0; i < V; i++){
        cout<<visited[i];
        if(visited[i] == false){
            DFSUtil(i,visited,vDegree,k);
        }
    }
    */

    cout<<"处理后："<<endl;
    for(int i = 0; i < V; i++){
        cout<<i<<":"<<vDegree[i]<<", ";
    }
    putchar('\n');

    //输出k-cores
    cout << "输出k-cores如下:";
    for(int v=0;v<V;v++){
        //只考虑那些在DFS处理过后度仍然>=k的顶点
        if(vDegree[v] >= k){
            cout<< "\n[" << v << "]";
            //遍历v的邻点，输出与v相邻的，且度≥k的邻点。
            list<int>::iterator itr;
            for(itr = adj[v].begin(); itr != adj[v].end(); ++itr){
                if(vDegree[*itr] >= k)
                    cout << "->" << *itr;
            }
        }
    }



}
int main() {
    int k =3 ;
    Graph g1(9);
    g1.addEdge(1,0);
    //g1.addEdge(1,2);
    g1.addEdge(1,5);
    //g1.addEdge(0,2);
    //g1.addEdge(2,5);
    //g1.addEdge(2,4);
    //g1.addEdge(2,3);
    //g1.addEdge(2,6);
    g1.addEdge(5,6);
    g1.addEdge(5,8);
    g1.addEdge(6,4);
    g1.addEdge(6,3);
    g1.addEdge(6,8);
    g1.addEdge(6,7);
    g1.addEdge(4,3);
    g1.addEdge(4,7);
    g1.addEdge(3,7);
    g1.printKCores(k);
}