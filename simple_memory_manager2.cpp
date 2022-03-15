#include<bits/stdc++.h>
using namespace std;

class Memory
{
    int Total_memory;
    int Available_memory;
    int Used_memory;
public:
    Memory(int total)
    {
        Total_memory=total;
        Available_memory=total;
        Used_memory=0;
    }
    int get_Total_memory()
    {
        return Total_memory;
    }
    int get_Available_memory()
    {
        return Available_memory;
    }
    int get_Used_memory()
    {
        return Used_memory;
    }
    void set_Available_memory(int aval)
    {
        Available_memory=aval;
    }
    void set_Used_memory(int used)
    {
        Used_memory=used;
    }
    bool check(int req_mem)
    {
        if(req_mem>((25*Total_memory)/100))
            return false;
        else
            return true;
    }
};


class Variable
{
    string p_name;
    string v_name;
    int start,last;
public:
    Variable(string p,string v)
    {
        p_name=p;
        v_name=v;
        start=-1;
        last=-1;
    }
    void set_start(int s)
    {
        start=s;
    }
    void set_last(int l)
    {
        last=l;
    }
    int get_start()
    {
        return start;
    }
    int get_last()
    {
        return last;
    }
    string get_process()
    {
        return p_name;
    }
    string get_variable()
    {
        return v_name;
    }
};

class Process
{
    string process_name;
    set<Variable *>var;
public:
    Process()
    {

    }
    Process(string p)
    {
        process_name=p;
    }
    string get_process_name()
    {
        return process_name;
    }
    set<Variable*> get_var()
    {
        return var;
    }
    void set_var(set<Variable*>ss)
    {
        var=ss;
    }

};





class Memory_Manager
{
    map<string, Process *>process_block;
    map<int,int>free_mem;
    map<int,int>allocate_mem;
    Memory *m;
public:
    Memory_Manager(int total)
    {
        Memory *m1=new Memory(total);
        m=m1;
        free_mem.insert({1,m->get_Total_memory()});
        //Process *process=new Process();
    }
    void Allocate_func(string p,string v, int req_mem)
    {
        if(!m->check(req_mem))
            cout<<"\nAukata se bahar mt jao ";
        else
        {
            if(process_block.find(p)!=process_block.end())
            {
                Process *temp=process_block[p];
                set<Variable *>s=temp->get_var();
                //Variable *vv=new Variable(p,v);
                bool flag=0;
                for(auto it1 :s)
                {
                    if(it1->get_variable()==v && it1->get_process()==p)
                    {
                        flag=1;
                        if(it1->get_start()==-1 && it1->get_last()==-1)
                        {
                            int flag1 =0;
                            for(auto it=free_mem.begin();it!=free_mem.end();it++)
                            {
                                if((it->second- it->first) +1>=req_mem)
                                {
                                    flag1=1;
                                    it1->set_start(it->first);
                                    it1->set_last(it->first+req_mem-1);
                                    s.insert(it1);
                                    temp->set_var(s);
                                    process_block[p]=temp;
                                    free_mem.erase(it->first);
                                    if((it->second- it->first) +1>req_mem)
                                    {
                                        free_mem.insert({it->first+req_mem,it->second});
                                    }
                                    int new_ava=m->get_Available_memory()-req_mem;
                                    m->set_Available_memory(new_ava);
                                    allocate_mem.insert({it->first,it->first+req_mem-1});
                                    break;
                                }
                            }
                            if(flag1==0)
                                cout<<"\n"<<p<<"- No contiguous space available";
                        }
                        else
                        {
                            cout<<"\n"<<p<<"- please make some space for others, memory already occupied";
                        }
                        break;
                    }
                }
                if(flag==0)
                {
                    cout<<"\n variable doesn't exists,create new";
                    Variable *new_var=new Variable(p,v);
                    int flag =0;
                    for(auto it=free_mem.begin();it!=free_mem.end();it++)
                    {
                        if((it->second- it->first) +1>=req_mem)
                        {
                            flag=1;
                            new_var->set_start(it->first);
                            new_var->set_last(it->first+req_mem-1);
                            s.insert(new_var);
                            temp->set_var(s);
                            process_block[p]=temp;
                            free_mem.erase(it->first);
                            if((it->second- it->first) +1>req_mem)
                            {
                                free_mem.insert({it->first+req_mem,it->second});
                            }
                            int new_ava=m->get_Available_memory()-req_mem;
                            m->set_Available_memory(new_ava);
                            allocate_mem.insert({it->first,it->first+req_mem-1});
                            break;
                        }
                    }
                    if(flag==0)
                        cout<<"\n"<<p<<"- No contiguous space available";
                }
            }
            else
            {
                if(m->get_Available_memory()>=req_mem)
                {
                    Process *new_prc=new Process(p);
                    Variable *new_var=new Variable(p,v);
                    set<Variable *>s;
                    int flag =0;
                    for(auto it=free_mem.begin();it!=free_mem.end();it++)
                    {
                        if((it->second- it->first) +1>=req_mem)
                        {
                            flag=1;
                            new_var->set_start(it->first);
                            new_var->set_last(it->first+req_mem-1);
                            s.insert(new_var);
                            new_prc->set_var(s);
                            process_block[p]=new_prc;
                            free_mem.erase(it->first);
                            if((it->second- it->first) +1>req_mem)
                            {
                                free_mem.insert({it->first+req_mem,it->second});
                            }
                            int new_ava=m->get_Available_memory()-req_mem;
                            m->set_Available_memory(new_ava);
                            allocate_mem.insert({it->first,it->first+req_mem-1});
                            break;
                        }
                    }
                    if(flag==0)
                        cout<<"\n"<<p<<"- No contiguous space available";
                }
                else
                    cout<<"\n"<<p<<"- No more space left for you, please make some space";
            }
        }

    }
    void free_func(string p, string v)
    {
        if(process_block.find(p)==process_block.end())
        {
            cout<<"\n"<<p<<"- Not possible,process does not exist";
            return;
        }
        else
        {
            Process *temp=process_block[p];
            set<Variable *>s;
            s=temp->get_var();
            bool flag=0;
            for(auto it :s)
            {
                if(it->get_variable()==v)
                {
                    flag=1;
                    allocate_mem.erase(it->get_start());
                    free_mem.insert({it->get_start(),it->get_last()});
                    int new_ava=m->get_Available_memory()+(it->get_last()-it->get_start()+1);
                    m->set_Available_memory(new_ava);
                    it->set_start(-1);
                    it->set_last(-1);
                    break;
                }
            }
            if(flag=0)
                cout<<"\nNot possible, Variable doesn't exists in this process : "<<p;
        }
    }

    void kill_func(string p)
    {
        if(process_block.find(p)==process_block.end())
        {
            cout<<"\n"<<p<<"- Cannot be killed,process does not exist";
            return;
        }
        else
        {
            Process *temp=process_block[p];
            set<Variable *>s;
            s=temp->get_var();
            for(auto it :s)
            {
                allocate_mem.erase(it->get_start());
                free_mem.insert({it->get_start(),it->get_last()});
                int new_ava=m->get_Available_memory()+(it->get_last()-it->get_start()+1);
                m->set_Available_memory(new_ava);
            }
            process_block.erase(p);
        }
    }

    void inspect_func(string p)
    {
        cout<<"\n----------------------------------------------inspect start-------------------------------------------";
        if(process_block.find(p)==process_block.end())
        {
            cout<<"\n"<<p<<"- process does not exist";
            return;
        }
        else
        {
            Process *temp=process_block[p];
            cout<<"\nProcess_name : "<<temp->get_process_name();
            set<Variable *>s;
            s=temp->get_var();
            //bool flag=0;
            for(auto it :s)
            {
                cout<<"\nVariable: "<<it->get_variable()<<" -> "<<it->get_start()<<" to "<<it->get_last();
            }
        }
         cout<<"\n----------------------------------------------inspect end---------------------------------------------";
    }
};


int main()
{
    int t,req_mem,storage;
    string p,vv;
    string req_type;
    cout<<"enter the total memory storage present: ";
    cin>>storage;
    Memory_Manager *Mem=new Memory_Manager(storage);
    cout<<"enter number of test cases- ";
    cin>>t;
    while(t--)
    {
        cout<<"\nEnter request_ type: ";
        cin>>req_type;
        if(req_type=="Allocate")
        {
            cout<<"\nwrite process name: ";
            cin>>p;
            cout<<"\nEnter variable name: ";
            cin>>vv;
            cout<<"\nEnter required memory: ";
            cin>> req_mem;

            Mem->Allocate_func(p,vv,req_mem);
            Mem->inspect_func(p);
        }
        else if(req_type=="Free")
        {
            cout<<"\nwrite process name: ";
            cin>>p;
            cout<<"\nEnter variable name: ";
            cin>>vv;
            Mem->free_func(p,vv);
            Mem->inspect_func(p);

        }
        else if(req_type=="Kill")
        {
            cout<<"\nwrite process name: ";
            cin>>p;
            Mem->kill_func(p);
            Mem->inspect_func(p);
        }
        else
        {
            cout<<"\nwrite process name: ";
            cin>>p;
            Mem->inspect_func(p);
        }
    }
    return 0;
}
