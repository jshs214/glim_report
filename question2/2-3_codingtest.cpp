#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int americano = 4500;
const int cafelatte = 5000;

bool check(string str, string findStr){
    return (str.find(findStr) !=string::npos) ? true : false;
}

int solution(vector<string> order) {
    int answer = 0;
    
    int ameCnt = 0, cafeCnt = 0;
    for(string str: order){
        if(check(str, "americano") || check(str, "anything"))
            ameCnt ++;
        else if(check(str, "cafelatte"))
            cafeCnt ++;
    }
    
    answer = (americano * ameCnt) + (cafelatte * cafeCnt);
    
    
    return answer;
}