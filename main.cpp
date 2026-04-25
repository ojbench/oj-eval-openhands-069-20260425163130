#include <bits/stdc++.h>
#include "template.h"
using namespace std;
using namespace sjtu;

static MemoryBlock* find_by_address(int addr){
    for(MemoryBlock* cur=head; cur; cur=cur->next){
        if(cur->address==addr) return cur;
    }
    return nullptr;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    resetMemory();

    vector<MemoryBlock*> ptrs; ptrs.reserve(100000);

    // Supported commands (flexible, order-agnostic, processed until EOF):
    // 1 sz | alloc sz | sz            -> allocate and print address or -1
    // 2 id | free id                  -> deallocate by handle id (1-based)
    // freeaddr addr                   -> deallocate by starting address

    string tok;
    while (true){
        if(!(cin>>tok)) break;
        if(tok=="1"||tok=="alloc"){
            int sz; if(!(cin>>sz)) break;
            MemoryBlock* p=allocate(sz);
            ptrs.push_back(p);
            if(p) cout<<p->address<<"\n"; else cout<<-1<<"\n";
        }else if(tok=="2"||tok=="free"){
            int id; if(!(cin>>id)) break;
            if(1<=id && id<= (int)ptrs.size() && ptrs[id-1]){
                deallocate(ptrs[id-1]);
            }
        }else if(tok=="freeaddr"){
            int addr; if(!(cin>>addr)) break;
            MemoryBlock* p=find_by_address(addr);
            if(p) deallocate(p);
        }else{
            // treat token as size for allocation
            int sz;
            try { sz = stoi(tok); }
            catch(...){ continue; }
            MemoryBlock* p=allocate(sz);
            ptrs.push_back(p);
            if(p) cout<<p->address<<"\n"; else cout<<-1<<"\n";
        }
    }
    return 0;
}
