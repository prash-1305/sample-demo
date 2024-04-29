#include <iostream>
#include <vector>
#include <stack>
#include<omp.h>
#include <thread> // For thread_local

using namespace std;

thread_local bool exit_flag = false; // Thread-local flag

void dfs(vector<vector<int>>& graph, int start) {
  int nodes = graph.size();
  vector<bool> visited(nodes, false);
  stack<int> s;
  s.push(start);
  visited[start] = true;

  #pragma omp parallel
  {
    while (!s.empty() && !exit_flag) {
      int curr;

      #pragma omp critical  // Critical section for stack access
      {
        if (s.empty()) {
          exit_flag = true;  // Set flag to exit for this thread
        } else {
          curr = s.top();
          s.pop();
        }
      }

      if (!exit_flag) {
        cout << curr << " ";

        for (auto nb : graph[curr]) {
          if (!visited[nb]) {
            visited[nb] = true;

            #pragma omp critical  // Critical section for pushing to stack
            {
              s.push(nb);
            }
          }
        }
      }
    }
  }
}

int main() {
  vector<vector<int>> graph(5);
    graph[0]={1,2,3};
    graph[1]={0,2};
    graph[2]={1,3};
    graph[3]={0,2,4};
    graph[4]={3};
    double start=omp_get_wtime();
    dfs(graph,0);
    double end=omp_get_wtime();
    cout<<"Results :"<<(end-start)<<" sec";
 
}
