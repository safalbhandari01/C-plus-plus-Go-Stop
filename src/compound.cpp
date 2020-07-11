
#include <string>
#include<cstdio>
#include<algorithm>
#include<iostream>

using namespace std;

int main(){

    
    double rate = 0.03;
    double compoundInterest =1000;
    //calculating compound interest
    for(int i=0; i<365;i++){
        compoundInterest += 0.03 * compoundInterest;
        cout<<"End of Day "<<i<<": "<<compoundInterest<<endl;
    }

    //print
    return 0;
    
}//end of main() function


