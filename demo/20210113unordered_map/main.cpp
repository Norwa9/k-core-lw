#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include "graph.h"
using namespace std;
int main()
{
    graph g("../demoData/edges_demo.txt");
    g.del_adj();
}

