#include<iostream>
#include<fstream>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
#define CHUNK 10
string s;
long long n,n1,num=0,file_num=0;
vector<long long> v;
struct heap
{
    public:
    vector<pair<long long int,int>> h;
    int parent(int n)
    {
        return (n-1)/2;
    }
    int left(int n)
    {
        return 2*n+1;
    }
    int right(int n)
    {
        return 2*n+2;
    }
    unsigned long int size()
    {
        return h.size();
    }
    bool empty()
    {
        if(h.size()==0)
        return true;
        return false;
    }
    void heapify_down(int i)
    {
        int l=left(i),r=right(i),largest=i;
        if(l<h.size() && h[l].first>h[i].first)
        largest=l;

        if(r<h.size() && h[r].first>h[largest].first)
        largest=r;

        if(largest!=i)
        {
            long long temp=h[i].first;
            h[i].first=h[largest].first;
            h[largest].first=temp;

            int temp1=h[i].second;
            h[i].second=h[largest].second;
            h[largest].second=temp1;

            heapify_down(largest);
        }
    }
    void heapify_up(int i)
    {
        if(i!=0 && h[parent(i)].first<h[i].first)
        {
            long long temp=h[i].first;
            h[i].first=h[parent(i)].first;
            h[parent(i)].first=temp;

            int temp1=h[i].second;
            h[i].second=h[parent(i)].second;
            h[parent(i)].second=temp1;

            heapify_up(parent(i));
        }
    }
    void push(long long int ele,int fileno)
    {
        h.push_back({ele,fileno});
        heapify_up(h.size()-1);
    }
    void pop()
    {
        if(h.size()>0)
        {
            h[0].first=h[h.size()-1].first;
            h[0].second=h[h.size()-1].second;
            h.pop_back();
            heapify_down(0);
        }
    }
    pair<long long int,int> top()
    {
        if(h.size()>0)
        return h[0];
        else
        return {-1,-1};
    }
};

long long int getNext(string &s)
{
    string temp="";
    int i;
    for(i=0;i<s.length();i++)
    {
        if(s[i]==',')
        break;
        temp+=s[i];
    }
    if(i!=s.length())
    s=s.substr(i);
    cout<<temp<<endl;
    string temp1="";
    for(int j=0;j<temp.length();j++)
    {
        if(temp[j]>='0'&&temp[j]<='9')
        temp1+=temp[i];
    }
    return stoll(temp1);
    // return 10;
}
int main()
{
    ifstream finp;
    finp.open("input.txt"); //assuming file will have number in one line seprated by comma 
    finp>>s;
    n=s.length();
    cout<<n<<endl;
    int count=0;

    for(int i=0;i<n;i++)
    {
        if(s[i]==',')
        count++;
    }
    count++;
    cout<<"Numbers:"<<count;

    string temp="";
    for(int i=0;i<n;i++)
    {
        if(num==CHUNK)
        {
            num=0;
            sort(v.begin(),v.end());
            ofstream foutp;
            string filename="Tfile"+to_string(file_num)+".txt";
            file_num++;
            foutp.open(filename);
            for(int j=0;j<v.size();j++)
            {
                if(j!=v.size()-1)
                foutp<<(to_string(v[j])+",");
                else
                foutp<<to_string(v[j]);
            }
            v.clear();
            foutp.close();
        }
        if(s[i]==',')
        {
            v.push_back(stol(temp));
            num++;
            temp="";
            continue;
        }
        temp+=s[i];
    }
    v.push_back(stol(temp));
    sort(v.begin(),v.end());
    ofstream foutp;
    string filename="Tfile"+to_string(file_num);
    file_num++;
    foutp.open(filename);
    cout<<file_num;
    for(int j=0;j<v.size();j++)
    {
        if(j!=v.size()-1)
        foutp<<(to_string(v[j])+",");
        else
        foutp<<to_string(v[j]);
    }
    foutp.close();
    v.clear();
    heap hp;

    ifstream f[file_num];
    string files[file_num];
    for(int i=0;i<file_num;i++)
    {
        string filename="Tfile"+to_string(i)+".txt";
        f[i].open(filename.c_str());
        f[i]>>files[i];
        hp.push(getNext(files[i]),i);
    }
    int counter=0;
    ofstream output;
    output.open("output.txt");
    while(counter!=count)
    {
        if(hp.size()>0)
        {
            pair<long long int,int> file_info=hp.top();
            output<<(to_string(file_info.first)+",");
            hp.pop();
            hp.push(getNext(files[file_info.second]),file_info.second);
            counter++;
        }

    }
    for(int i=0;i<file_num;i++)
    {
        f[i].close();
    }
    output.close();
    finp.close();
    return 0;
}