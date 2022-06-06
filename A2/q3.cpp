#include<iostream>
using namespace std;
#define DTYPE int
template<class T>
class LL
{
    public:
    T data;
    LL<T> *prev;
    LL<T> *next;
    LL(T d)
    {
        data=d;
    }
};
template<class T>
class DEQUE
{
    public:
    T data;
    int size=0; 
    static T temp_init;
    LL<T> *front=new LL<T>(0);
    LL<T> *end=new LL<T>(0);
    void deque()
    {
        front->next=end;
        front->prev=NULL;
        end->prev=front;
        end->next=NULL;
    }
    void deque(int n,T x)
    {
        for(int i=0;i<n;i++)
        push_back(x);
    }
    void push_back(T x)
    {
        LL<T> *t=new LL<T>(x);
        end->prev->next=t;
        t->prev=end->prev;
        end->prev=t;
        t->next=end;
        size++;
    }
    void push_front(T x)
    {
        LL<T> *t=new LL<T>(x);
        front->next->prev=t;
        t->next=front->next;
        front->next=t;
        t->prev=front;
        size++;
    }
    void pop_back()
    {
        if(end->prev!=front)
        {
            LL<T> *t=end->prev;
            end->prev->prev->next=end;
            end->prev=end->prev->prev;
            free(t);
            size--;
        }
        else
        {
            cout<<"Deque is empty\n";
        }
    }
    void pop_front()
    {
        if(front->next!=end)
        {
            LL<T> *t=front->next;
            front->next->next->prev=front;
            front->next=front->next->next;
            free(t);
            size--;
        }
        else
        {
            cout<<"Deque is empty\n";
        }
    }
    void display()
    {
        LL<T> *t=front->next;
        while(t!=end)
        {
            cout<<t->data<<" ";
            t=t->next;
        }
        cout<<endl;
    }
    T front_()
    {
        if(front->next!=end)
        {
            return front->next->data;
        }
        else
        {
            static T temp_val;
            cout<<"Deque is empty,Returning default value:";
            return temp_val;
        }
    }
    T back()
    {
        if(end->prev!=front)
        {
            return end->prev->data;
        }
        else
        {
            static T temp_val;
            cout<<"Deque is empty,Returning default value:";
            return temp_val;
        }
    }
    int size_()
    {
        return size;
    }
    bool empty()
    {
        return size==0;
    }
    void resize(int n,T x)
    {
        if(size==n)
        return;
        else if(size>n)
        {
            int s=size;
            for(int i=0;i<s-n;i++)
            pop_back();
        }
        else
        {
            int s=size;
            for(int i=0;i<n-s;i++)
            push_back(x);
        }
    }
    void clear()
    {
        if(front->next!=end)
        {
            front->next=end;
            end->prev=front;
        }
    }
    T operator[](int n)
    {
        if(size<n+1)
        {
            cout<<"Size of deque is less that n,nth index doe not exist returning default value";
            static T temp_val;
            return temp_val;
        }
        else
        {
            if(n==0)
            return front_();
            else if(size==n+1)
            return back();
            else
            {
                LL<T> *t=front;
                while(n--)
                {
                    t=t->next;
                }
                return t->data;
            }
        }
    }
};
int main()
{
    int ch;
    DEQUE<DTYPE> dq;
    dq.deque();
    int n;
    for(int i=0;i<1000;i++)
    {
        dq.push_back(i);
        cout<<dq.back()<<" ";
    }
    cout<<endl;

    for(int i=0;i<100;i++)
    {
        dq.push_front(i*2);
        cout<<dq.front_()<<" ";
    }
    cout<<endl;

    cout<<dq.size_()<<endl;

    cout<<dq.empty()<<endl;

    dq.clear();
    dq.resize(10,4);

    cout<<dq.size_()<<endl;

    cout<<dq.empty()<<endl;

    cout<<dq.size_()<<endl;

    for(int i=0;i<dq.size_();i++){

        cout<<dq[i]<<" ";

    }
    return 0;
}

