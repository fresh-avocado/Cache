//
// Created by Gabriel Spranger Rojas on 9/5/20.
//

#ifndef TESTENTRADA_LRUCACHE_H
#define TESTENTRADA_LRUCACHE_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class LRUCache {
private:
    int maxSize;

    unordered_map<string, int> cache;
    pair<string, int>* lru;
    std::unordered_map<std::string,int>::const_iterator lastInserted;
    vector<string> keys;
public:
    explicit LRUCache(int n): maxSize{n}, lru{nullptr} { cache = {}; }

    void insertKeyValuePair(const string& key, int value) {
        if (cache.find(key) != cache.end()) { // O(1)
            cache[key] = value; // O(1)
        } else {
            if (cache.size() < maxSize) {
                cache[key] = value; // O(1)
            } else {
                // evict
                if (!keys.empty()) {
                    cache.erase(*keys.begin()); // O(1)
                    keys.erase(keys.begin()); // O(1)
                }
                cache[key] = value; // O(1)
            }
            lastInserted = cache.find(key); // O(1)
            keys.push_back(key); // O(1) (amortizado)
        }
    }

    void getValueFromKey(const string& key) {
        if (cache.find(key) != cache.end()) { // O(1)
            lastInserted = cache.find(key); // O(1)
            auto justUsed = std::find(keys.begin(), keys.end(), key); // O(maxSize)
            auto aux = *(keys.end()-1); // O(1)
            *(keys.end()-1) = *justUsed; // O(1)
            *justUsed = aux; // O(1)
            cout << cache[key] << "\n"; // O(1)
        } else {
            cout << "None\n";
        }
    }

    string getMostRecentKey() {
        return lastInserted->first; // O(1)
    }
};


#endif //TESTENTRADA_LRUCACHE_H
