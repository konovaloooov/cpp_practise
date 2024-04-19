#include <iostream>
using namespace std;
struct list {
    int inf;
    list *next;
    list *prev;
};

void push (list *&h, list *&t, int x){ 
    list *r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t){
        r->prev = NULL; 
    h = r;
    }
    else{
        t->next = r;
        r->prev = t;
    }
    t = r;
}

void print (list *&h, list *&t){ 
    list *p = h;
    while (p){ 
    cout << p->inf << " ";
    p = p->next; 
    }
}
void insert_after(list *&h, list *&t, list *r, int y){ 
    list *p = new list; 
    p->inf = y;
    if (r == t){
        p->next = NULL; 
        p->prev = r; 
        r->next = p;
        t = p; 
    }
    else{ 
        r->next->prev = p;
        p->next = r->next; 
        p->prev = r; 
        r->next = p;
    }
}

int minn(list *&h, list *&t){ 
    list *p = h;
    int min_ = INT_MAX;
    while (p){ 
        if (p->inf < min_) min_ = p->inf;
        p = p->next;
    }
    return min_; 
}

int even(list *&h, list *&t){
    list *p = h; 
    int e = INT_MIN;
    while (p){ 
        if (!(p->inf & 1)) e = p->inf;
        p = p->next;
    }
    return e; 
}

void result(list *&h, list *&t) {
    int min_i = minn(h,t);
    int ev = even(h, t);
    list *p = h; 
    while (p){ 
        if (p->inf == min_i)
            insert_after(h, t, p, ev);
        p = p->next;
    }
}
void del_list(list* &h) {
    list* cur = h;
    list* next;
    while (cur != NULL) {
        next = cur->next;
        delete cur;
        cur = next;
    }
    h = NULL;
}
int main(){
    int n, y;
    list *h = NULL;
    list *t = NULL;
    cout << "n = ";
    cin >> n;
    cout << "origin: ";
    for (int i = 0; i < n; i++) {
        cin >> y;
        push(h, t, y); 
    }
    result(h, t);
    cout << "result: ";
    print(h, t);
    del_list(h);
    return 0;
}