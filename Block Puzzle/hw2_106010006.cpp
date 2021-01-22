/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 106010006
 * 3. OJ ID: meg871017
 * 4. OJ SID: 2159252
 * 5. OJ Score: 10
 */ 

#include <iostream>

using namespace std; 

int final;
void puzzle(int A[10][2],int B[10][10][10],int B_map[10][10][10],int W_map,int H_map,int x,int y,int num,int N,int te){
    int che=0;
    int xx=x;
    int yy=y;
    for(int y=0;y<H_map;y++){
        for(int x=0;x<W_map;x++){
            che=0;
            yy=y;
            for (int j=0; j<A[num][1];j++){
                xx=x;
                for(int k=0; k<A[num][0]; k++){
                    //cout <<"B:" <<B[1][j][k]<<"xx: "<<xx<<"yy: "<<yy<<"map: " << B_map[0][yy][xx]<<endl;
                    if((B[num][j][k]==1)&&(B_map[te][yy][xx]==1)){
                        che=1;
                    }
                    xx=xx+1;
                }
                yy=yy+1; 
            }
            //cout <<"che: "<<che<<endl;
            if(che==0){
                //cout <<"num: "<< num<<endl;
                if(num==N-1){
                    final=1;
                    //cout <<"map: "<<te<<"final:"<<final<<endl;
                    return;
                }
                int nx=x;
                int ny=y;
                int c_map[10][10][10];

                for(int ii=0; ii<10;ii++){
                    for(int jj=0; jj<10;jj++){
                        for(int kk=0;kk<10;kk++){
                            c_map[ii][jj][kk]=B_map[ii][jj][kk];
                        }
                    }
                }
                /*
                cout << "original_c_map: "<<endl;
                for(int v=0; v<10; v++){
                    for(int z=0; z<10; z++){
                        cout << c_map[te][v][z];
                    }
                    cout <<endl;
                }
                cout <<endl;
                */
                for (int m=0; m<A[num][1];m++){
                    nx=x;
                    for(int n=0; n<A[num][0]; n++){
                        c_map[te][ny][nx]=B[num][m][n]+B_map[te][ny][nx] ;
                        //cout <<"nx: "<<nx<<"ny: "<<ny<<endl;
                        nx=nx+1;
                    }
                    ny=ny+1;
                }
                ny=y;
                /*
                cout << "new_c_map: "<<endl;
                for(int v=0; v<10; v++){
                    for(int z=0; z<10; z++){
                        cout << c_map[te][v][z];
                    }
                    cout <<endl;
                }
                */
                puzzle(A,B,c_map,W_map,H_map,0,0,num+1,N,te);
                if(final==1){
                    return;
                }
            }
            //cout <<endl;
        }
       
    }

    if(num==N-1){
        return;
    }



}


int main() { 
    int N,W,H;
    int A[10][2];
    int B[10][10][10];
    int A_map[10][2];
    int B_map[10][10][10];
    char a,a_map;
    int N_map,W_map,H_map;
    int x,y,num=0;
    int aa,aa_map;

    cin >> N;

    for(int i=0; i<10;i++){
        for(int j=0; j<10;j++){
            for(int k=0;k<10;k++){
                B_map[i][j][k]=1;
            }
        }
    }


    for (int i=0; i<N; i++ ){
        cin >> W >> H;
        A[i][0]=W;
        A[i][1]=H;
        for (int j=0; j<H;j++){
            for(int k=0; k<W; k++){
                cin >> a;
                if(a==79){
                    aa=1;
                }
                else{
                    aa=0;
                }
                B[i][j][k]=aa;
                
            }
        }
        
    }

    cin >> N_map;
    
    for (int i=0; i<N_map; i++ ){
        cin >> W_map >> H_map;
        A_map[i][0]=W_map;
        A_map[i][1]=H_map;
        for (int j=0; j<H_map;j++){
            for(int k=0; k<W_map; k++){
                cin >> a_map;
                if(a_map==79){
                    aa_map=1;
                }
                else{
                    aa_map=0;
                }
                B_map[i][j][k]=aa_map;
                
            }
        }
        
    }


   

  
    for(int te=0; te<N_map; te++){
        final=0;
        puzzle(A,B,B_map,A_map[te][0],A_map[te][1],0,0,num,N,te);
        if(final==1){
            cout<< "Yes"<<endl;
        }
        else{
            cout <<"No"<<endl;
        }
    }
    
    /*
    for (int i=0; i<N; i++){
        cout << "i:"<<i << "W: "<< A[i][0] <<"H: "<< A[i][1]<<endl;
        for(int j=0; j<A[i][1]; j++){
            for(int k=0; k<A[i][0]; k++){
                cout << B[i][j][k];
            }
            cout <<endl;
        }


    }
   
    for (int i=0; i<N_map; i++){
        cout << "i_map:"<<i << "W_map: "<< A_map[i][0] <<"H_map: "<< A_map[i][1]<<endl;
        for(int j=0; j<A_map[i][1]; j++){
            for(int k=0; k<A_map[i][0]; k++){
                cout << B_map[i][j][k];
            }
            cout <<endl;
        }


    }
    */
    return 0; 
}