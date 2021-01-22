/*
 * 1. This Program is Developed Solely by Myself:Yes
 * 2. Student ID: 106010006
 * 3. OJ ID: meg871017
 * 4. OJ SID: 2226826
 * 5. OJ Score: 10
 */ 

#include <queue>
#include <iostream>
#include <string>
using namespace std; 

class Node 
{ 
    public:
    char str; 
    Node *left;
    Node *right;
}; 
  
string Levelorder(Node* node){
    string levelor="";
    queue<Node*> q;
    q.push(node);                     
                                           
    while (!q.empty()){                 

        Node *current = q.front();   
        q.pop();               
        levelor+=current->str;           
    
        if (current->left != NULL){    
            q.push(current->left);
        }
        if (current->right != NULL){   
            q.push(current->right);
        }
    }
    return levelor;
}

Node* newNode(char str) 
{ 
    Node *node = new Node; 
    node->str = str; 
    node->left = node->right = NULL; 
    return (node); 
} 

int find(char A[],int start,int end,char value) 
{ 
    for (int i=start; i<=end; i++) {
        if (A[i]==value) {
            return i; 
        }
    }    
    return -1; 
} 
  
Node* creat(char in[],char level[],int in_start,int in_end,int n) 
{  
    if (in_start > in_end){
        return NULL; 
    }

    Node *root = newNode(level[0]); 
  
    if (in_start == in_end) {
        return root; 
    }
    int index = -1;

    for (int i = in_start; i <= in_end; i++) {
        if (in[i] == root->str) {
            index= i; 
        }
    }    

    int j=0;
    char *level_le = new char[index]; 
    for (int i=0; i<n; i++) {

        int found=find(in, 0, index-1, level[i]);

        if (found != -1) {
            level_le[j] = level[i];
            j=j+1; 
        }

    }

    j=0;
    char *level_ri = new char[n-index-1]; 
    for (int i = 0; i < n; i++) {

        int found=find(in+index+1, 0, n-index-2, level[i]);

        if (found != -1) {
            level_ri[j] = level[i];
            j=j+1; 
        }
    }
    
    root->left = creat(in,level_le,in_start,index-1,n); 
    root->right = creat(in,level_ri,index+1,in_end,n); 
    
    delete [] level_le; 
    delete [] level_ri; 

    return root; 
} 

int main() {
    int num;
    cin >> num;
    string in1,in2;
    char level[5]={""};
    char in[5]={""};
    cout << num <<endl;

    // TreeNode instantiation
    for(int i=0; i<num; i++){
        cin >> in1;
        cin >> in2;
        cout << in1 <<endl;
        cout << in2;
        
        int len=in1.length();
        char level[len];
        char in[len];

        for(int i=0; i<len; i++){
            level[i] =in1[i];
            //cout << level[i];
        }
        for(int i=0; i<len; i++){
            in[i] =in2[i];
            //cout << in[i];
        }
        
        cout <<" ";
        int k=0;
        for(int j=0; j<in1.length();j++){
            int found = in2.find(in1[j]);
            if(k==0){
                cout<<found;
            }else{
                cout<<"-"<<found;
            }
            k=1;
        }
        cout <<" ";
        
        
        Node *root = creat(in, level, 0, len - 1, len); 
        string level_out=Levelorder(root); 
        
        if(level_out==in1){
            cout << "Yes";
        }else{
            cout << "No";
        }
        
        cout <<endl;
    
        
    }


    return 0;
}