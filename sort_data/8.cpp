#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct base{ //структура даты
    string surname, post, date;
    int birth, experience, salary;
};

void fill(vector <base> &staff){ //заполнение вектора(по индексу)
    ifstream in("input.txt");
    while(in.peek() != EOF){
        base elem;
        string one, two, three, four, five;
        in >> one >> two >> three >> four >> five;
        elem.surname = one;
        elem.post = two;
        elem.date = three;

        string str1 = three.substr(6, 4);
        int yy = atoi(str1.c_str());
        elem.birth = yy;

        elem.experience = atoi(four.c_str());
        elem.salary = atoi(five.c_str());
        staff.push_back(elem);
    }
}

void sort_(vector <base> &staff, int l, int r, int m){ 
    if (l >= r || m < l || m > r)
        return;
    if (r - l == 1 && (staff[l].salary > staff[r].salary || (staff[l].salary == staff[r].salary && staff[l].birth > staff[r].birth))){
        swap(staff[l], staff[r]);
        return;
    }
    vector<base> buf (r - l + 1);
    int cur = 0;
    int i = l, j = m + 1;
    while(r - l + 1 != cur){
        if (i > m){
            for(int y = j; y <= r; y++)
                buf[cur++] = staff[y];
        }
        else if (j > r){
            for(int y = i; y <= m; y++)
                buf[cur++] = staff[y];
        }
        else if (staff[i].salary > staff[j].salary || (staff[i].salary == staff[j].salary && staff[i].birth > staff[j].birth)){
            buf[cur++] = staff[j++];
        }
        else{
            buf[cur++] = staff[i++];
        }
    }
    for(int k = 0; k < r - l + 1; k++){
        staff[l + k] = buf[k];
    }
}


void alg_(vector <base> &staff, int l, int r){
    if (l >= r){
        return;
    }
    int m = (l + r) / 2;
    alg_(staff, l, m);
    alg_(staff, m + 1, r);
    sort_(staff, l, r, m);
}
    

int main(){
    ofstream out("output2.txt");
    vector <base> staff;
    fill(staff);

    alg_(staff, 0, staff.size() - 1);

    out << setw(10) << "|surname|" << setw(15) << "|post|" << setw(15) << "|birthday|" << setw(13) << "|experience|" << setw(10) << "|salary|" << endl;
    for (int i = 0; i < staff.size(); i++)
        out << setw(10) << staff[i].surname << setw(15) << staff[i].post << setw(15) << staff[i].date << setw(7) << staff[i].experience << setw(16) << staff[i].salary << endl;
    
    return 0;
}
