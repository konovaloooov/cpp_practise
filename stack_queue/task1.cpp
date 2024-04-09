#include<iostream>
#include <cstdlib>
using namespace std;

struct queue {
    int inf;
    queue *next;
};

void push(queue *&h, queue*&t, int x) {
    queue *r = new queue; 
    r->inf = x;
    r->next = NULL;
    if (!h && !t) { 
        h = t = r; 
    }
    else {
        t->next = r; 
        t = r;
    }
}

int pop(queue *&h, queue *&t) {
    int i = h->inf; 
    queue *r = h;
    h = h->next;
    if (!h) 
        t = NULL;
    delete r; 
    return i;
}

void result(queue *&h, queue *&t) {
    queue *h_tmp = NULL, *t_tmp = NULL;
    int lo = INT_MAX, max_ = INT_MIN, x;
    while (h && t) {
        x = pop(h, t);
        if (x & 1)
            lo = x;
        if (x > max_)
            max_ = x;
        push(h_tmp, t_tmp, x);
    }
    while(h_tmp && t_tmp){
        x = pop(h_tmp, t_tmp);
        push(h, t, x);
        if (x == max_)
            push(h, t, lo);
    }
}
int main(){
    queue *h = NULL, *t = NULL;
    int n, x;
    cout << "Количество элеметов в заданной очереди n = "; cin >> n;
    system("clear");
    cout << "Введите элементы очереди:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(h, t, x);
    }
    cout << endl;
    result(h, t); cout << "Результат: " << endl;
    while (h && t )
        cout << pop(h, t) << " ";
    cout << endl;
    return 0;
}