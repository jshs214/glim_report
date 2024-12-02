#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {    
    string s1, s2;
    s1 = to_string(a) + to_string(b);
    s2 = to_string(b) + to_string(a);
    
    int num1, num2;
    num1 =stoi(s1); num2 = stoi(s2);
    
    if(num1 >= num2) return num1;
    else return num2;
    
}