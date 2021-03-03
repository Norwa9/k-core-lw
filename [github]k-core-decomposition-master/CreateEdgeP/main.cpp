// CreateEdgeP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <string.h>
#include <fstream>
#include <cmath>
#include <ctime>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 0x7fffffff;
#define random(x) (rand() % x)

string outname = "ProbilisticCore_TwoStage";

void Create_P(Graph* G) {
	int n = G->get_N();
	int m = G->get_M();
	int *VertexList = G->get_VertexList();

	map<pair<int, int>, double> Pr;
	map<pair<int, int>, int> Count;
	for (int i = 1; i <= n; i++) {
		int tx = VertexList[i];
		int *VertNeighborList = G->get_Neighbor(tx);
		int de = G->get_Deg(tx);
		for (int j = 1; j <= de; j++) {
			pair<int, int> p1(i, VertNeighborList[j]);
			double ex = G->get_p(tx, j);
			if (Pr.count(p1) == 0) {
				Pr.insert(pair<pair<int, int>, double>(p1, ex));
				Count.insert(pair<pair<int, int>, int>(p1, 0));
			}
		}
		delete[] VertNeighborList;
	}

	ofstream rout;
	rout.open("ProbilisticCore_TwoStage_Error.txt");
	int Round1 = (int)(ceil(8.0 * log10(n) / G->get_min_p()));
	printf("%d %.2f %d\n", n, G->get_min_p(), Round1);
	double Error_p;
	for (int Ro = 1; Ro <= Round1; Ro++) {
		map<pair<int, int>, int>::iterator it;
		for (it = Count.begin(); it != Count.end(); it++) {
			double px = 0.01 * (random(100) + 1);
			double ex = Pr[it->first];
			if (px <= ex) Count[it->first]++;
		}
		printf("%d\n", Ro);
	}
	rout.close();

	ofstream out;
	out.open("Graph_P.txt");
	map<pair<int, int>, double>::iterator it;
	for (it = Pr.begin(); it != Pr.end(); it++) {
		pair<int, int> p1 = it->first;
		out << p1.first << '	' << p1.second << '	' << (1.0 * Count[p1]) / (1.0 * Round1) << endl;
	}
	out.close();
}

int main()
{
	srand((int)time(0));
	char buffer[256];
	Graph *G = new Graph;
	ifstream in("./Data/104.txt");
	if (!in.is_open()) {
		printf("Error opening file");
		return 0;
	}
	printf("ok\n");
	bool is_oneline = true;
	double P = 0.0;
	while (!in.eof()) {
		in.getline(buffer, 100);
		int len = strlen(buffer);
		if (buffer[0] == 'c') continue;
		int x1 = 0, x2 = 0, k = 0;
		if (buffer[0] == 'p') k = 5;
		else if (buffer[0] == 'a') k = 2;
		double px = 0.0;
		for (k; k < len; k++) {
			if (buffer[k] == ' ') break;
			x1 = x1 * 10 + (int)(buffer[k] - '0');
		}
		k++;
		if (is_oneline) {
			G->init(x1);
			is_oneline = false;
			//printf("%d\n", x1);
		}
		else {
			for (; k < len; k++) {
				if (buffer[k] == ' ') break;
				x2 = x2 * 10 + (int)(buffer[k] - '0');
			}
			k++;
			for (; k < len; k++) {
				if (buffer[k] == ' ') break;
				px = px * 10 + (int)(buffer[k] - '0');
			}
			px /= 100;
			if (x1 == 0 && x2 == 0) break;
			x1++; x2++;
			G->add_Edge(x1, x2, px);
			//printf("%d %d %.2f",x1,x2,px);
		}
	}
	in.close();

	Create_P(G);
}

