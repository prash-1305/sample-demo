#include<iostream>
#include<omp.h>
#include<queue>
#include<vector>
#include<thread>
using namespace std;
thread_local bool exit_flag=false;
void bfs(vector<vector<int>>&graph,int start)
{
    int nodes=graph.size();
    vector<bool> visited(nodes,false);
    queue<int>q;
    q.push(start);
    visited[start]=true;
    #pragma omp parallel 
  {
    while(!q.empty() && !exit_flag)
    {
        int curr;
        #pragma omp critical
        {
            if(q.empty()){
                exit_flag=true;
            }
            else{
                curr=q.front();
                q.pop();
            }
        }
        if(!exit_flag){
           cout<<curr<<" ";
           for(auto nb:graph[curr])
          {
            if(!visited[nb])
            {
                visited[nb]=true;
                #pragma omp critical
                {
                   q.push(nb);
                }
                
            }
          }
        }
       
        
    }
  } 
    
}
int main()
{
    vector<vector<int>>graph(5);
    graph[0]={1,2,3};
    graph[1]={0,2};
    graph[2]={1,3};
    graph[3]={0,2,4};
    graph[4]={3};
    bfs(graph,0);
}