#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool check(string s1, string s2){
    return (s1.compare(s2) == 0) ? true: false;
}

int solution(string my_string, string is_prefix) {
    // exception
    if(my_string.size() < is_prefix.size()) 
        return 0;
    
    int answer = 0;
    string s = "";
    
    for(char c :  my_string){
        s += c;
        
        if(s.size() == is_prefix.size()){
            if(check(s, is_prefix) ) {
                answer = 1;
                break;
            }
            else {
                answer = 0;
                break;
            }
        }
        
    }
    
    
    return answer;
}