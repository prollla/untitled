#include <algorithm>
#include <QMessageBox>
#include "lab6.h"


struct compare {
    bool operator()(const pair<string, int>& value,
                    const string& key)
    {
        return (value.first < key);
    }
    bool operator()(const string& key,
                    const pair<string, int>& value)
    {
        return (key < value.first);
    }
};

string findRandomSynonym(const string& orig, const vector<pair<string, int>>& g) {
    //ищем слово в глоссарии
    //auto it = std::lower_bound(g.begin(), g.end(), orig, compare());
    auto it = g.begin();
    while(it != g.end()) {
        if(it -> first == orig) {
            break;
        }
        ++it;
    }
    if(it == g.end()) {
        return orig;
    }
    vector<string> sy;
    for(size_t k = 0; k < g.size(); k++ ) {
        if(g[k].second != it -> second) {
            continue;
        }
        if(g[k].first == it -> first) {
            continue;
        }
        sy.push_back(g[k].first);
    }
    return sy[rand()%sy.size()];
}
