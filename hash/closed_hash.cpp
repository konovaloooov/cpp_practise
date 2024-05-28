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

const int M = 25; // Размерность хэш-таблицы
const int INF = -1;
const float A = (sqrt(5) - 1) / 2;

int h(base value){
    float a1 = value.experience * A;
    int tmp = a1;
    int res = (a1 - tmp) * M;
    return res; // Простая хэш-функция
}
int f(int k, int j) {
    return (k + j) % M; // Линейное пробирование для разрешения коллизий
}

void createHashTable(vector <base>& staff, vector<int>& hashTable) {
    hashTable.assign(M, INF); // Создаем хэш-таблицу и заполняем ее значением INF

    for (int i = 0; i < staff.size(); i++) {
        int k = h(staff[i]);
        int j = 0;

        while (true) {
            int p = f(k, j);

            if (hashTable[p] == INF) {
                hashTable[p] = i;
                break;
            } else {
                j++;
            }
        }
    }
} 
void find(vector <base>& staff, vector<int>& hashTable, string obj) {
    int key;
    bool fl = false;
    for (int i = 0; i < staff.size(); i++) {
        if (staff[i].surname == obj){
            key = h(staff[i]);
            fl = true;
            break;
        }
    }
    if (!fl){
        cout << "Сотрудник не найден";
        return;
    }
    for (int j = key; j < hashTable.size(); j++){
        if (staff[hashTable[j]].surname == obj){
            cout << "Сотрудник найден: " << endl;
            cout << setw(10) << "|surname|" << setw(15) << "|post|" << setw(15) << "|birthday|" << setw(13) << "|experience|" << setw(10) << "|salary|" << endl;
            cout << setw(10) << staff[hashTable[j]].surname << setw(15) << staff[hashTable[j]].post << setw(15) << staff[hashTable[j]].date << setw(7) << staff[hashTable[j]].experience << setw(16) << staff[hashTable[j]].salary << endl;
            break;
        }
        else if(hashTable[j] == INF){
            cout << "Сотрудник не найден";
            break;
        }
    }
}
void outhash(vector<int>& hashTable, vector <base>& staff) {
    for (int i = 0; i < M; i++) {
        cout << "hash key " << i << ": " << staff[hashTable[i]].surname << endl;
    }
    cout << endl;
}


int main(){
    vector <base> staff;
    fill(staff);
    
    vector<int> hashTable(M); // Создаем пустую хэш-таблицу размерности M
    createHashTable(staff, hashTable); // Создаем хэш-таблицу
    outhash(hashTable, staff);// Выводим содержимое хэш-таблицы

    string sur;
    cout << "Введите фамилию для поиска в базе данных: "; cin >> sur;
    find(staff, hashTable, sur);

    return 0;

}
