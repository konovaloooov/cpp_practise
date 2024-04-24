#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
using namespace std;

ifstream in("input.txt");

struct tree //динамическая структура дерева
{
    int inf;
    tree *right;
    tree *left;
};

tree *node(int x) //определение корня дерева
{
    tree *n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    return n;
}

void create(tree *&tr, int n)//алгоритм заполнения идеально сбаланс. дерева
{
    int x;
    if (n > 0)
    {
        in >> x;
        tr = node(x);
        int nl = n / 2;
        int nr = n - nl - 1;
        create(tr->left, nl);
        create(tr->right, nr);
    }
}

void preorder(tree *tr) //прямой обсход(К-Л-П) - лучше подходит для ИСБ
{
    if (tr)
    {
        cout << tr->inf << " ";
        preorder(tr->left);
        preorder(tr->right);
    }
}

void print(tree *tr, int k) //вывод в виде дерева
{
    if (!tr)
        cout << "Empty tree\n";
    else
    {
        queue<tree *> cur, next; //создаем очередь для конкретного и следующего
        tree *r = tr;
        cur.push(r);
        int j = 0;
        while (cur.size())
        {
            if (j == 0)
            {
                for (int i = 0; i < (int)pow(2.0, k) - 1; i++)
                    cout << " "; //расстояние между элементами одного уровня
            }
            tree *buf = cur.front(); //передний элемент очереди в буфер
            cur.pop();
            j++;
            if (buf) //если не лист, дальше 
            {
                cout << buf->inf;
                next.push(buf->left);
                next.push(buf->right);
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    cout << " ";
            }
            if (!buf) //иначе конец
            {
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    cout << " ";
                cout << " ";
            }
            if (cur.empty()) //меняем местами и переходим к след
            {
                cout << endl;
                swap(cur, next);
                j = 0;
                k--;
            }
        }
    }
}
int findDepth(tree* root, int value, int depth) {
    if (root) { //если непустое дерево от этого корня
        if (root->inf == value) {
            return depth; //нашлось значение - конец
        }
        int leftDepth = findDepth(root->left, value, depth + 1); //обход рекурсивно по левой ветке каждого узла
        if (leftDepth) {
            return leftDepth;
        }
        return findDepth(root->right, value, depth + 1); //по правой
    }
    return 0;
}
int main()
{
    tree *tr = NULL;
    int n, x;
    in >> n;
    create(tr, n);
    int k = int(log((float)n) / log((float)2.0)); //расстояние между элементами
    print(tr, k);
    preorder(tr);
    cout << endl;
    cout << "X = "; cin >> x;
    cout << "Глубина узла X: " << findDepth(tr, x, 0)<< endl;
    return 0;
}