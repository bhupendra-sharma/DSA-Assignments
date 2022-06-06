#include<iostream>
#include<vector>
#include<stack>
#include<bits/stdc++.h>
using namespace std;
vector<string> v,words;
int count_=0,dp[1001][1001];
string st;
class trie
{
    public:
    trie *child[26];
    int end;
    string word;
    trie()
    {
        end=0;
        for(int i=0;i<26;i++)
        {
            child[i]=NULL;
        }
        string word;
    }
};
void insert(trie *t,string s)
{
    for(int i=0;i<s.length();i++)
    {
        if(t->child[s[i]-'a']==NULL)
        {
            t->child[s[i]-'a']=new trie();
        }
        t=t->child[s[i]-'a'];
    }
    t->end=1;
    t->word=s;
    words.push_back(s);
}
int spellcheck(trie *t,string s)
{
    for(int i=0;i<s.length();i++)
    {
        if(t->child[s[i]-'a']==NULL)
        {
            return false;
        }
        t=t->child[s[i]-'a'];
    }
    return t->end;
}
void dfs(trie *t)
{
    if(t==NULL)
    return;
    if(t->end)
    {
        v.push_back(st);
        count_++;
        // cout<<st<<endl;
    }
    
    for(int i=0;i<26;i++)
    {
        if(t->child[i])
        {
            st.push_back(i+'a');
            dfs(t->child[i]);
            st.pop_back();
        }
    }
    
}
void autocomplete(trie* t,string s)
{
    v.clear();
    st="";
    count_=0;
    for(int i=0;i<s.length();i++)
    {
        if(t->child[s[i]-'a']==NULL)
        {
            break;
        }
        
        st.push_back(s[i]);
        t=t->child[s[i]-'a'];
    }
    // cout<<endl<<s<<" "<<st<<endl;
    dfs(t);
}
// int min(int a,int b,int c)
// {
//     return min(a,min(b,c));
// }
// void autocorrect(trie *t,string s,int m,int n)
// {
//     if(t==NULL || n>s.length())
//     return;
//     for(int i=0;i<26;i++)
//     {
//         if(t->child[i])
//         {
//             if(s[n-1]==i+'a')
//             dp[m][n]=dp[m-1][n-1];
//             else
//             dp[m][n]=1+min(dp[m][n-1],dp[m-1][n],dp[m-1][n-1]);
//             if(t->end&&dp[m][n]<=3)
//             {
//                 v.push_back(t->word);
//             }
//             autocorrect(t->child[i],s,m+1,n);  
//         }      
//     }  
//     autocorrect(t,s,m,n+1);    
// }

int edit_distance(string a,string b)
{
    int m=a.length(),n=b.length();
    for(int i=0;i<=max(m,n);i++)
    {
        dp[i][0]=dp[0][i]=i;
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(a[i-1]==b[j-1])
            dp[i][j]=dp[i-1][j-1];
            else
            dp[i][j]=1+min(dp[i-1][j-1],min(dp[i][j-1],dp[i-1][j]));
        }
    }
    return dp[m][n];
}
void autocorrect(trie *t,string s)
{
    for(int i=0;i<words.size();i++)
    {
        if(edit_distance(s,words[i])<=3)
        v.push_back(words[i]);
    }
}
int main()
{
    for(int i=0;i<=1000;i++)
    dp[i][0]=dp[0][i]=i;
    int n;
    string s;
    trie *t=new trie();
    // cout<<"Enter N:\n";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        insert(t,s);
    }
    int q=1;
    // cout<<"Enter number of queries\n";
    // cin>>q;
    for(int i=0;i<q;i++)
    {
        int ai;
        string ti;
        cin>>ai>>ti;
        if(ai==1)
        {
            cout<<spellcheck(t,ti)<<endl;
        }
        else
        if(ai==2)
        {
            v.clear();
            count_=0;
            autocomplete(t,ti);
            cout<<count_<<endl;
            sort(v.begin(),v.end());
            for(int i=0;i<count_;i++)
            {
                cout<<v[i]<<endl;
            }
        }
        else
        if(ai==3)
        {
            v.clear();
            // autocorrect(t,ti,1,1);

            autocorrect(t,ti);

            cout<<v.size()<<endl;
            sort(v.begin(),v.end());
            for(int i=0;i<v.size();i++)
            {
                cout<<v[i]<<endl;
            }


        }
    }
    return 0;
}