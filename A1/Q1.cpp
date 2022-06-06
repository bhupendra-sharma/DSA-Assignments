#include<iostream>
using namespace std;
string add(string,string);
string mul(string,string);
string sub(string,string);
string exp(string,unsigned long long);
string fact(string);
string mul_fact(string,int);
string cal(string);
string gcd(string,string);
string mod(string,string);
int isEven(string);
string divby2(string);
int gt(string,string);
void rev(string &);
int main()
{
  int c;
  cout<<"1.Exponentiation\n2.GCD\n3.Factorial\n4.Calculator\n";
  cin>>c;
  string a,b;
  unsigned long long m;
  switch(c)
  {
    case 1:
           cin>>a>>m;
           cout<<"Exponentiation:"<<exp(a,m)<<endl;
           break;
    case 2:
           cin>>a>>b;
           cout<<"GCD:"<<gcd(a,b)<<endl;
           break;
    case 3:
           cin>>a;
           cout<<"Factorial:"<<fact(a)<<endl;
           break;
    case 4:
           cin>>a;
           cout<<"Result:"<<cal(a)<<endl;
           break;
    default:cout<<"Enter correct input"<<endl;
  }
  return 0;
}
string cal(string a)
{
  string operand[1000],operation;
  int p=0;
  for(int i=0;i<a.length();i++)
  {    
    if(a[i]=='x'||a[i]=='-'||a[i]=='+')
    {
      operation.push_back(a[i]);
      p++;
    }
    else
    {
      operand[p].push_back(a[i]);
    }
  }
  int i=0;
  int c_operand=operation.length()+1;
  int c_operation=operation.length();
  for(i=0;i<c_operation;i++)
  {
    if(operation[i]=='x')
    {
      string int_res=mul(operand[i],operand[i+1]);
      operand[i]=int_res;
      for(int j=i+1;j<c_operand-1;j++)
      {
        operand[j]=operand[j+1];
        operation[j-1]=operation[j];
      }
      c_operand--;
      c_operation--;
      i--;
    }
      
  }
  
  for(i=0;i<c_operation;i++)
  {
    if(operation[i]=='+')
    {
      operand[i+1]=add(operand[i],operand[i+1]);
    }
    else
    {
      operand[i+1]=sub(operand[i],operand[i+1]);      
    }
  }
  
  //for(i=0;i<c_operation;i++)
  //cout<<operand[i]<<operation[i];  
  //cout<<operand[i];
  //return " ";
  return operand[i];
}
string add(string a,string b)
{
  string c;
  rev(a);
  rev(b);
  int carry=0;
  for(int i=0;i<max(a.length(),b.length());i++)
  {
    if(i<a.length())
    carry+=a[i]-'0';
    if(i<b.length())
    carry+=b[i]-'0';
    c.push_back(carry%10+'0');
    carry/=10;
  }
  if(carry)
  c.push_back(carry+'0');
  rev(c);
  return c;
}
string mul(string a,string b)
{
  string ans="0";
  rev(a);
  rev(b);
  for(int i=0;i<a.length();i++)
  {
    int carry=0;
    string c;
    for(int j=0;j<b.length();j++)
    {
      carry+=(a[i]-'0')*(b[j]-'0');
      c.push_back(carry%10+'0');
      carry/=10;
    }
    if(carry)
    c.push_back(carry+'0');
    rev(c);
    for(int k=1;k<=i;k++)
    c.push_back('0');
    ans=add(ans,c);
    //cout<<"C:"<<c<<" ans"<<ans<<endl;
  }
  return ans;
}
string sub(string a,string b)
{
  string c;
  if(a.length()<b.length())
  {
    string t=a;
    a=b;
    b=t;
  }
  rev(a);
  rev(b);
  int alen=a.length(),blen=b.length();
  for(int i=1;i<=alen-blen;i++)
  b.push_back('0');
  for(int i=0;i<max(a.length(),b.length());i++)
  {
  if(a[i]==b[i])
  {
    c.push_back('0');
    
  }
  else
  {
    if(a[i]<b[i])
    {
      int j=i+1;
      while(a[j]<=b[j])
      j++;
      //j--;
      a[j]--;
      for(int k=j-1;k>=i+1;k--)
      a[k]+=9;
      c.push_back((a[i]-'0'+10)-(b[i]-'0')+'0');
    }
    else
    c.push_back((a[i]-'0')-(b[i]-'0')+'0'); 
  }
   //cout<<c[i]<<"  ";
  }
  int i=c.length()-1;
  while(c[i]=='0')
  i--;
  c=c.substr(0,i+1);
  rev(c);
  return c;
}
string exp(string a,unsigned long long m)
{
  if(m==1)
  return a;
  string ans=exp(a,m/2);
  if(m%2==0)
  return mul(ans,ans);
  else
  return mul(mul(ans,ans),a);
  }
string mul_fact(string s,int n)
{
  int carry=0;
  string res;
  rev(s);
  for(int i=0;i<s.length();i++)
  {
     int x=(s[i]-'0')*n+carry;
     res.push_back(x%10+'0');
     carry=x/10;
  }
  while(carry)
  {
    res.push_back(carry%10+'0');
    carry/=10;
  }
  rev(res);
  return res;
}
string fact(string s)
{
  string c="1";
  for(int i=2;i<=stoi(s);i++)
  {
    c=mul_fact(c,i);
  }
  return c;
}
void rev(string &s)
{
 int i=0,j=s.length()-1;
 while(i<j)
 {
  char t=s[i];
  s[i]=s[j];
  s[j]=t;
  i++;
  j--;
 }
 //return s;
}



string gcd(string a,string b)
{
    
    if (a == b)
        return a;
    if (a == "0")
        return b;
    if (b == "0")
        return a;
    if (isEven(a))
    {
        if (!isEven(b))
            return gcd(divby2(a),b);
        else 
            return mul("2",gcd(divby2(a),divby2(b)));
    }
 
    if (isEven(b))
        return gcd(a, divby2(b));

    if (gt(a,b))
        return gcd(divby2(sub(a,b)),b);
 
    return gcd(divby2(sub(b,a)),a);
}
int gt(string a,string b)
{
    if(a.length()>b.length())
    return 1;
    if(a.length()<b.length())
    return 0;
    
    for(int i=0;i<a.length();i++)
    {
        if(a[i]==b[i])
        continue;
        if(a[i]>b[i])
        return 1;
        else
        return 0; 
    }
    return a>b;
}

int isEven(string a)
{
  if((a[a.length()-1]-'0')%2==0)
  return 1;
  else
  return 0;
}
string divby2(string s)
{
  string r;
  int c=((s[0]-'0')%2);
  if(((s[0]-'0')/2)!=0)
  r.push_back((s[0]-'0')/2+'0');
  for(int i=1;i<s.length();i++)
  {
    r.push_back((((s[i]-'0')+(c==1?10:0))/2)+'0');
    c=((s[i]-'0')%2);
  }
  return r;
}
