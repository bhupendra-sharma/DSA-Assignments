#include<iostream>
using namespace std;
void add();
void mul();
void transpose();
int main()
{
  int ch;
  cout<<"1.Addition\n2.Multiplication\n3.Transpose\n";
  cin>>ch;
  switch(ch)
  {
   case 1:add();
          break; 
   case 2:mul();
          break; 
   case 3:transpose();
          break;
  }
  return 0;
}
void add()
{
  int r1,c1,nz1;
  cout<<"Enter 1st matrix\n";
  cin>>r1>>c1>>nz1;
  double a[nz1+1][3];
  a[0][0]=r1;
  a[0][1]=c1;
  a[0][2]=nz1;
  for(int i=1;i<=nz1;i++)
  cin>>a[i][0]>>a[i][1]>>a[i][2];
  int r2,c2,nz2;
  cout<<"Enter 2nd matrix\n";
  cin>>r2>>c2>>nz2;
  double b[nz2+1][3];
  b[0][0]=r2;
  b[0][1]=c2;
  b[0][2]=nz2;
  for(int i=1;i<=nz2;i++)
  cin>>b[i][0]>>b[i][1]>>b[i][2];
  double c[nz1+nz2+1][3];
  int nz3=1;
  c[0][0]=r1;
  c[0][1]=c1;
  int i=1,j=1;
  while(i<=nz1&&j<=nz2)
  {
    if(a[i][0]==b[j][0])
    {
      if(a[i][1]==b[j][1])
      {
        c[nz3][0]=a[i][0];
        c[nz3][1]=a[i][1];
        c[nz3][2]=a[i][2]+b[j][2];
        i++;
        j++;
        nz3++;
      }
      else if(a[i][1]<b[j][1])
      {
        c[nz3][0]=a[i][0];
        c[nz3][1]=a[i][1];
        c[nz3][2]=a[i][2];
        i++;
        nz3++;
      }
      else
      {
        c[nz3][0]=b[j][0];
        c[nz3][1]=b[j][1];
        c[nz3][2]=b[j][2];
        j++;
        nz3++;
      }
    }
    else
    if(a[i][0]<b[j][0])
    {
        c[nz3][0]=a[i][0];
        c[nz3][1]=a[i][1];
        c[nz3][2]=a[i][2];
        i++;
        nz3++;
    }
    else
    {
        c[nz3][0]=b[j][0];
        c[nz3][1]=b[j][1];
        c[nz3][2]=b[j][2];
        j++;
        nz3++;
    }
  }
  if(i==nz1+1)
  {
    while(j<=nz2)
    {
        c[nz3][0]=b[j][0];
        c[nz3][1]=b[j][1];
        c[nz3][2]=b[j][2];
        j++;
        nz3++;
    }
  }
  if(j==nz2+1)
  {
    while(i<=nz1)
    {
        c[nz3][0]=a[i][0];
        c[nz3][1]=a[i][1];
        c[nz3][2]=a[i][2];
        i++;
        nz3++;
    }
  }
  c[0][2]=nz3-1;
  cout<<"Result:"<<endl;
  for(int i=0;i<=c[0][2];i++)
  cout<<c[i][0]<<" "<<c[i][1]<<" "<<c[i][2]<<endl;
}
void mul()
{
  int r1,c1,nz1;
  cout<<"Enter 1st matrix\n";
  cin>>r1>>c1>>nz1;
  double a[nz1+1][3];
  a[0][0]=r1;
  a[0][1]=c1;
  a[0][2]=nz1;
  for(int i=1;i<=nz1;i++)
  cin>>a[i][0]>>a[i][1]>>a[i][2];
  int r2,c2,nz2;
  cout<<"Enter 2nd matrix\n";
  cin>>r2>>c2>>nz2;
  double b[nz2+1][3];
  b[0][0]=r2;
  b[0][1]=c2;
  b[0][2]=nz2;
  for(int i=1;i<=nz2;i++)
  cin>>b[i][0]>>b[i][1]>>b[i][2];
  double c[r1*c2][3];
  int k=1;
  c[0][0]=r1;
  c[0][1]=c2;
  for(int i=1;i<=nz1;i++)
  {
    for(int j=1;j<=nz2;j++)
    {
      if(a[i][1]==b[j][0])
      {
        c[k][0]=a[i][0];
        c[k][1]=b[j][1];
        c[k][2]=a[i][2]*b[j][2];
        k++;
      }
    }
  }
  k--;
  c[0][2]=k;
  for(int i=1;i<k;i++)
  {
    if(a[i][0]==-1)
    continue;
    
    for(int j=i+1;j<=k;j++)
    {
      if(c[i][0]<c[j][0])
      break;
      if(c[i][0]==c[j][0]&&c[i][1]==c[j][1])
      {
       c[i][2]+=c[j][2];
       c[j][0]=-1;
       c[0][2]--;
      }
    }
  }
  //c[0][2]=nz_k;
  cout<<"Result:"<<endl;
  for(int i=0;i<=k;i++)
  if(c[i][0]!=-1)
  cout<<c[i][0]<<" "<<c[i][1]<<" "<<c[i][2]<<endl;
}
void transpose()
{
  int r,col,nz;
  cout<<"Enter array:"<<endl;
  cin>>r>>col>>nz;
  double a[nz+1][3];
  a[0][0]=r;
  a[0][1]=col;
  a[0][2]=nz;
  for(int i=1;i<=nz;i++)
  cin>>a[i][0]>>a[i][1]>>a[i][2];
  double c[nz+1][3];
  c[0][0]=col;
  c[0][1]=r;
  c[0][2]=nz;
  int nzc[col+1]={0};
  //for(int i=1;i<=col;i++)
  //nzc[i]=0;
  int idx[r];  
  idx[0]=1;
  int k=1;
  for(int i=1;i<=nz;i++)
  nzc[(int)a[i][1]]++;
 
  for(int i=1;i<=col;i++)
  idx[i]=idx[i-1]+nzc[i-1];
 
  for(int i=1;i<=nz;i++)
  {
    int t=idx[(int)a[i][1]];
    idx[(int)a[i][1]]++;
    c[t][0]=a[i][1];
    c[t][1]=a[i][0];
    c[t][2]=a[i][2];
  }
  cout<<"Result:"<<endl;
  for(int i=0;i<=c[0][2];i++)
  cout<<c[i][0]<<" "<<c[i][1]<<" "<<c[i][2]<<endl;
}
