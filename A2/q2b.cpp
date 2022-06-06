#include<iostream>
#include<string>
#include<sstream>

#define DTYPE1 string
#define DTYPE2 string
#define STR(X) #X

using namespace std;
template<class K,class V>
class node
{
    public:
    K key;
    V val;
    node(K k,V v)
    {
        key=k;
        val=v;
    }
};
template<class K,class V>
class MAP
{
    public:
    K keys[100000];
    int len=0,total_val=0;
    node<K,V> *map[100000];
    
    MAP()
    {
        for(int i=0;i<=100000;i++)
        map[i]=NULL;
    }
    /*
    string to_string(string s)
    {
        return s;
    }
    */
   
    int computeHash(K k)
    {
        int hash=0;
        
        stringstream s1;
        s1 << k;
        string s=s1.str();
        
        for(int i=0;i<s.length();i++)
        {
            if((int)s[i]%2)
            hash+=(s[i]<<2)*23*(i+1);
            else
            hash+=(s[i]<<3)*91*(i+1);
            hash%=100000;
        }
        
        return abs(hash);
    }
    void insert(K k,V v)
    {
       int pos=computeHash(k);
            if(map[pos]==NULL)
            {
                keys[len++]=k;
                total_val++; 
            }
            
        
        
       map[pos]=new node<K,V>(k,v);
        // cout<<"m["<<k<<"]:"<<v<<"("<<pos<<")  ";
        }
    void display()
    {
        for(int i=0;i<len;i++)
        {
            int idx=computeHash(keys[i]);
            if(map[idx]!=NULL)
            cout<<map[idx]->key<<":"<<map[idx]->val<<endl;
        }
    }
    V operator [](K k)
    {
        int idx=computeHash(k);
        if(map[idx]==NULL)
        {
            static V v;
            insert(k,v);
            map[idx]=new node<K,V>(k,v);
        }
        return map[idx]->val;
    }
    void remove(K k)
    {
        int idx=computeHash(k);
        if(map[idx]!=NULL&&total_val>0)
        {
           
            total_val--;
            // cout<<"m["<<map[idx]->key<<"]:"<<map[idx]->val<<"("<<idx<<")  ";
             map[idx]=NULL;
        }
    }
    bool find(K k)
    {
      int idx=computeHash(k);
      if(map[idx]==NULL)
      return false;
      else
      return true;
    }
};

int main()
{
       int n=23,k=7;
       MAP<int,int> m;
       int a[100000]={1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,4,5,9,8,10,15,68};
    //    cout<<"Enter n and k:\n";
    //    cin>>n>>k;
    //    for(int i=0;i<n;i++)
    //    cin>>a[i];
       int c=0;
       for(int i=0;i<k;i++)
       {
           if(m.find(a[i]))
           {
             m.insert(a[i],m[a[i]]+1);
           }
           else
           {
             c++;
             m.insert(a[i],1);
           }
       }
       cout<<c<<" ";
       for(int i=k;i<n;i++)
       {
         if(m[a[i-k]]==1)
         {
           c--;
         }
         m.insert(a[i-k],m[a[i-k]]-1);
         if(m.find(a[i]))
           {
             m.insert(a[i],m[a[i]]+1);
           }
           else
           {
             c++;
             m.insert(a[i],1);
           }
           cout<<c<<" ";
       }
       cout<<endl;
       exit(0);
       return 0;
}


