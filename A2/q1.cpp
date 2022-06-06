#include<iostream>
using namespace std;
#define DTYPE int
template<typename t>
class node
{
    public:
    t data;
    int height;
    node<t> *left;
    node<t>* right;
    int freq;
};
template<typename T>
class AVL
{
    public:
    long double prev=-1;
    T lowerbound_val;
    T upperbound_val;
    T kth;
    int numsinrange=0;
    int count=0;
    node<T>* root=NULL;
    node<T>* createNode(T data)
    {
    node<T>* n=new node<T>();
    n->data=data;
    n->freq=n->height=1;
    n->left=n->right=NULL;
    return n;
    }
int max(int a,int b)
{
    return a>b?a:b;
}
void inorder(node<T>* n)
{
    if(n==NULL)
    return;
    inorder(n->left);
    cout<<"("<<n->data<<":"<<n->freq<<") ";
    inorder(n->right);
}
void preorder(node<T>* n)
{
    if(n==NULL)
    return;
    cout<<"("<<n->data<<":"<<n->freq<<") ";
    preorder(n->left);
    preorder(n->right);
}

int getH(node<T>* n)
{
    return n!=NULL?n->height:0;
}
int getBF(node<T>* n)
{
    return n!=NULL?getH(n->left)-getH(n->right):0;
}
node<T>* L_Rotation(node<T>* n)
{
    node<T>* R=n->right;
    node<T>* R_L=n->right->left;
    n->right=R->left;
    R->left=n;
    n->height=max(getH(n->left),getH(n->right))+1;
    R->height=max(getH(R->left),getH(R->right))+1;
    return R;
}
node<T>* R_Rotation(node<T>* n)
{
    node<T>* L=n->left;
    node<T>* L_R=n->left->right;
    n->left=L->right;
    L->right=n;
    n->height=max(getH(n->left),getH(n->right))+1;
    L->height=max(getH(L->left),getH(L->right))+1;
    return L;
}

node<T>* insertion(node<T>* n,T val)
{
    if(n==NULL)
    {
        node<T>* t=createNode(val);
       //cout<<"data in insertion fun:"<<t->data<<endl;
        return t;
    }
    else
    if(n->data>val)
    {
        n->left=insertion(n->left,val);
    }
    else
    if(n->data<val)
    {
        n->right=insertion(n->right,val);
    }
    else
    {
        n->freq++;
        return n;
    }
    n->height=1+(getH(n->left)+getH(n->right));
    int BF=getBF(n);
    //LR
    if(BF>1&&val>n->left->data)
    {
        n->left=L_Rotation(n->left);
        return R_Rotation(n);
    }
    //LL
    if(BF>1&&val<n->left->data)
    {
        
        return R_Rotation(n); 
    }
    //RL
    if(BF<-1&&n->right->data>val)
    {
        n->right=R_Rotation(n->right);
        return L_Rotation(n);
    }
    //RR
    if(BF<-1&&val>n->right->data)
    {
        return L_Rotation(n);
    }
    return n;
}

node<T>* deletion(node<T>* n,T val)
{
    if(n==NULL)
    return NULL;
    if(n->data>val)
    n->left=deletion(n->left,val);
    else if(n->data<val)
    n->right=deletion(n->right,val);
    else
    {
        
        if(n->freq>1)
        {
          n->freq-=1;//available multiple time,just decrease occurence by 1
          return n;
        }
        else //single occurence,need to remove the node from tree
        {
            if(n->left==NULL&&n->right==NULL)
            n=NULL;
            else if(n->left==NULL&&n->right!=NULL)
            {
            n=n->right;
            /*
              node<T>* temp=n->right;
              n=temp;
              free(temp);
              */
            }
            else if(n->right==NULL&&n->left!=NULL)
            {
            n=n->left;
            /*cout<<n->left->data<<" ::"<<endl;
              node<T>* temp=n->left;
              n=temp;
              free(temp);
              cout<<n->data<<endl;              
              */
            }
            else
            {
              node<T>* temp=n->right;
              while(temp->left!=NULL)
              temp=temp->left;
              n->data=temp->data;
              n->freq=temp->freq;
              n->right=deletion(n->right,n->data);
            }
        }
        
    }
    if(n==NULL)
    return NULL;
    
    n->height=1+max(getH(n->left),getH(n->right));
    int BF=getBF(n);
    int BF_L=getBF(n->left);
    int BF_R=getBF(n->right);
    if(BF>1&&BF_L<0)
    {
      n->left=L_Rotation(n->left);
      return R_Rotation(n);
    }
    if(BF>1&&BF_L>=0)
    {
      return R_Rotation(n);
    }
    if(BF<-1&&BF_R>0)
    {
      n->right=R_Rotation(n->right);
      return L_Rotation(n);
    }
    if(BF<-1&&BF_R<=0)
    {
      return L_Rotation(n);
    }
    return n;  
    
}

node<T>* find(node<T>* n,T val)
{
    if(n==NULL)
    return NULL;
    if(n->data==val)
    return n;
    else
    if(n->data>val)
    return find(n->left,val);
    else
    return find(n->right,val);
}
T abs(T a,T b)
{
    if(a-b>0)
    return a-b;
    else
    return b-a;    
}


long double closestelement(node<T>* n, long double val)
    {   
        if(n->data==val)
        return val;
        else
        if(n->data>val)
        {
            if(n->left)
            {
                prev=n->data;
                return closestelement(n->left,val);
            }
            else
            if(prev==-1)
            {
                return n->data;
            }
            else
            {
               return abs(prev,val)<abs(n->data,val)?prev:n->data;
            }
            
        }
        else
        {
            if(n->right)
            {
                prev=n->data;
                return closestelement(n->right,val);
            }
            else
            if(prev==-1)
            {
                return n->data;
            }
            else
            {
               return abs(prev,val)<abs(n->data,val)?prev:n->data;
            }
        }
    }
    //DUMMY Function
    string closestelement(node<string>* n,string s)
    {
        return "-1(Closest element is not supported for string)";
    }
    void lowerbound(node<T>* n,int val)
    {
        if(n==NULL)
        return;
        if(n->data>=val)
        {
            lowerbound_val=n->data;
            lowerbound(n->left,val);
        }
        else
        lowerbound(n->right,val);
    }
    void upperbound(node<T>* n,int val)
    {
        if(n==NULL)
        return;
        if(n->data>val)
        {
            upperbound_val=n->data;
            upperbound(n->left,val);
        }
        else
        upperbound(n->right,val);
    }
    void numinrange(node<T> *n,T v1,T v2)
    {
    	if(n==NULL)
    	return;
        if(n->data>=v1&&n->data<=v2)
        numsinrange+=n->freq;
        numinrange(n->left,v1,v2);
        numinrange(n->right,v1,v2);
    }
    /*
    T kthfromR(node<T>* n,int k)
    {
        if(n==NULL)
        return -1;
        kthfromR(n->right,k);
        count++;
        if(count==k)
        return n->data;
        kthfromR(n->left,k);
        
    }
    */
    void kthlargest(node<T>* n,int k)
    {
        if(n==NULL)
        return;
        kthlargest(n->right,k);
        int f=n->freq;
        while(f--)
        {
        count++;
        if(count==k)
        kth=n->data;
        }
        kthlargest(n->left,k);
        
    }
    /*
    T kthlargest(node<T>* n,int k)
    {
    if(k<n-k)
      return kthfromR(n,k);
      else
      return kthfromL(n,k);
      
    }
    */
};
int main()
{
    int ch;
    AVL<DTYPE> t;
    while(1)
    {
        int ch;
        DTYPE val,val1,val2;
        //cout<<"Enter the operation\n1.Insert\n2.Delete\n3.Search\n4.Occurenceof element\n5.Lower bound\n6.Upper bound\n7.CLosest element to given value\n8.Kth largest element\n9.Count the number of elements in the tree whose values fall into a given range.\n10.exit\n11.Display\n";
        cin>>ch;
        switch(ch)
        {
            case 1:
                cin>>val;
                t.root=t.insertion(t.root,val);
                //cout<<"after insertion root data:"<<tree->data<<endl;
                break;
            case 2:
                cin>>val;
                t.root=t.deletion(t.root,val);
                break;
            case 3:
                cin>>val;
                
                if(t.find(t.root,val))
                cout<<val<<" found\n";
                else
                cout<<"Not found\n";
                
                break;
            case 4:
                cin>>val;
                //node<DTYPE> *res=t.find(t.root,val);
                if(t.find(t.root,val))
                cout<<val<<" found,Occurence :"<<t.find(t.root,val)->freq<<endl;
                else
                cout<<"Not found\n";
                break;
            case 5:
                cin>>val;
                t.lowerbound(t.root,val);
                cout<<"Lower bound:"<<t.lowerbound_val<<endl;
                break;
            case 6:
                cin>>val;
                t.upperbound(t.root,val);
                cout<<"Upper bound:"<<t.upperbound_val<<endl;
                break;
                
            case 7:
                //long double val_;
                cin>>val;
                cout<<"Closest Element:"<<t.closestelement(t.root,val);
                break;
            case 8:
                int k;
                cin>>k;
                t.count=0;
                t.kthlargest(t.root,k);
                cout<<t.kth<<endl;
                break;
            case 9:
                cin>>val1>>val2;
                t.numsinrange=0;
                t.numinrange(t.root,val1,val2);
                cout<<t.numsinrange<<endl;
                break;
            case 10:
                exit(0);
            case 11:
            cout<<"Inorder:";
                t.inorder(t.root);
                cout<<endl<<"Preorder:";
                t.preorder(t.root);
                cout<<endl;
                break;
            default:cout<<"Choose correct option\n";      
        }
    }
    return 0;
}

