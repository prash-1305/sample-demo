#include<iostream>
#include<omp.h>
using namespace std;
void sort(int arr[],int n)
{  
    #pragma omp parallel
    for(int i=0;i<n-1;i++)
    {   
        #pragma omp for
        for(int j=i+1;j<n;j++)
        {
            if(arr[i]>arr[j])
            {
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    for(int k=0;k<n;k++)
    {
        cout<<arr[k]<<"\t";
    }
}
int main()
{
    int arr[]={4,2,1,3,5};
    double start=omp_get_wtime();
    sort(arr,5);
    double end=omp_get_wtime();
    cout<<endl;
    cout<<"Result : "<<(end-start)<<" sec"<<endl;
}