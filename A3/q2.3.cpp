#include<iostream>
#include<vector>
using namespace std;
int m,n,vis[1000][1000],x,y,min_cost=1000000;
vector<int> costs;
void dfs(char grid[1000][1000], int i, int j,int cost)
{
    // cout<<i<<" "<<j<<" "<<cost<<endl;
    if(i>=n||i<0||j>=m||j<0||grid[i][j]=='#'||grid[i][j]=='R'||vis[i][j]==1)
    return;
    if(i==x&&j==y)
    {
        // cout<<cost<<endl;
        if(cost<min_cost)
        min_cost=cost;
        return;
    }
    vis[i][j]=1;
    dfs(grid,i-1,j,cost+1);
    dfs(grid,i,j+1,cost+1);
    dfs(grid,i+1,j,cost+1);
    dfs(grid,i,j-1,cost+1);
    vis[i][j]=0;
}
int main()
{
    char grid[1000][1000];
    vector<pair<int,int>> pos;
    for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
    vis[i][j]=0;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>grid[i][j];
            if(grid[i][j]=='A')
            {
                x=i;
                y=j;
            }
            if(grid[i][j]=='R')
            {
                pos.push_back({i,j});
            }
        }
    }

    dfs(grid,1,0,0);
    costs.push_back(min_cost);
    // cout<<"----"<<endl;
    // cout<<min_cost<<endl;
    x=1;y=0;
    for(int i=0;i<pos.size();i++)
    {
        min_cost=1000000;
        // cout<<"X:"<<pos[i].first<<" Y:"<<pos[i].second<<endl;
        grid[pos[i].first][pos[i].second]='.';
        dfs(grid,pos[i].first,pos[i].second,0);
        grid[pos[i].first][pos[i].second]='R';
        costs.push_back(min_cost);
        // cout<<"----"<<endl;
        // cout<<min_cost<<endl;
    }
    
    for(int i=1;i<costs.size();i++)
    {
        if(costs[i]<costs[0])
        {
            cout<<"NO\n";
            exit(0);
        }
    }
    cout<<"YES"<<endl<<costs[0]<<endl;
    return 0;
}