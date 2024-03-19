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

        string str1 = three.substr(6, 4);
        int yy = atoi(str1.c_str());
        elem.birth = yy;

        elem.experience = atoi(four.c_str());
        elem.salary = atoi(five.c_str());
        staff.push_back(elem);
    }
}
bool check(base &a, base &b) {
    return a.experience < b.experience;
}


int main(){
    ofstream out("output1.txt");
    vector <base> staff;
    fill(staff);
    
    auto max_it = max_element(staff.begin(), staff.end(), check);
    auto min_it = min_element(staff.begin(), staff.end(), check);
    int max_ = (*max_it).experience;
    int min_ = (*min_it).experience;

    int p = 5;
    float m = (max_ - min_) / p;
    vector< vector<base> > v(p);
    for (int i = 0; i < staff.size(); i++){
        int k = round((staff[i].experience - min_) / m);
        if (k == p)
            v[4].push_back(staff[i]);
        else
            v[k].push_back(staff[i]);
    }
    for (int k = 0; k < p; k++){
        for (int i = 1; i < v[k].size(); i++){
            int j = i;
            while (j > 0 && v[k][j].experience < v[k][j - 1].experience){
                swap(v[k][j], v[k][j - 1]);
                j--;
            }
        }
    }
    staff.clear();
    for (int i = 0; i < p; i++){
        for (int j = 0; j < v[i].size(); j++)
            staff.push_back(v[i][j]);
    }
    out << setw(10) << "|surname|" << setw(15) << "|post|" << setw(15) << "|birthday|" << setw(13) << "|experience|" << setw(10) << "|salary|" << endl;
    for (int i = 0; i < staff.size(); i++)
        out << setw(10) << staff[i].surname << setw(15) << staff[i].post << setw(15) << staff[i].date << setw(7) << staff[i].experience << setw(16) << staff[i].salary << endl;

    return 0;

}
