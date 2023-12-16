#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void updateMap(unordered_map <string, int>& pattern, string s)
{
    if(pattern.find(s) != pattern.end())
    {
        auto itr = pattern.find(s);
        itr->second++;
    }
    else
    {
        pattern[s] = 1;
    }
}

void update(unordered_map <string, int>& pattern, string ipStr)
{
    int i = 0;
    while(i < ipStr.length())
    {
        string ap;
        ap.append(ipStr, i, 2);
        updateMap(pattern, ap);
        i += 1;
    }
}

void print(unordered_map <string, int> pattern)
{
    for(auto it : pattern)
         cout << "it.first:" << it.first << "\tit.second: " << it.second << endl;
}

void show(unordered_map <string, int>& pattern, string s)
{
    if(pattern[s])
    {
        cout << pattern[s] << " ";
    }
    else
    {
        cout << 0 << " ";
    }
}

void showOutput(unordered_map<string, int>& pattern, int ip2)
{
    string ipStr2;
    while(ip2)
    {
        cin >> ipStr2;
        show(pattern, ipStr2);
        ip2--;
    }
}

int main()
{
    int ip1, ip2;
    cin >> ip1 >> ip2;
    
    string ipStr, ipStrDup;
    cin >> ipStr;
    ipStrDup = ipStr;

    unordered_map <string, int> pattern;
    update(pattern, ipStr);

    int len = ipStrDup.length();
    while(len >= 2)
    {
        string ap;
        for(int i = 0; i < len; i++)
        {
            if(i % 2 == 0)
            {
                ap.append(1, ipStrDup[i]);
            }
        }
        update(pattern, ap);
        // print(pattern);
        len = ap.length();
        ipStrDup = ap;
    }
    showOutput(pattern, ip2);

    return 0;
}
