#include<iostream>
using namespace std;
class LL
{
public:
int row;
int col;
double data;
LL* next;
LL* prev;
};
void add();
void mul();
void transpose();
void print(LL*);
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
  cout<<"Enter 1st sparse matrix in triplet form[First line should have triplet-> (number of rows,number of cols,non zero values in matrix i.e nz),each nz line should have triplet in form->(row number,Column numer,value)]\n";
  cin>>r1>>c1>>nz1;
  LL* head1=new LL();
  head1->row=r1;
  head1->col=c1;
  head1->data=nz1;
  head1->prev=NULL;
  head1->next=NULL;
  LL* temp=head1;
  for(int i=1;i<=nz1;i++)
  {
    int t1,t2;
    double t3;
    cin>>t1>>t2>>t3;
    LL* temp1=new LL();
    temp1->row=t1;
    temp1->col=t2;
    temp1->data=t3;
    temp1->prev=temp;
    temp1->next=NULL;
    temp->next=temp1;
    temp=temp->next;
  }
  int r2,c2,nz2;
  cout<<"Enter 2nd sparse matrix in triplet form[First line should have triplet-> (number of rows,number of cols,non zero values in matrix i.e nz),each nz line should have triplet in form->(row number,Column numer,value)]\n";
  cin>>r2>>c2>>nz2;
  if(r1!=r2 || c1!=c2)
  {
    cout<<"Matrices should have same dimension\n";
    return;
  }
  LL* head2=new LL();
  head2->row=r2;
  head2->col=c2;
  head2->data=nz2;
  head2->prev=NULL;
  head2->next=NULL;
  temp=head2;
  for(int i=1;i<=nz2;i++)
  {
    int t1,t2;
    double t3;
    cin>>t1>>t2>>t3;
    LL* temp1=new LL();
    temp1->row=t1;
    temp1->col=t2;
    temp1->data=t3;
    temp1->prev=temp;
    temp1->next=NULL;
    temp->next=temp1;
    temp=temp->next;
  }
  LL* head3=new LL();
  head3->row=r2;
  head3->col=c2;
  head3->data=0;
  head3->prev=NULL;
  head3->next=NULL;
  int total_nz=0;
  LL* i=head1->next;
  LL* j=head2->next;
  LL* k=head3;
  while(i!=NULL&&j!=NULL)
  {
    if(i->row==j->row)
    {
      if(i->col==j->col)
      {
        LL* k1=new LL();
        k1->row=i->row;
        k1->col=i->col;
        k1->data=i->data+j->data;
        k1->prev=k;
        k1->next=NULL;
        k->next=k1;
        k=k->next;
        i=i->next;
        j=j->next;
        total_nz++;
      }
      else if(i->col < j->col)
      {
        LL* k1=new LL();
        k1->row=i->row;
        k1->col=i->col;
        k1->data=i->data;
        k1->prev=k;
        k1->next=NULL;
        k->next=k1;
        k=k->next;
        i=i->next;
        total_nz++;
      }
      else
      {
        LL* k1=new LL();
        k1->row=j->row;
        k1->col=j->col;
        k1->data=j->data;
        k1->prev=k;
        k1->next=NULL;
        k->next=k1;
        k=k->next;
        j=j->next;
        total_nz++;
      }
    }
    else
    if(i->row < j->row)
    {
        LL* k1=new LL();
        k1->row=i->row;
        k1->col=i->col;
        k1->data=i->data;
        k1->prev=k;
        k1->next=NULL;
        k->next=k1;
        k=k->next;
        i=i->next;
        total_nz++;
    }
    else
    {
        LL* k1=new LL();
        k1->row=j->row;
        k1->col=j->col;
        k1->data=j->data;
        k1->prev=k;
        k1->next=NULL;
        k->next=k1;
        k=k->next;
        j=j->next;
        total_nz++;
    }
  }
  if(i==NULL)
  {
    while(j!=NULL)
    {
        LL* k1=new LL();
        k1->row=j->row;
        k1->col=j->col;
        k1->data=j->data;
        k1->prev=k;
        k1->next=NULL;
        k->next=k1;
        k=k->next;
        j=j->next;
        total_nz++;
    }
  }
  if(j==NULL)
  {
    while(i!=NULL)
    {
        LL* k1=new LL();
        k1->row=i->row;
        k1->col=i->col;
        k1->data=i->data;
        k1->prev=k;
        k1->next=NULL;
        k->next=k1;
        k=k->next;
        i=i->next;
        total_nz++;
    }
  }
  head3->data=total_nz;
  cout<<"Result:"<<endl;
  print(head3);
  
}
void mul()
{
  int r1,c1,nz1;
  cout<<"Enter 1st sparse matrix in triplet form[First line should have triplet-> (number of rows,number of cols,non zero values in matrix i.e nz),each nz line should have triplet in form->(row number,Column numer,value)]\n";
  cin>>r1>>c1>>nz1;
  LL* head1=new LL();
  head1->row=r1;
  head1->col=c1;
  head1->data=nz1;
  head1->prev=NULL;
  head1->next=NULL;
  LL* temp=head1;
  for(int i=1;i<=nz1;i++)
  {
    int t1,t2;
    double t3;
    cin>>t1>>t2>>t3;
    LL* temp1=new LL();
    temp1->row=t1;
    temp1->col=t2;
    temp1->data=t3;
    temp1->prev=temp;
    temp1->next=NULL;
    temp->next=temp1;
    temp=temp->next;
  }
  int r2,c2,nz2;
  cout<<"Enter 2nd sparse matrix in triplet form[First line should have triplet-> (number of rows,number of cols,non zero values in matrix i.e nz),each nz line should have triplet in form->(row number,Column numer,value)]\n";
  cin>>r2>>c2>>nz2;
  
  if(c1!=r2)
  {
    cout<<"Matrices are not comatible for multiplication,Columns of 1st matrix is not equal rows in second matrix\n";
    return;
  }
  
  LL* head2=new LL();
  head2->row=r2;
  head2->col=c2;
  head2->data=nz2;
  head2->prev=NULL;
  head2->next=NULL;
  temp=head2;
  for(int i=1;i<=nz2;i++)
  {
    int t1,t2;
    double t3;
    cin>>t1>>t2>>t3;
    LL* temp1=new LL();
    temp1->row=t1;
    temp1->col=t2;
    temp1->data=t3;
    temp1->prev=temp;
    temp1->next=NULL;
    temp->next=temp1;
    temp=temp->next;
  }
  LL* head3=new LL();
  head3->row=r1;
  head3->col=c2;
  head3->data=0;
  head3->prev=NULL;
  head3->next=NULL;
  int total_nz=0;
  LL* i=head1->next;
  LL* j=head2->next;
  LL* k=head3;
  while(i!=NULL)
  {
    j=head2->next;
    while(j!=NULL)
    {
      if(i->col==j->row)
      {
        LL* k1=new LL();
        k1->row=i->row;
        k1->col=j->col;
        k1->data=i->data*j->data;
        k1->prev=k;
        k1->next=NULL;
        k->next=k1;
        k=k->next;
        total_nz++;
      }
      j=j->next;
    }
    i=i->next;
  }

  total_nz--;
  k=head3->next;
  while(k->next!=NULL)
  {
    LL* k1=k->next;
    while(k1!=NULL)
    {
      if(k->row < k1->row)
      break;
      if(k->row==k1->row&&k->col==k1->col)
      {
        
        total_nz--;
        k->data+=k1->data;
        if(k1->next!=NULL)
        {
          k1->prev->next=k1->next;
          k1->next->prev=k1->prev;
        }
        else
        k1->prev->next=NULL;
      }
      k1=k1->next;
    }
    k=k->next;
  }
   head3->data=total_nz;
  cout<<"Result:"<<endl;
  print(head3);
}
void transpose()
{
  int r,col,nz;
  cout<<"Enter sparse matrix in triplet form[First line should have triplet-> (number of rows,number of cols,non zero values in matrix i.e nz),each nz line should have triplet in form->(row number,Column numer,value)]\n";
  cin>>r>>col>>nz;
  LL* head1=new LL();
  head1->row=r;
  head1->col=col;
  head1->data=nz;
  head1->prev=NULL;
  head1->next=NULL;
  LL* temp=head1;
  for(int i=1;i<=nz;i++)
  {
    int t1,t2;
    double t3;
    cin>>t1>>t2>>t3;
    LL* temp1=new LL();
    temp1->row=t1;
    temp1->col=t2;
    temp1->data=t3;
    temp1->prev=temp;
    temp1->next=NULL;
    temp->next=temp1;
    temp=temp->next;
  }
  double c[nz+1][3];
  c[0][0]=col;
  c[0][1]=r;
  c[0][2]=nz;
  int nzc[col+1]={0};
  int idx[r];  
  idx[0]=1;
  int k=1;
  temp=head1->next;
  while(temp!=NULL)
  {
    nzc[temp->col]++;
    temp=temp->next;
  }
  
  for(int i=1;i<=col;i++)
  idx[i]=idx[i-1]+nzc[i-1];
  
  temp=head1->next;
  while(temp!=NULL)
  {
    int t=idx[(int)temp->col];
    idx[(int)temp->col]++;
    c[t][0]=temp->col;
    c[t][1]=temp->row;
    c[t][2]=temp->data;
    temp=temp->next;
  }
  
  LL* transposed=new LL();
  transposed->row=c[0][0];
  transposed->col=c[0][1];
  transposed->data=c[0][2];
  transposed->prev=NULL;
  transposed->next=NULL;
  temp=transposed;
  for(int i=1;i<=c[0][2];i++)
  {
    int t1,t2;
    double t3;
    t1=c[i][0];
    t2=c[i][1];
    t3=c[i][2];
    LL* temp1=new LL();
    temp1->row=t1;
    temp1->col=t2;
    temp1->data=t3;
    temp1->prev=temp;
    temp1->next=NULL;
    temp->next=temp1;
    temp=temp->next;
  }
  cout<<"Result:"<<endl;
  print(transposed);
  
}
void print(LL* k)
{
  cout<<"Rows:"<<k->row<<" Columns:"<<k->col<<" Non zero Values:"<<k->data<<endl;
  k=k->next;
  while(k!=NULL)
  {
    cout<<k->row<<" "<<k->col<<" "<<k->data<<endl;
    k=k->next;
  }
}
