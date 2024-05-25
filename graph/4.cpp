#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Graph {
    int V; // количество вершин
    vector< vector<int> > adjList; // список смежности
    Graph(int n) {
        V = n;
        adjList.resize(V);
    }
    void add(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // для неориентированного графа
    }
    void uni(){
        for (int i = 0; i < V; i++) {
            adjList[i].erase(unique(adjList[i].begin(), adjList[i].end()), adjList[i].end());
        }
    }
    void print(){
        for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (int j = 0; j < adjList[i].size(); ++j) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
    }
    void dfs(vector< vector<int> >& Gr, int x, vector<int>& used, vector<int>& path) {
        used[x] = 1;
        path.push_back(x);
        for (int i = 0; i < Gr[x].size(); i++) 
            if (used[Gr[x][i]] == 0)
                dfs(Gr, Gr[x][i], used, path);
    }


};

int main() {
    ifstream in("input2.txt");
    int n, n1, n2;
    in >> n;
    Graph Gr(n); // создаем граф с 5 вершинами
    while(in.peek() != EOF){
        in >> n1 >> n2;
        Gr.add(n1, n2);
    }
    Gr.uni();

    // cout << "Список смежности графа:" << endl;
    // Gr.print();

    vector<int> used(Gr.adjList.size(), 0);
    vector<int> path;
    Gr.dfs(Gr.adjList, 0, used, path);

    if (find(used.begin(), used.end(), 0) != used.end())
        cout << "Несвязный граф";
    else cout << "Связный граф";
  
    return 0;
}
