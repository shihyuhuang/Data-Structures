/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 106010006
 * 3. OJ ID: meg871017
 * 4. OJ SID: 2135554
 * 5. OJ Score: 10
 */ 
#include <iostream>

using namespace std; 

int to;

void sum(int L[1000][3],int j, int v, int w,int N,int K){

    for(int i =j; i< N; i++){

        if(w <= K-(L[i][2])){
            if(v >= to - (L[i][1])) 
            to = v + L[i][1];
            sum(L,i+1,v + L[i][1],w + L[i][2],N,K);
            
        }
    }
}

int main() { 
    int N,K;
    cin >> N >> K;
    int j=0;
    int L[1000][3] = {0};

    for (int i=0; i<N; i++){
        cin >> L[i][1] >> L[i][2];
        //cout << L[i][1] <<" "<< L[i][2];
        }

    


    sum(L,j,j,j,N,K);

    cout  << to ;

    return 0; 

}

