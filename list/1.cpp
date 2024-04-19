#include <iostream>
using namespace std;
struct list {
    int inf;
    list *next;
    list *prev;
};

void push (list *&h, list *&t, int x){ //вставка элемента в конец списка
    list *r = new list; //создаем новый элемент
    r->inf = x;
    r->next = NULL; //всегда последний
    if (!h && !t){ //если список пуст
        r->prev = NULL; //первый элемент
    h = r; //это голова
    }
    else{
        t->next = r; //r - следующий для хвоста
        r->prev = t; //хвост - предыдущий для r
    }
    t = r; //r теперь хвост
}

void print (list *&h, list *&t){ //печать элементов списка
    list *p = h; //укзатель на голову
    while (p){ //пока не дошли до конца списка
    cout << p->inf << " ";
    p = p->next; //переход к следующему элементу
    }
}
void insert_after(list *&h, list *&t, list *r, int y){ //вставляем после r
    list *p = new list; //создаем новый элемент
    p->inf = y;
    if (r == t){ //если вставляем после хвоста
        p->next = NULL; //вставляемый эл-т - последний
        p->prev = r; //вставляем после r
        r->next = p;
        t = p; //теперь хвост - p
    }
    else{ //вставляем в середину списка
        r->next->prev = p; //для следующего за r эл-та предыдущий - p
        p->next = r->next; //следующий за p - следующий за r
        p->prev = r; //p вставляем после r
        r->next = p;
    }
}

int minn(list *&h, list *&t){ //печать элементов списка
    list *p = h; //укзатель на голову
    int min_ = INT_MAX;
    while (p){ //пока не дошли до конца списка
        if (p->inf < min_) min_ = p->inf;
        p = p->next;
    }
    return min_; //возвращаем указатель
}

int even(list *&h, list *&t){ //печать элементов списка
    list *p = h; //укзатель на голову
    int e = INT_MIN;
    while (p){ //пока не дошли до конца списка
        if (!(p->inf & 1)) e = p->inf;
        p = p->next;
    }
    return e; //возвращаем указатель
}

void result(list *&h, list *&t) {
    int min_i = minn(h,t);
    int ev = even(h, t);
    list *p = h; //укзатель на голову
    while (p){ //пока не дошли до конца списка
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
    //инициализируем список
    list *h = NULL;
    list *t = NULL;
    cout << "n = ";
    cin >> n;//вод количества элементов
    cout << "origin: ";
    for (int i = 0; i < n; i++) { //ввод самих элементов
        cin >> y;
        push(h, t, y); //добавление элемента в стек
    }
    result(h, t);
    cout << "result: ";
    print(h, t);//выводим полученный список
    del_list(h);
    return 0;
}