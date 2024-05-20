#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Graph {
    int V; // количество вершин
    vector< vector<int> > adjList; // список смежности
    Graph(int n) {
        V = n;
        adjList.resize(V);
    }
    void add(int u, int v) {
        adjList[u].push_back(v); // для ориентированного графа
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

};

int main() {
    ifstream in("input1.txt");
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
    cout << "Полустепень исхода:" << endl;
    for (int i = 0; i < Gr.V; ++i) 
        cout << i << ": " << Gr.adjList[i].size() << endl;
    return 0;
}
