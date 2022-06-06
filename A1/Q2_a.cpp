#include<iostream>
#include<unordered_map>
using namespace std;
class LRUCache {
public:
    
    class LL
    {
        public:
        int key,val;
        LL* prev;
        LL* next;
    };
    LL* head=new LL();
    LL* tail=new LL();
    int size;
    unordered_map<int,LL*> m;
    LRUCache(int capacity) {
        head->key=head->val=tail->key=tail->val=0;
        head->next=tail;
        head->prev=NULL;
        tail->prev=head;
        tail->next=NULL;
        size=capacity;
    }
    
    int get(int key) {
        if(size==0)
    	{
    	  return -1;
    	}
        if(m.find(key)==m.end())
            return -1;
        else
        {
            LL* t=m[key];
            t->prev->next=t->next;
            t->next->prev=t->prev;
            LL* t1=new LL();
            t1->key=key;
            t1->val=t->val;
            t1->prev=head;
            t1->next=head->next;
            head->next->prev=t1;
            head->next=t1;
            m[key]=t1;
            return t1->val;
        }
    }
    
    void put(int key, int value) {
    	if(size==0)
    	{
    	  cout<<"Cannot insert any value in cache as size of cache 0.\n";
    	  return;
    	}
        if(m.find(key)==m.end())
        {
            if(m.size()==size)
            {
                LL* t=tail->prev;
                t->prev->next=t->next;
                t->next->prev=t->prev;
                m.erase(t->key);
                LL* t1=new LL();
                t1->key=key;
                t1->val=value;
                t1->prev=head;
                t1->next=head->next;
                head->next->prev=t1;
                head->next=t1;
                m[key]=t1;
            }
            else
            {
                LL* t1=new LL();
                t1->key=key;
                t1->val=value;
                t1->prev=head;
                t1->next=head->next;
                head->next->prev=t1;
                head->next=t1;
                m[key]=t1;
            }
        }
        else
        {
            LL* t=m[key];
            t->prev->next=t->next;
            t->next->prev=t->prev;
            LL* t1=new LL();
            t1->key=key;
            t1->val=value;
            t1->prev=head;
            t1->next=head->next;
            head->next->prev=t1;
            head->next=t1;
            m[key]=t1;
        }
        
          cout<<"Inserted successfully,Current cache size :"<<m.size()<<"/"<<size<<endl;
    }
};
int main()
{
 int ch,k,v,n;
 LRUCache* cache;
 while(1)
 {
  cout<<"1.Create Cache\n2.Get value for key\n3.Insert(key,value)\n4.Exit\n";
  cin>>ch;
  switch(ch)
  {
   case 1: {cout<<"Enter capacity\n";
   	  cin>>n;
   	  cache=new LRUCache(n);
          cout<<"Cache created with capacity"<<n<<endl;
          break;}
   case 2: {cout<<"Enter key\n";
   	  cin>>k;
          cout<<"Value:"<<cache->get(k)<<endl;
          break;}
   case 3: {cout<<"Enter key and value to insert\n";
   	  cin>>k>>v;
   	  cache->put(k,v);
          break;}
   case 4: exit(0);
   default: {cout<<"Enter correct input\n";
           break;}
  }
 }
 return 0;
}
