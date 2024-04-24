#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
using namespace std;

ifstream in("input.txt");

struct tree
{
    int inf;
    tree *right;
    tree *left;
};

tree *node(int x)
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

void print(tree *tr, int k)//вывод в виде дерева
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
int sum_(tree* root) { //сумма листьев
    if (root) {
        if (root->left == NULL && root->right == NULL) {
            return root->inf;
        }
        return sum_(root->left) + sum_(root->right);
    }
    return 0;
}
int main()
{
    tree *tr = NULL;
    int n, x;
    in >> n;
    create(tr, n);
    int k = int(log((float)n) / log((float)2.0));
    print(tr, k);
    preorder(tr);
    cout << endl;
    cout << "Сумма листьев: " << sum_(tr)<< endl;
    return 0;
}