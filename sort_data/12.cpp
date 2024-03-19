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

int main(){
    ofstream out("output3.txt");
    vector <base> staff;
    fill(staff);
    
    for (int i = 0; i < staff.size(); i++){
        if (!(i & 1)){
            for (int j = 2; j < staff.size(); j+=2){
                if (staff[j-1].surname > staff[j].surname || (staff[j-1].surname == staff[j].surname && staff[j-1].experience > staff[j].experience) || (staff[j-1].surname == staff[j].surname && staff[j-1].experience == staff[j].experience && staff[j - 1].salary > staff[j].salary)){
                    swap(staff[j - 1], staff[j]);
                }
            }
        }
        else{
            for (int j = 1; j < staff.size(); j+=2){
                if (staff[j-1].surname > staff[j].surname || (staff[j-1].surname == staff[j].surname && staff[j-1].experience > staff[j].experience) || (staff[j-1].surname == staff[j].surname && staff[j-1].experience == staff[j].experience && staff[j - 1].salary > staff[j].salary)){
                    swap(staff[j - 1], staff[j]);
                }
            }
        }
        }
    out << setw(10) << "|surname|" << setw(15) << "|post|" << setw(15) << "|birthday|" << setw(13) << "|experience|" << setw(10) << "|salary|" << endl;
    for (int i = 0; i < staff.size(); i++)
        out << setw(10) << staff[i].surname << setw(15) << staff[i].post << setw(15) << staff[i].date << setw(7) << staff[i].experience << setw(16) << staff[i].salary << endl;
     return 0;
}