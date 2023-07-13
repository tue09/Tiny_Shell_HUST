#include <iostream>
using namespace std;
int main(){
    string name;
    long long i = 0;
    int j = 0;
    while(true){
        i = i + 0.0001;
        int k = i;
        if (k % 10000000 == 0)
        {
            j = j + 1;
            cout<<j<<": "<<"Hello "<<endl;
        }
    }
    

    return 0;
}