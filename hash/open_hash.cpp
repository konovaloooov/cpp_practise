#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
struct base{ 
    string surname, post, date;
    int birth, experience, salary;
};
struct elem{
    string s;
    int n; //pos в базе данных
};
struct Node {
    elem val;
    Node* next;

    Node(elem _val) : val(_val), next(nullptr) {}
};

struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}

    bool is_empty() {
        return first == nullptr;
    }

    void push_back(elem _val) {
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void print() {
        if (is_empty()) return;
        Node* p = first;
        while (p) {
            cout << p->val.s << " ";
            p = p->next;
        }
        cout << endl;
    }
    Node* find(string _val) {
        Node* p = first;
        while (p && p->val.s != _val) p = p->next;
            return (p && p->val.s == _val) ? p : nullptr;
    }
    void remove_first() {
        if (is_empty()) return;
        Node* p = first;
        first = p->next;
        delete p;
    }

    void remove_last() {
        if (is_empty()) return;
        if (first == last) {
            remove_first();
            return;
        }
        Node* p = first;
        while (p->next != last) p = p->next;
        p->next = nullptr;
        delete last;
        last = p;
    }

    void remove(string _val) {
        if (is_empty()) return;
        if (first->val.s == _val) {
            remove_first();
            return;
        }
        else if (last->val.s == _val) {
                remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->val.s != _val) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            cout << "Элемент не существует'" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
    }
};

void fill(vector <base> &staff){ 
    ifstream in("input.txt");
    while(in.peek() != EOF){
        base elem;
        string one, two, three, four, five;
        in >> one >> two >> three >> four >> five;
        elem.surname = one;
        elem.post = two;
        elem.date = three;

        string str1 = three.substr(3, 2);
        int mm = atoi(str1.c_str());
        elem.birth = mm;

        elem.experience = atoi(four.c_str());
        elem.salary = atoi(five.c_str());
        staff.push_back(elem);
    }
}
void outfile(vector <base> &staff){
    ofstream out("output.txt");
    out << setw(10) << "|surname|" << setw(15) << "|post|" << setw(15) << "|birthday|" << setw(13) << "|experience|" << setw(10) << "|salary|" << endl;
    for (int i = 0; i < staff.size(); i++)
        out << setw(10) << staff[i].surname << setw(15) << staff[i].post << setw(15) << staff[i].date << setw(7) << staff[i].experience << setw(16) << staff[i].salary << endl;
    cout << "Данные сохранены в файле output.txt";
}

const int M = 12; // Размерность хэш-таблицы

int h(base value){
    return value.birth % M; // Простая хэш-функция
}

void createHashTable(vector <base>& staff, vector< list >& hashTable) {
    for (int i = 0; i < staff.size(); i++) {
        int key = h(staff[i]); // Вычисляем значение хэш-функции
        elem tmp;
        tmp.s = staff[i].surname;
        tmp.n = i;

        hashTable[key].push_back(tmp); // Добавляем элемент в соответствующий список хэш-таблицы
    }
} 
void outhash(vector< list >& hashTable){
    for (int i = 0; i < M; i++) {
        cout << "hash key " << i << ": ";
        hashTable[i].print();
    }
    cout << endl;
}

void del(vector< list >& hashTable, string obj, vector <base>& staff){
    int key = -1;
    for (int i = 0; i < staff.size(); i++) {
        if (staff[i].surname == obj){
            key = h(staff[i]);
            break;
        }
    }
    Node* p;
    if(key == -1)
        p = nullptr;
    else
        p = hashTable[key].find(obj);
    if (p != nullptr){
            staff.erase(staff.begin() + (p->val).n);
            hashTable[key].remove(obj);
            cout << "Удаление произошло успешно" << endl;
            cout << endl;
            outhash(hashTable);
    }
    else
        cout << "Сотрудник не найден" << endl;
}

void find(vector< list >& hashTable, string obj, vector <base>& staff){
    int key = -1;
    for (int i = 0; i < staff.size(); i++) {
        if (staff[i].surname == obj){
            key = h(staff[i]);
            break;
        }
    }
    Node* p;
    if(key == -1)
        p = nullptr;
    else
        p = hashTable[key].find(obj);
    if (p != nullptr){
             cout << "Сотрудник найден: " << endl;
                cout << setw(10) << "|surname|" << setw(15) << "|post|" << setw(15) << "|birthday|" << setw(13) << "|experience|" << setw(10) << "|salary|" << endl;
                cout << setw(10) << staff[(p->val).n].surname << setw(15) << staff[(p->val).n].post << setw(15) << staff[(p->val).n].date << setw(7) << staff[(p->val).n].experience << setw(16) << staff[(p->val).n].salary << endl;
    }
    else
        cout << "Сотрудник не найден" << endl;
    cout << endl;
}

int main(){
    vector <base> staff;
    fill(staff);
    
    vector< list > hashTable(M); // Создаем пустую хэш-таблицу размерности M
    createHashTable(staff, hashTable); // Создаем хэш-таблицу
    outhash(hashTable);// Выводим содержимое хэш-таблицы

    string sur;
    cout << "Введите фамилию для поиска в базе данных: "; cin >> sur;
    cout << endl;
    find(hashTable, sur, staff);

    cout << "Введите фамилию для удаления из базы данных: "; cin >> sur;
    del(hashTable, sur, staff);
    outfile(staff);
    return 0;

}