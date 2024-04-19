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

void insert_begin(list *&t, list *&h, list *r, int y){ //вставляем после r
    list *p = new list; //создаем новый элемент
    p->inf = y;
    if (r == t){ //если вставляем после хвоста
        p->prev = NULL; //вставляемый эл-т - последний
        p->next = r; //вставляем после r
        r->prev = p;
        t = p; //теперь хвост - p
        t -> prev = NULL;
    }
}

void del_curr(list *&h, list *&t, list *r) {
    if (r == h && r == t) //если в списке один элемент
        h = t = NULL; //то список будет пустым
    else if (r == h) { //если надо удалить первый элемент в списке
        h = h->next; //то сдвигаем голову h на один элемент
        h->prev = NULL;
    }
    else if (r == t) { //если удаляем последний элемент
        t = t->prev; //сдвигаем хвост на один элемент влево
        t->next = NULL;
    }
    else {//случай когда удаляемый элемент в середине списка
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r; //удаляем r
}
void result(list *&h, list *&t, int k, int n){
    bool flag = false;
    list *p = t;//указатель на голову
    for(int i = 0; i < n; i++){//пока не дошли до конца списка
        int tmp = p->inf;
        if (tmp < k) {
            insert_begin(h,t,h,tmp);
            list *k = p->next;
            del_curr(h, t, p);
            p = k;
        }
        p = p -> prev;//присваиваем p следующий элемент
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
    //инициализируем список
    list *h = NULL;
    list *t = NULL;
    cout << "n = ";
    cin >> n;//вод количества элементов
    cout << "k = ";
    cin >> k;//вод количества элементов
    cout << "origin: ";
    for (int i = 0; i < n; i++) { //ввод самих элементов
        cin >> y;
        push(h, t, y); //добавление элемента в стек
    }
    result(h, t, k, n);
    cout << "result: ";
    print(h, t);//выводим полученный список
    del_list(h);
    return 0;
}