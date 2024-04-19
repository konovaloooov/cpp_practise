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

void insert_begin(list *&t, list *&h, list *r, int y){ //вставляем после r
    list *p = new list; 
    p->inf = y;
    if (r == t){ 
        p->prev = NULL; 
        p->next = r; 
        r->prev = p;
        t = p; 
        t -> prev = NULL;
    }
}

void del_curr(list *&h, list *&t, list *r) {
    if (r == h && r == t) 
        h = t = NULL; 
    else if (r == h) {
        h = h->next; 
        h->prev = NULL;
    }
    else if (r == t) {
        t = t->prev;
        t->next = NULL;
    }
    else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}
void result(list *&h, list *&t, int k, int n){
    bool flag = false;
    list *p = t;
    for(int i = 0; i < n; i++){
        int tmp = p->inf;
        if (tmp < k) {
            insert_begin(h,t,h,tmp);
            list *k = p->next;
            del_curr(h, t, p);
            p = k;
        }
        p = p -> prev;
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
    int n, y, k;
    list *h = NULL;
    list *t = NULL;
    cout << "n = ";
    cin >> n;
    cout << "k = ";
    cin >> k;
    cout << "origin: ";
    for (int i = 0; i < n; i++) {
        cin >> y;
        push(h, t, y); 
    }
    result(h, t, k, n);
    cout << "result: ";
    print(h, t);
    del_list(h);
    return 0;
}