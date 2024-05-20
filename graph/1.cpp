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
        adjList[u].push_back(v);
        adjList[v].push_back(u); // для неориентированного графа
    }
    void uni(){
        for (int i = 0; i < V; i++) {
        adjList[i].erase(unique(adjList[i].begin(), adjList[i].end()), adjList[i].end());
    }
    }
};

int main() {
    ifstream in("input.txt");
    int n, n1, n2;
    in >> n;
    Graph Gr(n); // создаем граф с 5 вершинами
    while(in.peek() != EOF){
        in >> n1 >> n2;
        Gr.add(n1, n2);
    }
    Gr.uni();

    cout << "Выберите вершину графа из списка: ";
     for (int i = 0; i < Gr.V; ++i)
        cout << i << " ";
    cout << endl;
    int k;
    cout << "Вершина: "; cin >> k;
    
    cout << "Количество вершин, смежных с данной: " << Gr.adjList[k].size() << endl;

    // cout << "Список смежности графа:" << endl;
    // for (int i = 0; i < Gr.V; ++i) {
    //     cout << i << ": ";
    //     for (int j = 0; j < Gr.adjList[i].size(); ++j) {
    //         cout << Gr.adjList[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}
