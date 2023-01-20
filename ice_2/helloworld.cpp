#include <iostream>
#include <string>
#include <cmath>
#include <vector>


//learncpp.com has great examples

using namespace std;

void ModifiedHello (string arg);
string GetWord();
float GetDistance(int *a, int *b, int length);
//float GetDistance(vector int *b, int length);

int main()
{
    ModifiedHello(GetWord());
    int a1[] {1,2,3};
    int b1[] {2,2,2};
    cout << GetDistance(a1,b1,3);
    vector<int> a2 {1,2,3};
    vector<int> b2 {3,3,3};
}

void ModifiedHello (string arg){
    cout << "Hello " << arg << endl;
}

string GetWord () {
    string name {};
    cout << "Enter your name: ";
    cin >> name;
    cout << endl;
    return name;
}

float GetDistance(int *a, int *b, int length){
    float sum = 0;
    for (int i = 0; i < length; i++){
        sum += pow( (a[i] - b[i]) , 2);
    }
    return sqrt(sum);
}