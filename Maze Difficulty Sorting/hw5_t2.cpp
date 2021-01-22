/*
 * 1. This Program is Developed Solely by Myself:Yes
 * 2. Student ID: 106010006
 * 3. OJ ID: meg871017
 * 4. OJ SID: 2251949
 * 5. OJ Score: 10
 */ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

void BubSort(int A[][6], int n,int m) {
    int i,j,k,t=1;
    int Temp[6];
    int sp;
    for (i=n-1; i>0; i--){
        sp=1;
        for (j =0; j <i; j++){
            //cout <<"    "<<A[j][m]<<" "<<A[j+1][m]; 
            if (A[j][m] > A[j+1][m]){ 
                //cout <<"----"; 
                copy(A[j], A[j]+6, Temp);
                copy(A[j+1], A[j+1]+6, A[j]);
                copy(Temp, Temp+6, A[j+1]);
                sp=0;
            }
        }    
        if (sp==1) break;          
       }
}



void dijkstra(int sta,int **map,int len[],int parent[],int take[],int num)
{
    for (int i=0; i<num; i++) {
        take[i] = 0;
        len[i] = 9999999;
        parent[i]=-1;
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

void find(int x, int parent[],int &k,int **map,int core_path[])  
{
    if (x != parent[x]){ 
        find(parent[x],parent,k,map,core_path);
    }  
    
    //cout << " "<<x;
    core_path[k]=x;
    
    k=k+1;
    
  
}

void find2(int x, int parent[],int &k,int **map,int **incore_path,int i)  
{
    if (x != parent[x]){ 
        find2(parent[x],parent,k,map,incore_path,i);
    }  
    
    //cout << " "<<x;
    incore_path[i][k]=x;
    
    k=k+1;
    
  
}

int main(){
    int map_num=0;
    cin >> map_num;
    int A[map_num][6]; //0:編號, 1:overall, 2:N1, 3:N2, 4:L1, 5:L2
    for(int i=0; i<map_num;i++){
        for(int j=0;j<6;j++){
        A[i][j]=0;
        }
    }

    for(int ii=0;ii<map_num;ii++){
        char a='P';
        int W_num,H_num=0;
        int dot_num=0;
        vector<int> w;
        vector<int> h;
        cin >>A[ii][0];
        cin >>W_num>>H_num;
        int maze[H_num][W_num];

        for (int i=0; i<H_num; ++i){
            for (int j=0; j<W_num; ++j){
                maze[i][j] = -1;  
            }
        }
        for(int j=0; j<H_num; j++){
            for(int k=0; k<W_num; k++){
                cin >>a;
                if(a!='N'){
                    h.push_back(j);
                    w.push_back(k);
                    maze[j][k]=dot_num;
                    dot_num=dot_num+1;
                }
                else{
                    maze[j][k]=-1;
                }

            }
        }
        if(dot_num==1){
            A[ii][1]=0;
            A[ii][2]=0;
            A[ii][3]=0;
            A[ii][4]=0;
            A[ii][5]=0;
        }else{
        /*
        for(int i=0; i<dot_num;i++){
            cout <<i<<" "<<h[i]<<" "<<w[i]<<endl;
        }
      
        for(int j=0; j<H_num; j++){
            for(int k=0; k<W_num; k++){
                cout << maze[j][k]<<" ";
            }
            cout <<endl;
        }
        */
        
        int **road_map;
        road_map = new int*[dot_num];
        for(int i= 0; i <dot_num; i++){
            road_map[i] = new int[dot_num];
        }  
        int len[dot_num];       
        int parent[dot_num]; 
        int take[dot_num]; 

        for (int i=0; i<dot_num; ++i){
            for (int j=0; j<dot_num; ++j){
                road_map[i][j] = 9999999;  
            }
        }

        road_map[0][1] = 1; //start point
        road_map[1][0] = 1; 
        road_map[dot_num-1][dot_num-2] = 1; //end point
        

        //find end
        vector<int> dead_end;

        for(int i=0;i<dot_num;i++){
            int wall=4;
            if((w[i]!=0)&&(w[i]!=W_num-1)){
                if(maze[h[i]-1][w[i]]!=-1){
                    wall=wall-1;
                    road_map[i][maze[h[i]-1][w[i]]] = 1; 
                }
                if(maze[h[i]+1][w[i]]!=-1){
                    wall=wall-1;
                    road_map[i][maze[h[i]+1][w[i]]] = 1; 
                }
                if(maze[h[i]][w[i]+1]!=-1){
                    wall=wall-1;
                    road_map[i][maze[h[i]][w[i]+1]] = 1; 
                }
                if(maze[h[i]][w[i]-1]!=-1){
                    wall=wall-1;
                    road_map[i][maze[h[i]][w[i]-1]] = 1; 
                }
            }
            if(wall==3){  //found end
                //cout<<maze[h[i]][w[i]]<<endl;
                dead_end.push_back(maze[h[i]][w[i]]);
            }   
        }

        int dead_end_num=dead_end.size();
        A[ii][3]=dead_end_num;
        
        //cout <<"N2: "<<A[ii][3]<<endl;
        int start=0;
        int end=dot_num-1;

        dijkstra(start,road_map,len,parent,take,dot_num);

        
        A[ii][4]=len[end]; //L1 
        
        
        //cout <<"L1: "<<A[ii][4]<<endl;
        int kk=0;
        int core_path[len[end]+1];
        find(end,parent,kk,road_map,core_path);
        
        if(dead_end_num==0){
            A[ii][1]=0;
            A[ii][2]=0;
            A[ii][3]=0;
            A[ii][4]=len[end];
            A[ii][5]=0;
        }else{

        /*
        for(int i=0; i<len[end]+1;i++){
            cout <<core_path[i]<<" ";
        }
        cout <<endl;
        */
        int max=-1;
        
        for(int i=0; i<dead_end_num; i++){
            if(len[dead_end[i]]+1>max){
                max=len[dead_end[i]]+1;
            }
        }
        //cout <<"max: "<<max<<endl;
        
        int **incore_path;
        incore_path = new int*[dead_end_num];
        for(int i= 0; i <dead_end_num; i++){
            incore_path[i] = new int[max];
        }


        
        int fork[dead_end_num];
        for(int i=0; i<dead_end_num; i++){
            fork[i]=-1;
            kk=0;
            //cout <<"len: "<<len[dead_end[i]]+1<<endl;
            find2(dead_end[i],parent,kk,road_map,incore_path,i);
        }
        
        for(int i= 0; i <dot_num; i++){
            delete road_map[i];
        }
        delete[] road_map;
        /*
        for(int i=0; i<dead_end_num; i++){
            for(int j=0; j<len[dead_end[i]]+1;j++){
                cout << incore_path[i][j]<<" ";
            }
            cout <<endl;
        }
        */

        
        int len_inco[dead_end_num];
        for(int i=0; i<dead_end_num; i++){
            int check=0;
            int min=0;
            if(len[dead_end[i]]<len[end]){
                min=len[dead_end[i]];
            }else{
                min=len[end];
            }
            for(int j=0; j<min+1;j++){
                //cout << incore_path[i][j]<<" ";
                if(incore_path[i][j]==core_path[j]){
                    fork[i]=incore_path[i][j];
                    //cout <<"fork: "<<fork[i]<<endl;
                }
                else{
                    len_inco[i]=len[dead_end[i]]-len[fork[i]];
                    for(int n=0;n<i;n++){
                        if(fork[n]==parent[incore_path[i][j]]){
                            if(incore_path[n][j]==incore_path[i][j]){
                                //cout <<"i "<<i<<"n: "<<n<<incore_path[n][j]<<" "<<incore_path[i][j];
                                check=1;
                            }
                        }
                    }
                }

            }
            //cout <<endl;
            if (check==0){
                A[ii][2]=A[ii][2]+1; //N1
            }
        }
        for(int i= 0; i <dead_end_num; i++){
            delete incore_path[i];
        }
        delete[] incore_path;
       /*
        cout <<"N1: "<<A[ii][2];
        
        for(int n=0;n<dead_end_num;n++){
            cout << len_inco[n]<<" ";
        }
        cout <<endl;
        */
        sort(len_inco,len_inco+dead_end_num);
        /*
        for(int n=0;n<dead_end_num;n++){
            cout << len_inco[n]<<" ";
        }
        */
        int hal;
        if(dead_end_num==0){
            hal=0;
        }else if(dead_end_num==1){
            hal=1;
        }else{
            hal=(dead_end_num+1)/2;
        }

        
        //cout <<"half: "<<hal<<endl;
        if(dead_end_num==0){
            A[ii][5]=0;
        }
        else if(dead_end_num%2==0){
            A[ii][5]=(len_inco[hal-1]+len_inco[hal])/2;
        }
        else if(dead_end_num%2==1){
            A[ii][5]=len_inco[hal-1];
        }


        //cout <<"L2: "<<A[ii][5]<<endl;  //L2
        A[ii][1]=((A[ii][2]+A[ii][3])*(A[ii][4]+A[ii][5])); //overall
        }
        }
    
    
    }

    if(map_num!=1){
        for(int m=5; m>0; m--){
            BubSort(A,map_num,m);
        }
    }

    for(int i=0; i<map_num;i++){
            cout << A[i][0]<<endl;
            cout <<A[i][1]<<" "<<A[i][2]<<" "<<A[i][3]<<" "<<A[i][4]<<" "<<A[i][5];
            cout << endl;
    }   
    
    return 0;
};