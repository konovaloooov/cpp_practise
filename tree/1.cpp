#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
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

tree *find( tree *tr, int x){//поиск
    if (! tr || x == tr->inf)//нашли или дошли до конца ветки
        return tr;
    if (x < tr->inf)
        return find(tr->left, x);//ищем по левой ветке
    else
        return find(tr->right, x);//ищем по правой ветке
}

tree *Min(tree *tr){//поиск min
    if (! tr->left) return tr;//нет левого ребенка
    else return Min(tr->left);//идем по левой ветке до конца
}

tree *Max(tree *tr){//поиск max
    if (! tr->right) return tr;//нет правого ребенка
    else return Max(tr->right);//идем по правой ветке до конца
}

tree *Next(tree*tr, int x){//поиск следующего
    tree* n = find( tr , x);
    if (n->right)//если есть правый ребенок
        return Min(n->right);//min по правой ветке
    tree *y = n->parent; //родитель
    while (y && n == y->right){//пока не дошли до корня или узел - правый ребенок
        n = y;//идем вверх по дереву
        y = y->parent;
    }
    return y;//возвращаем родителя
}

tree *Prev(tree *tr, int x){//поиск предыдущего
    tree *n = find(tr , x);
    if (n->left)//если есть левый ребенок
        return Max(n->left);//max по левой ветке
    tree *y = n->parent;//родитель
    while(y && n == y->left){//пока не дошли до корня или узел - левый ребенок
        n = y;//идем вверх по дереву
        y = y->parent;
    }
    return y;//возвращаем родителя
}

void Delete(tree *&tr, tree *v){//удаление узла
    tree *p = v->parent;
    if (!p) tr = NULL; //дерево содержит один узел
    else if (!v->left && !v->right){//если нет детей
        if (p->left == v) //указатель у родителя меняем на NULL
            p->left = NULL;
        if (p->right == v)
            p->right = NULL;
        delete v;       
    }
    else if (!v->left || !v->right){//если только один ребенок
        if (!p){ //если удаляем корень, у которого 1 ребенок
            if (!v->left){ //если есть правый ребенок
                tr = v->right; //он становится корнем
                v->parent = NULL;
            }
            else { //аналогично для левого
                tr = v->left;
                v->parent = NULL;
            }
        }
        else {
            if (!v->left){//если есть правый ребенок
                if (p->left == v) //если удаляемый узел явл. левым ребенком
                    p->left = v->right; //ребенок удаляемого узла становится левым ребенком своего "деда"
                else
                    p->right = v->right; ////ребенок удаляемого узла становится правым ребенком своего "деда"
                    v->right->parent = p; //родителем ребенка становится его "дед"
            }
            else{//аналогично для левого ребенка
                if (p->left == v)
                    p->left = v->left;
                else
                p->right = v->left;
                v->left->parent = p;
            }
            delete v;
        }
    }
    else{//есть оба ребенка
        tree *succ = Next(tr, v->inf);//следующий за удаляемым узлом
        v->inf = succ->inf; //присваиваем значение
        if (succ->parent->left ==succ){//если succ левый ребенок
            succ->parent->left = succ->right; //его правый ребенок становится левым ребенком своего "деда"
            if (succ->right) //если этот ребенок существует
                succ->right->parent = succ->parent; //его родителем становится "дед"
        }
        else {//аналогично если succ - правsq ребенок
            succ->parent->right = succ->right;
            if (succ->right)
            succ->right->parent = succ->parent;
        }
        delete succ;
    }
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
    for(int x = 0; x < n; x+=2){
        if (find( tr ,x)){
            Delete(tr , find (tr , x));
        }
    }
    cout << "modified tree:" << endl;
    k = int(log((float)n) / log((float)2.0));
    print ( tr, k );
    cout << endl;
    return 0;
    }