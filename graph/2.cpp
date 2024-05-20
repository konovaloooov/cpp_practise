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
    void print(){
        for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for (int j = 0; j < adjList[i].size(); ++j) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
    }
    bool rm(int u, int v) {
        bool fl = false;
        for (int i = 0; i < adjList[u].size(); i++) {
            if (adjList[u][i] == v) {
                adjList[u].erase(adjList[u].begin() + i);
                fl = true;
                break;
            }
        }
        for (int i = 0; i < adjList[v].size(); i++) {
            if (adjList[v][i] == u) {
                adjList[v].erase(adjList[v].begin() + i);
                fl = true;
                break;
            }
        }
        if(!fl){
            cout << "Такого ребра нет в данном графе..." << endl;
            return false;
        }
        return true;
    }

};

int main() {
    ifstream in("input.txt");
    int n, n1, n2;
    in >> n;
    Graph Gr(n); 
    while(in.peek() != EOF){
        in >> n1 >> n2;
        Gr.add(n1, n2);
    }
    Gr.uni();

    cout << "Список смежности графа(до удаления):" << endl;
    Gr.print();

    cout << "Выберите вершины графа, между которыми удалить ребро: " << endl;
    int k1, k2;
    cout << "Вершины: "; cin >> k1 >> k2;
    cout << endl;
    if(Gr.rm(k1, k2)){
        cout << "Список смежности графа(после удаления):" << endl;
        Gr.print();
    }

    return 0;
}
