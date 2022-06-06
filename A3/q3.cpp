#include <iostream>
using namespace std;
string ans[1000];
int ans_idx=0;
int res;
int vis[10][10], r, c;
class trie
{

public:
    trie *child[26];
    int end;
    string word;
    trie()
    {
        end = 0;
        word = "";
        for (int i = 0; i < 26; i++)
        {
            child[i] = NULL;
        }
    }
};

void dfs(trie *t, char grid[10][10], int i, int j)
{
    if (i >= r || j >= c || i < 0 || j < 0 || t->child[grid[i][j] - 'a'] == NULL || vis[i][j] == 1)
        return;
    if (t->child[grid[i][j] - 'a']->end == 1)
    {
        t->child[grid[i][j] - 'a']->end = 0;
        ans[ans_idx++]=t->child[grid[i][j] - 'a']->word;
        // return;
    }

    vis[i][j] = 1;
    trie *temp = t;
    t = t->child[grid[i][j] - 'a'];
    dfs(t, grid, i + 1, j);
    dfs(t, grid, i, j + 1);
    dfs(t, grid, i - 1, j);
    dfs(t, grid, i, j - 1);
    vis[i][j] = 0;
    t = temp;
}
void solve(trie *t, char grid[10][10])
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
             // cout<<grid[i][j]<<endl;
                if (t->child[grid[i][j] - 'a'])
            {
                dfs(t, grid, i, j);
            }
        }
    }
}
void insert(trie *t, string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (t->child[s[i] - 'a'] == NULL)
        {
            t->child[s[i] - 'a'] = new trie();
        }
        t = t->child[s[i] - 'a'];
    }
    t->word = s;
    t->end = 1;
}
int main()
{
    int X;
    cin >> r >> c;
    char grid[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            vis[i][j] = 0; //initializing visited array

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> grid[i][j];
        }
    }
    trie *t=new trie();
    cin >> X;
    for (int i = 0; i < X; i++)
    {
        string s;
        cin >> s;
        insert(t, s);
    }
    solve(t,grid);

    int n = ans_idx;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (ans[j] > ans[j + 1])
            {
                string t = ans[j];
                ans[j] = ans[j + 1];
                ans[j + 1] = t;
            }
        }
    }

    for (int i = 0; i < ans_idx; i++)
    {
        cout << ans[i] << endl;
    }
}