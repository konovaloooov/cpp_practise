#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void fill(vector<vector<int> > &data, int n){ 
    ifstream in("input.txt");
    int tmp;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            in >> tmp;
            data[i].push_back(tmp);
        }
    }
}
void out_file(vector< vector<int> > data){
    ofstream out("output1.txt");
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++)
            out << data[i][j] << " ";
        out << endl;
    }
}
int r(){
    int n;
    cout << "Введите размерность массива: ";
    cin >> n;
    return n;
}
void block(vector<vector<int> > &data, int n){
    for(int x = 0; x < n; x++){
        int max_ = *max_element(data[x].begin(), data[x].end());
        int min_ = *min_element(data[x].begin(), data[x].end());
        float p = 5;
        float m = (max_ - min_) / p;
        vector< vector<int> > v(p);
        for (int j = 0; j < data[x].size(); j++){
            int k = round(data[x][j] - min_) / m;
            if (k == p)
                v[4].push_back(data[x][j]);
            else
                v[k].push_back(data[x][j]);
        }
        for (int k = 0; k < p; k++){
            for (int i = 1; i < v[k].size(); i++){
                int j = i;
                while (j > 0 && v[k][j] < v[k][j - 1]){
                    swap(v[k][j], v[k][j - 1]);
                    j--;
                }
            }
        }
        data[x].clear();
        for (int i = p - 1; i >= 0; i--){
            for (int j = v[i].size() - 1; j >= 0; j--)
                data[x].push_back(v[i][j]);
        }
    }
}

void merge_(vector <int> &data, int l, int r, int m, bool flag){ 
    if (l >= r || m < l || m > r)
        return;
    if (flag && r - l == 1 && data[l] < data[r]){
        swap(data[l], data[r]);
        return;
    }
    if (!flag && r - l == 1 && data[l] > data[r]){
        swap(data[l], data[r]);
        return;
    }
    vector<int> buf (r - l + 1);
    int cur = 0;
    int i = l, j = m + 1;
    while(r - l + 1 != cur){
        if (i > m){
            for(int y = j; y <= r; y++)
                buf[cur++] = data[y];
        }
        else if (j > r){
            for(int y = i; y <= m; y++)
                buf[cur++] = data[y];
        }
        else if (!flag && data[i] > data[j]){
            buf[cur++] = data[j++];
        }
        else if (flag && data[i] < data[j]){
            buf[cur++] = data[j++];
        }
        else{
            buf[cur++] = data[i++];
        }
    }
    for(int k = 0; k < r - l + 1; k++){
        data[l + k] = buf[k];
    }
}


void sep_(vector <int> &data, int l, int r, bool flag){
    if (l >= r){
        return;
    }
    int m = (l + r) / 2;
    sep_(data, l, m, flag);
    sep_(data, m + 1, r, flag);
    merge_(data, l, r, m, flag);
}

void even_odd(vector<int> &data){
    for (int i = 0; i < data.size(); i++){
        if (!(i & 1)){
            for (int j = 2; j < data.size(); j+=2){
                if (data[j - 1] > data[j]){
                    swap(data[j - 1], data[j]);
                }
            }
        }
        else{
            for (int j = 1; j < data.size(); j+=2){
                if (data[j - 1] > data[j]){
                    swap(data[j - 1], data[j]);
                }
            }
        }
        }
}

void main_diagonal(vector<vector<int> > &data, int n){
    for(int k = 0; k < n; k++){
        vector<int> tmp;

        for(int i = 0; i < n; i++){
            if(k + i < n)
                tmp.push_back(data[i][k + i]);
        }
        even_odd(tmp);
        int l = 0;
        for(int i = 0; i <= n; i++){
            if(k + i < n){
                data[i][k + i] = tmp[l];
                l++;
            }
        }
        tmp.clear();
        for(int j = 0; j < n; j++){
            if(k + j < n)
                tmp.push_back(data[k + j][j]);
        }
        even_odd(tmp);
        l = 0;
        for(int j = 0; j < n; j++){
            if(k + j < n){
                data[k + j][j] = tmp[l];
                l++;
            }
        }
        tmp.clear();
    }
}
int main(){
    int num;
    cout << "*** Выберите номер задания (№) ***\n(1) - Блочная сортировка строк по убыванию\n\
(2) - Сортировка слиянием строк по возрастанию, нокаждую третью по убыванию\n\
(3) - Сортировка чёт-нечёт диагоналей, параллельные главной по возрастанию" << endl;
    cout << "Введите №: "; cin >> num;
    int n = r();
    vector<vector<int> > data(n);
    fill(data, n);
    switch(num){
        case 1:
            block(data, n);
        break;
            
        case 2:
            for(int x = 0; x < n; x++){
                bool flag = false;
                if(x && !((x + 1)%3)) flag = true;
                sep_(data[x], 0, data[x].size() - 1, flag);
            }
        break;

        case 3:
            main_diagonal(data, n);
        break;
    }
    out_file(data);
    cout << "Отсортированный массив сохранён в файл output.txt" << endl;
    return 0;
}