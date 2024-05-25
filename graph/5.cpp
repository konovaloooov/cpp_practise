#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

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


    void bfs(vector< vector<int> >& graph, int a, int b) {
    
    vector<int> path(V, -1);
    queue<int> q;

    q.push(a);
    path[a] = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int v = 0; v <= graph[cur].size(); v++) {
            if (path[graph[cur][v]] == -1) {
                path[graph[cur][v]] = path[cur] + 1;
                q.push(graph[cur][v]);
            }
        }
    }
    if (path[b] != -1)
        cout << "Кратчайший путь между вершинами " << a << " и " << b << " равен " << path[b] << endl;
    else cout << "Пути между вершинами нет.";
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

    // cout << "Список смежности графа:" << endl;
    // Gr.print();
    cout << "Введите a и b: ";
    int a, b;
    cin >> a >> b;
    Gr.bfs(Gr.adjList, a, b); 

    return 0;
}
