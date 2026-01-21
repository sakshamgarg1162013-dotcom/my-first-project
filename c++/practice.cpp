#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector <int> v;
    v = {1,6,1,2,3,2,4,5};
    sort(v.begin(),v.end());
    for (int i = 0; i < v.size(); i++)
    {
        cout<<v[i];
    }
    cout<<endl;
    
    
    for (int i = 0; i < v.size(); i++){
        if (v[v.size()-1]!=v[v.size()-2])
        {
            v.pop_back();
            
        }  
        
    }

    int arr[v.size()/2];
        for (int i = 1; i <= v.size()/2; i++)
        {
            arr[i-1]=v[2*i-1];
        }
    for (int i = 0; i < v.size()/2; i++)
    {
        cout<<arr[i];
    }
        
    }