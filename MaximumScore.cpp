#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <bits/stdc++.h>

using namespace std;

void showVp(vector<pair <int, int>> vp);
void showV(vector<int> v);
void accuV(pair<int, int> fp, vector<int> v);
    
void finalVp(vector<pair <int, int>> vp1, vector<pair <int, int>> vp2, vector<pair <int, int>>& fvm, vector<int> ng)
{
    vector<pair<int, int>> dummyV(vp1.size() + vp2.size());
    merge(vp1.begin(), vp1.end(), vp2.begin(), vp2.end(), dummyV.begin());

    if(ng.size() > 0)
    {
    for(auto n : ng)
    {
        vector<pair<int, int>> tmpV;
        for(auto itr : dummyV)
        {
            if((n != itr.first) and (n != itr.second))
            {
                tmpV.push_back(make_pair(itr.first, itr.second));
            }
        }
        // dummyV = tmpV;
    }
    }
    fvm = dummyV;
}

void showVp(vector<pair <int, int>> vp)
{
    for(auto itr : vp)
        cout << "first: " << itr.first << " second: " << itr.second << endl;
}

void showV(vector<int> vp)
{
    for(auto it : vp)
        cout << "first: " << it << endl;
}

void findVp(string ipStrDup, string sstr, vector<pair<int, int>>& vm)
{
    size_t found = ipStrDup.find(sstr);
    while (found != string::npos) 
    {
        vm.push_back(make_pair(found, found + sstr.length() - 1));
        found = ipStrDup.find(sstr, found + 1);
    }
}

int main()
{
    uint64_t i;
    cin >> i;

    string ipStr, ipStrDup;
    cin >> ipStr;
    
    std::vector<int> v, ng;
    for(int j = 0; j < i; j++)
    {
        int k;
        cin >> k;
        v.push_back(k);
        // cout << "v.size(): " << v.size() << "k: " << k << endl;
        if(k < 0)
            ng.push_back(j);
    }
    
    string sstr1, sstr2;
    cin >> sstr1 >> sstr2;
    // cout << "sstr1: " << sstr1 << endl << "sstr2: " << sstr2 << endl;

    vector<pair<int, int>> vp1, vp2;
    ipStrDup = ipStr;

    findVp(ipStrDup, sstr1, vp1);
    // showVp(vp1);

    findVp(ipStrDup, sstr2, vp2);
    // showVp(vp2);
    
    vector<pair<int, int>> fvp(vp1.size() + vp2.size());
    finalVp(vp1, vp2, fvp, ng);
    // showVp(fvp);
    
    uint64_t sum = 0;
    for_each(
        fvp.begin(), 
        fvp.end(), 
        [&](auto vp)
        {
            /*sum += accumulate(
                v.begin() + vp.first,
                v.begin() + vp.second+1,
                0);*/
            for_each(
                v.begin() + vp.first,
                v.begin() + vp.second+1,
                [&](auto p)
                {
                    cout << "p: " << p << endl;
                    sum += p;
                });
        }
    );
    cout << sum << endl;
}
