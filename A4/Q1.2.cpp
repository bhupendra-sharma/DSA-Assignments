#define MAX_N 1000010 // second approach: O(n log n)
#include<bits/stdc++.h>
using namespace std;
char T[MAX_N]; // the input string, up to 100K characters
int n; // the length of input string
int k_inp;
int RA[MAX_N], tempRA[MAX_N]; // rank array and temporary rank array
int SA[MAX_N], tempSA[MAX_N]; // suffix array and temporary suffix array
int LCP[MAX_N];
int  rnk[MAX_N]; //for kasai

int c[MAX_N]; // for counting/radix sort

void kasai()
{
    int k=0;
    for(int i=0;i<n;i++) 
    {
        rnk[SA[i]]=i;
    }

    for(int i=0;i<n;i++,k=max(k-1,0))
    {
        if(rnk[i]==n-1)
        {
            k=0;
            continue;
        }
        int j=SA[rnk[i]+1];
        while (i+k<n&&j+k<n&&T[i+k]==T[j+k])
        k++;
        LCP[rnk[i]]=k;
    }
}
void countingSort(int k) { // O(n)

    int i, sum, maxi = max(300, n); // up to 255 ASCII chars or length of n
    memset(c, 0, sizeof c); // clear frequency table

    for (i = 0; i < n; i++){ // count the frequency of each integer rank
        c[i + k < n ? RA[i + k] : 0]++;
    }
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i]; c[i] = sum; sum += t; 
    }
    for (i = 0; i < n; i++){ // shuffle the suffix array if necessary
        tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
    }
    for (i = 0; i < n; i++){ // update the suffix array SA
        SA[i] = tempSA[i];
    }
}

void constructSA() { // this version can go up to 100000 characters
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i]; // initial rankings
    for (i = 0; i < n; i++) SA[i] = i; //initial SA: {0, 1, 2, ..., n-1}

    for (k = 1; k < n; k <<= 1) { // repeat sorting process log n times
        countingSort(k); //actually radix sort:sort based on the second item
        countingSort(0); // then (stable) sort based on the first item

        tempRA[SA[0]] = r = 0; // re-ranking; start from rank r = 0

        // compare adjacent suffixes
        for (i = 1; i < n; i++){
            // if same pair => same rank r; otherwise,increase r
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;           
        }

        for (i = 0; i < n; i++){// update the rank array RA
            RA[i] = tempRA[i];
        }

        if (RA[SA[n-1]] == n-1) break; // nice optimization trick
    } 
    kasai();
}
int main()
{
	 cin>>k_inp>>n;
    scanf("%s",T);
   if(k_inp==1)
   {cout<<n;exit(0);}
   string s1=T;
	s1=s1+'$';
	strcpy(T,s1.c_str());
   n++;
    // n=strlen(T);
    constructSA();
    int ans=0;
    for(int i=0;i<n-k_inp+1;i++)
    {
        int min_lcp=INT_MAX;
        // cout<<"i:"<<i<<" i+k:"<<i+k<<" ";
        for(int j=i;j<(i+k_inp-1);j++)
        {
            min_lcp=min(min_lcp,LCP[j]);
            // cout<<":"<<min_lcp<<":";
        }
        ans=max(ans,min_lcp);
    }
    // for(int i=0;i<n;i++)
    // cout<<LCP[i]<<" ";
    if(ans==INT_MAX)
    cout<<-1;
    else
    cout<<ans;
    return 0;
}