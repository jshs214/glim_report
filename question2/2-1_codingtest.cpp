#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int service = 10;
const int food = 12000;
const int drink = 2000;


int solution(int n, int k) {
    int answer = 0;

    k = k - (n/ service);
    
    answer = (n * food) + (k * drink);
    
    
    return answer;
}