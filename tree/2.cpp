#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

ifstream in("input1.txt");

struct tree{
    int inf;
    tree* right ;
    tree * left ;
    tree *parent;
};

tree *node(int x){//начальный узел
    tree *n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree *&tr, int x){//вставка
    tree *n = node(x);
    if (! tr ) tr = n; //если дерево пустое - корень
    else {
        tree *y = tr;
        while(y){ //ищем куда вставлять
            if (n->inf > y->inf) //правая ветка
                if (y->right)
                    y = y->right;
            else{
                n->parent = y; //узел становится правым ребенком
                y->right = n;
                break;
            }
            else if (n->inf < y->inf)//левая ветка
                if (y->left)
                    y = y->left;
                else{
                    n->parent = y;//узел становится левым ребенком
                    y->left = n;
                    break;
                }
        }
    }
}

void print(tree *tr, int k)
{
    if (!tr)
        cout << "Empty tree\n";
    else
    {
        queue<tree *> cur, next;
        tree *r = tr;
        cur.push(r);
        int j = 0;
        while (cur.size())
        {
            if (j == 0)
            {
                for (int i = 0; i < (int)pow(2.0, k) - 1; i++)
                    cout << " ";
            }
            tree *buf = cur.front();
            cur.pop();
            j++;
            if (buf)
            {
                cout << buf->inf;
                next.push(buf->left);
                next.push(buf->right);
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    cout << " ";
            }
            if (!buf)
            {
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    cout << " ";
                cout << " ";
            }
            if (cur.empty())
            {
                cout << endl;
                swap(cur, next);
                j = 0;
                k--;
            }
        }
    }
}

bool hasPath(tree *root, vector<int>& arr, int x)
{
    if (!root) //нет пути, если пустое дерево
        return false;
     
    arr.push_back(root->inf);    
     
    if (root->inf == x)    
        return true; //нашелся элемент - путь есть
     
    if (hasPath(root->left, arr, x) || //проверка, где находится требуемый узел(слева или справа)
        hasPath(root->right, arr, x))
        return true;
        
    arr.pop_back(); //если в искомой ветке нет нужного значения, удаляем узел, где дальше его нет
    return false;            
}
 

void printPath(tree *root, int x)
{

    vector<int> arr;
     
    //есть путь, выводим его в виде массива
    if (hasPath(root, arr, x))
    {
        for (int i=0; i<arr.size()-1; i++)    
            cout << arr[i] << "->";
        cout << arr[arr.size() - 1];    
    }
     
    //нет пути
    else
        cout << "No Path";
}
 

int main(){
    int n, x;
    in >> n;
    tree *tr = NULL;
    for(int i = 0; i < n; i++){
        in >> x;
        insert ( tr , x);
    }
    cout << "origin tree:" << endl;
    int k = int(log((float)n) / log((float)2.0));
    print ( tr, k);
    cout << endl;
    cout << "Узел: "; cin >> x;
    printPath(tr, x);
    return 0;
    }