/*
 * 1. This Program is Developed Solely by Myself:Yes
 * 2. Student ID: 106010006
 * 3. OJ ID: meg871017
 * 4. OJ SID: 2233541
 * 5. OJ Score: 10
 */ 

#include <iostream>
using namespace std; 

void dijkstra(int sta,int map[100][100],int len[100],int parent[100],int take[100],int num)
{
    for (int i=0; i<num; i++) {
        take[i] = 0;
        len[i] = 9999999;
    }
    len[sta] = 0;
    parent[sta] = sta;
    for (int k=0; k<num; k++)
    {
        int x = -1;
        int y = -1;
        int min = 9999999;
        for (int i=0; i<num; i++)
            if (!take[i] && len[i] < min)
            {
                x = i;  
                min = len[i];
            }
            //cout << "x: "<<x<<"min: "<<min;
        if (x == -1){
            break;
        }
        take[x] = 1;
        for (y=0; y<num; y++){
            if (!take[y] && len[x] + map[x][y] < len[y])
            {
                len[y] = len[x] + map[x][y];
                parent[y] = x;
                //cout << "len: "<<len;
            }
        }
    }
}

void find(int x, int parent[100],int &k,int &sum,int map[100][100])  
{
    if (x != parent[x]){ 
        sum=sum+ map[parent[x]][x];
        find(parent[x],parent,k,sum,map);
        //cout <<w[parent[x]][x]<<endl;
    }  
    int i=x+65;
    if(k==0){
        cout <<sum<<endl;  
        cout << char(i); 
    }
    else{
        cout << " "<<char(i);
    }
    k=1;
    
  
}


int main(){
    int a, b, c;
    char x,y;
    int k=0;
    int num,num_path;
    char start;
    char end;
    int sum;
    int map[100][100];   
    int len[100];       
    int parent[100]; 
    int take[100]; 
    cin >>num>>num_path;
    cin >>start;
    cin >>end;

    
    for (int i=0; i<num; ++i){
        for (int j=0; j<num; ++j){
            map[i][j] = 9999999;  
        }
    }
 
   
    for(int i=0; i<num_path;i++){
        cin >> x >> y >> c;
        a=int(x);
        b=int(y);
        a=a-65;
        b=b-65;
        map[a][b] = c;       
        //cout <<a<<" "<<b<<" "<<c<<endl;
    }

    int s=int(start)-65;
    dijkstra(s,map,len,parent,take,num);
    int e=int(end)-65;
    find(e,parent,k,sum,map);
   
    return 0;
}