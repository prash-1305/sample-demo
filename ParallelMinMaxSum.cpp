#include<iostream>
#include<omp.h>
using namespace std;
void minfunc(int arr[],int n)
{
    int mini=arr[0];
    #pragma omp parallel for reduction(min :mini)
    for(int i=0;i<n;i++)
    {
        if(arr[i]<mini)
        {
            mini=arr[i];
        }
    }
    cout<<"MIN :"<<mini<<endl;
}
void maxfunc(int arr[],int n)
{
    int maxi=arr[0];
    #pragma omp parallel for reduction(max : maxi)
    for(int j=0;j<n;j++)
    {
        if(arr[j]>maxi)
        {
            maxi=arr[j];
        }
    }
    cout<<"MAX :"<<maxi<<endl;
}
void sumfunc(int arr[],int n)
{
    int sum=0;
    #pragma omp parallel for reduction(+ : sum)
    for(int k=0;k<n;k++)
    {
        sum=sum+arr[k];
    }
    cout<<"SUM :"<<sum<<endl;
    int avg=sum/n;
    cout<<"AVG :"<<avg;
}
int main()
{
    int arr[]={3,1,12,5,6};
    double start=omp_get_wtime();
    minfunc(arr,5);
    maxfunc(arr,5);
    sumfunc(arr,5);
    double end=omp_get_wtime();
    cout<<"Result "<<end-start <<"seconds"<<endl;

}