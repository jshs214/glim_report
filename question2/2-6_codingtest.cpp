#include <iostream>
#include <string>
#include <stack>

using namespace std;
stack<int> stk;

int solution(string s) {
    int answer = 0;

    
    size_t parsePos = 0;
    string token = "";            
    int num = 0;
    
    while( (parsePos = s.find(" ") ) != string::npos){
        token = s.substr(0, parsePos);
        s = s.substr(parsePos+1, s.size() - parsePos);

        if(token == "Z"){
            if(stk.size()) 
                stk.pop();
        }else {
            num = stoi(token);
            stk.push(num);  // 스택에 푸시
        }
    }
    
    //마지막 문자열처리
    if(s == "Z") {
        if(stk.size())
            stk.pop();
    } else {
        num = stoi(s);
        stk.push(num);
    }
    
    while(stk.size()){
        answer += stk.top();
        stk.pop();
    }
        
    
    
    return answer;
}