#include<iostream>
#include<vector>
using namespace std;
class trie
{
    public:
    trie* left;
    trie* right;
    // trie()
    // {
    //     left=NULL;
    //     right=NULL;
    // }
};
void insert(trie *t,int n)
{
    for(int i=31;i>=0;i--)
    {
        if(n&(1<<i))
        {
            if(!t->right)
            t->right=new trie();
            t=t->right;
        }
        else
        {
            if(!t->left)
            t->left=new trie();
            t=t->left;
        }
    }
}
int find(trie *t,int n)
{
    int ans=0;
    for(int i=31;i>=0;i--)
    {
        int bit=n&(1<<i);
        if(bit)
        {
            if(t->left)
            {
                ans+=(1<<i);
                t=t->left;
            }
            else
            t=t->right;
        }
        else
        {
            if(t->right)
            {
                ans+=(1<<i);
                t=t->right;
            }
            else
            t=t->left;
        }
    }
    return ans;
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<int> v;
    trie* t=new trie();
    for(int i=0;i<n;i++)
    {
        int inp;
        cin>>inp;
        insert(t,inp);
        v.push_back(inp);
    }
    for(int i=0;i<m;i++)
    {
        int inp;
        cin>>inp;
        cout<<find(t,inp)<<endl;
    }
    return 0;
}