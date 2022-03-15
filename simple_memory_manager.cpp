#include<bits/stdc++.h>
using namespace std;
int total_mem=100;

map<int,int>free_mem;
map<int,int>allocate_mem;
map<string,pair<int,int>>process;

void allocate_func(string p, int req_mem)
{
    auto x=process[p];
    if(process.find(p)!=process.end()&& x.first!=0 && x.second!=0)
    {
        cout<<"\n"<<p<<"- please make some space for others";
    }
    else
    {

        if(total_mem>=req_mem)
        {
            int flag =0;
            for(auto it=free_mem.begin();it!=free_mem.end();it++)
            {
                //cout<<it->first <<" && "<<it->second;
                if((it->second- it->first) +1>=req_mem)
                {

                    flag=1;
                    process[p]={it->first,it->first+req_mem-1};
                   // process.insert({p,{it->first,it->first+req_mem-1}});
                   // cout<<"\np-"<<process[p].first<<"--"<<process[p].second;
                    free_mem.erase(it->first);
                    if((it->second- it->first) +1>req_mem)
                    {
                        free_mem.insert({it->first+req_mem,it->second});
                    }
                    total_mem=total_mem-req_mem;
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

void free_func(string p)
{
    if(process.find(p)==process.end())
    {
        cout<<"\n"<<p<<"- process does not exist";
        return;
    }
    else
    {
        auto x=process[p];
        allocate_mem.erase(x.first);
        free_mem.insert({x.first,x.second});
        total_mem=total_mem +(x.second-x.first +1);
        process[p]={0,0};

    }
}

void kill_func(string p)
{
    if(process.find(p)==process.end())
    {
        cout<<"\n"<<p<<"- process does not exist";
        return;
    }
    else
    {
        auto x=process[p];
        allocate_mem.erase(x.first);
        free_mem.insert({x.first,x.second});
        total_mem=total_mem +(x.second-x.first +1);
        process.erase(p);

    }
}

void inspect_func(string p)
{
    if(process.find(p)==process.end())
    {
        cout<<"\n"<<p<<"- process does not exist";
        return;
    }
    else
    {
        auto x=process[p];
        cout<<"\nAvailable space of process "<<p<<"-> "<<x.first <<"-"<<x.second;
    }
}

int main()
{
    int t,req_mem;
    string p;
    string req_type;
    cout<<"enter number of test cases- ";
    cin>>t;
    free_mem.insert({1,100});
    while(t--)
    {
        cout<<"\nwrite process name: ";
        cin>>p;
        cout<<"\nEnter request_ type: ";
        cin>>req_type;
        cout<<"\nEnter required memory: ";
        cin>> req_mem;
        if(req_type=="Allocate")
        {
            if(req_mem>25)
                cout<<"\nAsk in your limit";
            else
            {
                    allocate_func(p,req_mem);
                    inspect_func(p);
            }
        }
        else if(req_type=="Free")
        {
            free_func(p);
        }
        else if(req_type=="Kill")
        {
            kill_func(p);
        }
        else
        {
            inspect_func(p);
        }
    }
    return 0;
}
