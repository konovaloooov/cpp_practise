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

int max_(stack *&h) {
    stack *temp = NULL;
    int max = pop(h), x; 
    push(temp, max); 
    while (h) {
        x = pop(h);
        if (x > max) 
            max = x; 
        push(temp, x);
    }
    reverse(temp);
    h = temp;
    return max;
}

int min_(stack *&h) {
    stack *temp = NULL;
    int min = pop(h), x; 
    push(temp, min); 
    while (h) {
        x = pop(h);
        if (x < min) 
            min = x; 
        push(temp, x);
    }
    reverse(temp);
    h = temp;
    return min;
}

stack *result(stack *&h){
    int max = max_(h);
    int min = min_(h);
    stack *temp = NULL;
    int x;
    while (h) {
        x = pop(h);
        push(temp, x);
        if (x == max) 
            push(temp, min);
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