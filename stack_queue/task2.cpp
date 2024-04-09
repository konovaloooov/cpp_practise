#include<iostream>
#include <cstdlib>
using namespace std;
struct stack {
    int inf;
    stack *next;
};
void push(stack *&h, int x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}
int pop(stack *&h) {
    int i = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return i;
}

void reverse(stack *&h) {
    stack *head1 = NULL; 
    while (h) 
        push(head1, pop(h)); 
    h = head1;

}

int last_odd(stack *&h) {
    reverse(h);
    stack *temp = NULL;
    int odd = INT_MAX, x;
    while(h) {
        x = pop(h);
        if (x & 1){ 
            odd = x; 
        }
        push(temp, x);
    }
    h = temp;
    return odd;
    
}

stack *result(stack *&h){
    int odd = last_odd(h);
    stack *temp = NULL;
    int new_el, x;
    cout << "Новый элемент = ";
    cin >> new_el;
    cout << endl;
    while (h) {
        x = pop(h);
        if (x == odd) 
            push(temp, new_el);
        push(temp, x);
    }
    return (temp);
}
int main() {
    stack *h = NULL;
    int n, x;
    cout << "Количество элеметов в заданном стеке n = "; cin >> n;
    system("clear");
    cout << "Введите элементы очереди:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(h, x);
    }
    cout << endl;
    h = result(h);
    cout << "Результат: " << endl; 
    while (h){
        cout << pop(h) << " ";
    }
    return 0;
}