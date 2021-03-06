// ProbabilisticCore.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Graph.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <fstream>
#include <ctime>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 0x7fffffff;
#define random(x) (rand() % x)

string outname = "NewProbabilisticCore";

struct node {
	int core;
	double p;
};

bool cmp(node a, node b) {
	if (a.p > b.p) return true;
	if (a.p == b.p && a.core > b.core) return true;
	return false;
}

int calc_etadeg(Graph* G, map<pair<int, int>, double>* Pr, int ti, int tx, double eta) {
	int ans = 0;

	//int tx = VertexList[ti];
	int *NeighborList = G->get_Neighbor(tx);
	int mx = G->get_Deg(tx);
	double **PX = new double*[2];
	for (int i = 0; i < 2; i++) PX[i] = new double[mx + 5];
	PX[0][0] = 1;
	for (int i = 1; i <= mx; i++) {
		pair<int, int> p1(ti, NeighborList[i]);
		double Ph = (*Pr)[p1];
		PX[i % 2][0] = (1.0 - Ph) * PX[(i - 1) % 2][0];
		for (int j = 1; j <= i - 1; j++) {
			PX[i % 2][j] = Ph * PX[(i - 1) % 2][j - 1] + (1.0 - Ph) * PX[(i - 1) % 2][j];
		}
		PX[i % 2][i] = Ph * PX[(i - 1) % 2][i - 1];
	}
	for (int i = mx; i >= 0; i--) {
		if (PX[mx % 2][i] >= eta) {
			ans = i;
			break;
		}
	}
	delete[] PX[0];
	delete[] PX[1];
	delete[] PX;
	//delete[] VertexList;
	delete[] NeighborList;
	return ans;
}

int computeEtaCore(node* est, int n, int k, int de) {
	sort(est + 1, est + 1 + n, cmp);
	int *cnt = new int[k + 10];
	for (int i = 1; i <= k; i++) cnt[i] = 0;
	for (int i = 1; i <= de; i++) {
		int j = min(k, est[i].core);
		cnt[j]++;
	}
	for (int i = k; i >= 2; i--) {
		cnt[i - 1] += cnt[i];
	}
	int i = k;
	while (i > 0 && cnt[i] < i) i--;
	delete[] cnt;
	return i;
}

int* get_K_Core(Graph* G, double P) {
	int n = G->get_N();
	int m = G->get_M();
	int *VertexList = G->get_VertexList();
	bool *changed = new bool[n + 10];
	int *core = new int[n + 10];
	for (int i = 1; i <= n; i++) core[i] = G->get_Deg(VertexList[i]);
	map<pair<int, int>, double> Pr;
	map<pair<int, int>, int> Count;
	for (int i = 1; i <= n; i++) {
		int tx = VertexList[i];
		int *VertNeighborList = G->get_Neighbor(tx);
		int de = G->get_Deg(tx);
		for (int j = 1; j <= de; j++) {
			pair<int, int> p1(i, VertNeighborList[j]);
			if (Pr.count(p1) == 0) {
				Pr.insert(pair<pair<int, int>, double>(p1, 0.0));
				Count.insert(pair<pair<int, int>, int>(p1, 0));
			}
		}
		delete[] VertNeighborList;
	}
	//vector<int> Edelete;
	vector<int> Tchanged;
	vector<double> ETime;
	vector<double> Error_p;
	int tot = 0;
	clock_t startTime, endTime;
	ofstream out;
	out.open("NewProbabilisticCore_Round.txt");
	int Round1 = (int)(ceil(log10(n) / P));
	printf("%d %.2f %d\n", n, G->get_min_p(), Round1);

	while (tot != Round1) {
		startTime = clock();
		for (int i = 1; i <= n; i++) changed[i] = false;
		double err = 0.0;

		for (int i = 1; i <= n; i++) {
			int tx = VertexList[i];
			int *NeighborList = G->get_Neighbor(tx);
			int de = G->get_Deg(tx);
			for (int j = 1; j <= de; j++) {
				pair<int, int> p1(i, NeighborList[j]);
				double px = 0.01 * (random(100) + 1);
				double ex = G->get_p(tx, j);
				if (px <= ex)
					Count[p1]++;
				Pr[p1] = (1.0 * Count[p1]) / (1.0 * tot + 1.0);
				err += fabs(Pr[p1] - ex);
			}
			int etadeg = calc_etadeg(G, &Pr, i, tx, P);
			node *NeighborCore = new node[de + 10];
			for (int j = 1; j <= de; j++) {
				NeighborCore[j].core = core[NeighborList[j]];
				NeighborCore[j].p = G->get_p(tx, j);
			}
			int t = computeEtaCore(NeighborCore, de, core[i], etadeg);
			if (t != core[i]) {
				core[i] = t;
				changed[i] = true;
			}
			delete[] NeighborCore;
			delete[] NeighborList;
		}

		Error_p.push_back(err);
		Tchanged.push_back(0);
		for (int i = 1; i <= n; i++) {
			if (changed[i] == false) Tchanged[tot]++;
			changed[i] = false;
		}
		tot++;
		printf("%d %.2f\n", tot, err);
		endTime = clock();
		double nowTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		ETime.push_back(nowTime);
		out << "This " << tot << " round, Not Changed Nodes = " << Tchanged[tot - 1] << ", Run Times = " << nowTime << endl;
		ofstream outt;
		outt.open("./Result/" + outname + to_string(tot) + ".txt");
		for (int i = 1; i <= n; i++) {
			outt << core[i] << endl;
		}
		outt.close();
		//if (n - Tchanged[tot - 1] <= 10) break;
	}

	while (true) {
		startTime = clock();
		for (int i = 1; i <= n; i++) changed[i] = false;
		double err = 0.0;

		for (int i = 1; i <= n; i++) {
			int tx = VertexList[i];
			int *NeighborList = G->get_Neighbor(tx);
			int de = G->get_Deg(tx);
			for (int j = 1; j <= de; j++) {
				pair<int, int> p1(i, NeighborList[j]);
				double px = 0.01 * (random(100) + 1);
				double ex = G->get_p(tx, j);
				if (px <= ex) 
					Count[p1]++; 
				Pr[p1] = (1.0 * Count[p1]) / (1.0 * tot + 1.0);
				err += fabs(Pr[p1] - ex);
			}
			int etadeg = calc_etadeg(G, &Pr, i, tx, P);
			node *NeighborCore = new node[de + 10];
			for (int j = 1; j <= de; j++) {
				NeighborCore[j].core = core[NeighborList[j]];
				NeighborCore[j].p = G->get_p(tx, j);
			}
			int t = computeEtaCore(NeighborCore, de, core[i], etadeg);
			if (t != core[i]) {
				core[i] = t;
				changed[i] = true;
			}
			delete[] NeighborCore;
			delete[] NeighborList;
		}

		Error_p.push_back(err);
		Tchanged.push_back(0);
		for (int i = 1; i <= n; i++) {
			if (changed[i] == false) Tchanged[tot]++;
			changed[i] = false;
		}
		tot++;
		printf("%d %.2f\n", tot, err);
		endTime = clock();
		double nowTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		ETime.push_back(nowTime);
		out << "This " << tot << " round, Not Changed Nodes = " << Tchanged[tot - 1] << ", Run Times = " << nowTime << endl;
		ofstream outt;
		outt.open("./Result/" + outname + to_string(tot) + ".txt");
		for (int i = 1; i <= n; i++) {
			outt << core[i] << endl;
		}
		outt.close();
		if (n - Tchanged[tot - 1] <= 10) break;
	}
	out.close();

	ofstream rout;
	rout.open(outname + "_Error.txt");
	for (int i = 0; i < tot; i++) {
		rout << Error_p[i] << endl;
	}
	rout.close();

	delete[] VertexList;
	delete[] changed;
	return core;
}

int main()
{
	srand((int)time(0));
	char buffer[256];
	Graph *G = new Graph;
	ifstream in("./106.txt");
	if (!in.is_open()) {
		printf("Error opening file");
		return 0;
	}
	bool is_oneLine = true;
	double P = 0.0;
	while (!in.eof()) {
		in.getline(buffer, 100);
		int len = strlen(buffer);
		int x1 = 0, x2 = 0, k = 0;
		double px = 0.0;
		for (k; k < len; k++) {
			if (buffer[k] == '	') break;
			x1 = x1 * 10 + (int)(buffer[k] - '0');
		}
		k++;
		if (is_oneLine) {
			G->init(x1);
			is_oneLine = false;
		}
		else {
			for (; k < len; k++) {
				if (buffer[k] == '	') break;
				x2 = x2 * 10 + (int)(buffer[k] - '0');
			}
			k++;
			for (; k < len; k++) {
				if (buffer[k] == '.') break;
				px = px * 10.0 + 1.0 * (int)(buffer[k] - '0');
			}
			double td = 0.1;
			k++;
			for (; k < len; k++) {
				px = px + td * (int)(buffer[k] - '0');
				td *= 0.1;
			}
			if (x1 == 0 && x2 == 0) break;
			x1++; x2++;
			G->add_Edge(x1, x2, px);
		}
	}
	in.close();
	printf("Please print eta : ");
	cin >> P;

	int *ans;
	ans = get_K_Core(G, P);

	int n = G->get_N();
	ofstream out;
	out.open(outname + ".txt");
	for (int i = 1; i <= n; i++) {
		out << ans[i] << endl;
	}
	out.close();
	return 0;
}

