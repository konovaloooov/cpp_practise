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

void result(list *&h, list *&t){
    list *p = h;
    while (p){ 
        list *tmp_p = p->next;
        int sum_ = 0, c = 0;
        while (tmp_p){
            sum_ += tmp_p -> inf;
            c++;
            tmp_p = tmp_p->next;
        }
        if(c){
            float sr_a = sum_ / c;
            if (p -> inf > sr_a){
                list *k = p->next;
                del_curr(h, t, p);
                p = k;
            }
        }
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