#include<iostream>
#include<string>
#include<sstream>

#define DTYPE1 string
#define DTYPE2 int
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
    int ch;
    MAP<DTYPE1,DTYPE2> m;
    m.insert("A",190);
    m.insert("C",257);
    cout<<"m.find(A):"<<m.find("A")<<endl;
    cout<<"m[A]:"<<m["A"]<<endl;
    m.remove("C");
    cout<<"m.find(C):"<<m.find("C")<<endl;
    m.insert("D",129);
    cout<<"m[C]:"<<m["C"]<<endl;
    cout<<"m[B]:"<<m["B"]<<endl;
    cout<<"m[D]:"<<m["D"]<<endl;
    exit(0);
    return 0;
}
//Remove cout from remove and insert method

