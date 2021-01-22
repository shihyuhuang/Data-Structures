/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 106010006
 * 3. OJ ID: meg871017
 * 4. OJ SID: 2207928
 * 5. OJ Score: 10
 */ 


#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


string Sick= "Sick";
string Healthy= "Healthy";
string Masked= "Masked";
string ICU= "ICU";
string Die= "Die";


class Term{
    public:
    Term(string Name="aaa",int row=0,int col=0,string condition=Healthy,int recovery_time=0,int come_day=0,
    int death_time=7,int more_sick=0,int sick_neighbor=0);
    string Name;
    int row;
    int col;
    string condition;
    int come_day;
    int recovery_time;
    int death_time;
    int get_sick_by[4]; //4 capacity of sick neighbor list
    int more_sick; //new sick neighbor
    int sick_neighbor; //total sick nsighbor
};


Term::Term(string Name,int row,int col,string condition,int recovery_time,int come_day,
    int death_time,int more_sick,int sick_neighbor)
{
    this->recovery_time = recovery_time;
    this->row = row;
    this->col = col;
    this->condition = condition;
    this->Name = Name;
    this->come_day = come_day;
    this->death_time = death_time;
    this->more_sick = more_sick;
    this->sick_neighbor = sick_neighbor;
}

//check neighbor
void ch_sick_neighbor(Term termArray[2000],int **Mat,int Now_people,int r,int c){
    termArray[Now_people].sick_neighbor=0;
    int x=termArray[Now_people].row;
    int y=termArray[Now_people].col;
    if(x>0){
        int up=Mat[x-1][y]; //Now_people's up person
        if((up!=-1)&&(termArray[up].condition==Sick)) {
            termArray[Now_people].sick_neighbor=termArray[Now_people].sick_neighbor+1;//how many sick neighbor
            //how many new sick neighbor
            int r=0;
            for(int l=0 ;l<4;l++){
                if(termArray[Now_people].get_sick_by[l]==up){
                    r=1; //if this sick neighbor is in the list, not a new sick neighbor
                }
            }
            if(r==0){ //is new sick neighbor
                for(int l=0 ;l<4;l++){
                  if(termArray[Now_people].get_sick_by[l]==-1){ //insert to a empty position of the list
                    termArray[Now_people].get_sick_by[l]=up;
                    break;
                   }
                }
                termArray[Now_people].more_sick=termArray[Now_people].more_sick+1; //new sick person number plus 1
            }
        }
    }
    if(x<r-1){
        int down=Mat[x+1][y];
        if((down!=-1)&&(termArray[down].condition==Sick)){
            termArray[Now_people].sick_neighbor=termArray[Now_people].sick_neighbor+1;
            int r=0;
            for(int l=0 ;l<4;l++){
                if(termArray[Now_people].get_sick_by[l]==down){
                    r=1;
                }
            }
            if(r==0){
                for(int l=0 ;l<4;l++){
                  if(termArray[Now_people].get_sick_by[l]==-1){
                    termArray[Now_people].get_sick_by[l]=down;
                    break;
                   }
                }
                termArray[Now_people].more_sick=termArray[Now_people].more_sick+1;
            }

        }
    }
    if(y<c-1){
        int right=Mat[x][y+1];
        if((right!=-1)&&(termArray[right].condition==Sick)){
            termArray[Now_people].sick_neighbor=termArray[Now_people].sick_neighbor+1;
            int r=0;
            for(int l=0 ;l<4;l++){
                if(termArray[Now_people].get_sick_by[l]==right){
                    r=1;
                }
            }
            if(r==0){
                for(int l=0 ;l<4;l++){
                  if(termArray[Now_people].get_sick_by[l]==-1){
                    termArray[Now_people].get_sick_by[l]=right;
                    break;
                   }
                }
                termArray[Now_people].more_sick=termArray[Now_people].more_sick+1;
            }

        }
    }
    if(y>0){
        int left=Mat[x][y-1];
        if((left!=-1)&&(termArray[left].condition==Sick)){
            termArray[Now_people].sick_neighbor=termArray[Now_people].sick_neighbor+1;
            int r=0;
            for(int l=0 ;l<4;l++){
                if(termArray[Now_people].get_sick_by[l]==left){
                    r=1;
                }
            }
            if(r==0){
                for(int l=0 ;l<4;l++){
                  if(termArray[Now_people].get_sick_by[l]==-1){
                    termArray[Now_people].get_sick_by[l]=left;
                    break;
                   }
                }
                termArray[Now_people].more_sick=termArray[Now_people].more_sick+1;
            }

        }

    }
}
// change state
void ch_state(Term termArray[2000],int Now_people,int Now_day,int people_num,int &ICU_capacity,int change[1000],int *change_num){
    if(termArray[Now_people].condition==Healthy){
        if(termArray[Now_people].more_sick>0){ //if healthy anf have sick neighbor
            termArray[Now_people].condition=Sick;
            termArray[Now_people].recovery_time=14+7*termArray[Now_people].more_sick;
            termArray[Now_people].more_sick=0;
        }
        if((termArray[Now_people].recovery_time>28)&&(ICU_capacity>0)){ //after change state whether go to ICU
                termArray[Now_people].condition=ICU;
                ICU_capacity=ICU_capacity-1;
                change[*change_num]=Now_people; //inster him to today's change list
                *change_num=*change_num+1;
        }

    }
    else if(termArray[Now_people].condition==Sick){
            termArray[Now_people].recovery_time=termArray[Now_people].recovery_time-1; //every day minus recovery
            if(termArray[Now_people].recovery_time==0){ //check whether become healthy
                termArray[Now_people].condition=Healthy;
                termArray[Now_people].death_time =7;
                termArray[Now_people].more_sick=0;
                termArray[Now_people].sick_neighbor=0;
                change[*change_num]=Now_people; //inster him to today's change list
                *change_num=*change_num+1;
            }
            else{
                termArray[Now_people].recovery_time=termArray[Now_people].recovery_time+7*termArray[Now_people].more_sick;
                termArray[Now_people].more_sick=0;
            }
            if((termArray[Now_people].recovery_time>28)&&(ICU_capacity>0)){
                termArray[Now_people].condition=ICU;
                ICU_capacity=ICU_capacity-1;
                change[*change_num]=Now_people; //inster him to today's change list
                *change_num=*change_num+1;
            }
            if(termArray[Now_people].sick_neighbor==4){
                termArray[Now_people].death_time=termArray[Now_people].death_time-1;
                if(termArray[Now_people].death_time==0){
                    termArray[Now_people].condition=Die;
                    change[*change_num]=Now_people; //inster him to today's change list
                    *change_num=*change_num+1;
                }
            }

    }
}


void dele_nei_list(Term termArray[2000],int people_num,int Now_people){
    for(int i=0;i<people_num;i++){
        for(int j=0;j<4;j++){
            if(termArray[i].get_sick_by[j]==Now_people){
                termArray[i].get_sick_by[j]=-1;
                }
        }
    }

}




int main() {
    int ICU_capacity,r,c,output_time;
    int Now_day;
    int Now_people;
    int people_num;
    float survive_rate;
    float survive_num=0;
    int **Mat;
    Term termArray[2000];
    int change[1000]; //that day people who go to ICU/DIE or become healthy
    int change_num; //that day the number of people who go to ICU/DIE or become healthy
    cin >> r >> c >> ICU_capacity >> output_time;
    cin >> people_num;


    Mat = new int*[r];
    for(int i= 0; i <r; i++){
    Mat[i] = new int[c];
    }

    //let the map position with no person there be -1
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            Mat[i][j]=-1;
        }
    }

    for(int i=0; i<people_num ; i++){
    cin >> termArray[i].come_day >> termArray[i].row >> termArray[i].col >> termArray[i].Name >> termArray[i].condition;
    //let the people's sick neighbor list if no person in list be -1
    for(int l=0;l<4;l++){
        termArray[i].get_sick_by[l]=-1;
    }
    //initialize the recovery of sick people
    if(termArray[i].condition==Sick){
        termArray[i].recovery_time=14;
    }
    }

    for(Now_day=0; Now_day<output_time;Now_day++){
        //find sick neighbor of all people
        for(Now_people=0; Now_people<people_num ; Now_people++){
            if(termArray[Now_people].come_day<Now_day){
                ch_sick_neighbor(termArray,Mat,Now_people,r,c);
            }
        }
        //change the state of all people
        for(int Now_people=0; Now_people<people_num ; Now_people++){
            if(termArray[Now_people].come_day<Now_day){
                ch_state(termArray,Now_people,Now_day,people_num,ICU_capacity,change,&change_num);
            }
        }

        //if somebody go to ICU/DIE or become healthy, delete him from other's sick neighbor list
        for(int i=0; i<change_num; i++){
            Now_people=change[change_num];
            dele_nei_list(termArray,people_num,Now_people);
        }


        //insert new people
        for(int i=0;i<people_num;i++){
            if(termArray[i].come_day==Now_day){
                Mat[termArray[i].row][termArray[i].col]=i;
            }
        }
        /*
        cout <<"----------------------------"<<endl;
        cout<<"Now_day: "<<Now_day<<endl;
        for(Now_people=0; Now_people<people_num ; Now_people++){
            if(termArray[Now_people].come_day<Now_day){
                cout << " come_day: " <<termArray[Now_people].come_day <<" row: "<< termArray[Now_people].row <<" col: "<< termArray[Now_people].col
                <<" Name: "<<termArray[Now_people].Name <<" condition: "<<termArray[Now_people].condition<<" recovery_time: "<<termArray[Now_people].recovery_time
                <<" death_time: "<<termArray[Now_people].death_time<<" get_sick_by: "<<termArray[Now_people].get_sick_by[0]<<"/"<<termArray[Now_people].get_sick_by[1]
                <<"/"<<termArray[Now_people].get_sick_by[2]<<"/"<<termArray[Now_people].get_sick_by[3]
                <<" sick_neighbor: "<<termArray[Now_people].sick_neighbor<<endl;
                }
        }
        */



    }

    for(int i=0; i<people_num; i++){
        if(termArray[i].condition!=Die){
            survive_num=survive_num+1;
            //cout <<termArray[i].Name<<" ";
        }
    }

    survive_rate = (survive_num/people_num)*100;
    cout << fixed  <<  setprecision(2) << survive_rate<<"%"<<  endl;

    int k,aa=0;

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(Mat[i][j]!=-1){
                k=Mat[i][j];
                if((termArray[k].condition!=Die)&&(termArray[k].condition!=ICU)){
                    if(aa==0){
                    cout <<termArray[k].Name;
                    }
                    else{
                    cout <<" "<<termArray[k].Name;
                    }
                    aa=1;
                }
            }
        }
    }



    for(int i= 0; i <r; i++){
        delete Mat[i];
    }
    delete[] Mat;

    return 0;
}
