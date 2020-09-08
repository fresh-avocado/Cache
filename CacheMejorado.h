//
// Created by Gabriel Spranger Rojas on 9/6/20.
//

#ifndef TESTENTRADA_CACHEMEJORADO_H
#define TESTENTRADA_CACHEMEJORADO_H

#include <string>
#include <unordered_map>
#include <optional>
#include "ListaEnlazada.h"

namespace CACHE {

    enum ReplacementPolicy {
        LRU,
        FIFO
    };

    template<ReplacementPolicy replacementPolicy, typename U, typename T>
    class CacheMejorado {

    };

/// LRU

    template<typename U, typename T>
    class CacheMejorado<LRU, U, T> {
        int maxSize;
        unordered_map<U, Node<U, T> *> cache;
        ListaEnlazada<U, T> *keyValuePairs;
    public:
        explicit CacheMejorado(int n) : maxSize{n} {
            cache = {};
            keyValuePairs = new ListaEnlazada<U, T>();
        }

        void insertKeyValuePair(U key, T value) {
            if (cache.find(key) != cache.end()) { // O(1), linear if collisions exist
                cache[key]->updateKey(make_pair(key, value)); // O(1)
            } else {
                if (cache.size() < maxSize) { // no need to evict
                    auto *newNode = new Node(make_pair(key, value)); // O(1)
                    cache[key] = newNode; // O(1)
                    keyValuePairs->pushFront(newNode); // O(1)
                } else { // need to evict LRU
                    cache.erase(keyValuePairs->getTailKey()); // delete from hash, O(1)
                    keyValuePairs->deleteTail(); // delete from linked list, O(1)
                    auto *newNode = new Node(make_pair(key, value)); // O(1)
                    cache[key] = newNode; // O(1)
                    keyValuePairs->pushFront(newNode); // O(1)
                }
            }
        }

        optional<T> getValueFromKey(U key) {
            auto keyValue = cache.find(key); // O(1), linear if collisions exist
            if (keyValue != cache.end()) { // key exists
                keyValuePairs->deleteByAddress(keyValue->second); // O(1)
                keyValuePairs->pushFront(keyValue->second); // O(1)
                return keyValue->second->getKey().second; // O(1)
            } else { // key does not exist
                return nullopt;
            }
        }

        optional<U> getMostRecentKey() {
            if (keyValuePairs->getHead()) { // O(1)
                return keyValuePairs->getHead()->getKey().first; // O(1)
            } else {
                return nullopt;
            }
        }

        ~CacheMejorado() {
            delete keyValuePairs;
        }
    };

/// FIFO

    template<typename U, typename T>
    class CacheMejorado<FIFO, U, T> {
        int maxSize;
        unordered_map<U, Node<U, T> *> cache;
        ListaEnlazada<U, T> *keyValuePairs;
    public:
        explicit CacheMejorado(int n) : maxSize{n} {
            cache = {};
            keyValuePairs = new ListaEnlazada<U, T>();
        }

        void insertKeyValuePair(U key, T value) {
            if (cache.find(key) != cache.end()) { // O(1), linear if collisions exist
                cache[key]->updateKey(make_pair(key, value)); // O(1)
            } else {
                if (cache.size() < maxSize) { // no need to evict
                    auto *newNode = new Node(make_pair(key, value)); // O(1)
                    cache[key] = newNode; // O(1)
                    keyValuePairs->pushBack(newNode); // O(1)
                } else { // need to evict LRU
                    cache.erase(keyValuePairs->getHeadKey()); // delete from hash, O(1)
                    keyValuePairs->deleteHead(); // delete from linked list, O(1)
                    auto *newNode = new Node(make_pair(key, value)); // O(1)
                    cache[key] = newNode; // O(1)
                    keyValuePairs->pushBack(newNode); // O(1)
                }
            }
        }

        optional<T> getValueFromKey(U key) {
            auto keyValue = cache.find(key); // O(1), linear if collisions exist
            if (keyValue != cache.end()) { // key exists
                // don't update linked list order because we are using FIFO
                // if we update the position, we would be applying LRU
                return keyValue->second->getKey().second; // O(1)
            } else { // key does not exist
                return nullopt;
            }
        }

        optional<U> getMostRecentKey() { // O(1), (because we are using FIFO, it's basically the last inserted key)
            if (keyValuePairs->getTail()) { // O(1)
                return keyValuePairs->getTail()->getKey().first; // O(1)
            } else {
                return nullopt;
            }
        }

        ~CacheMejorado() {
            delete keyValuePairs;
        }
    };

}

#endif //TESTENTRADA_CACHEMEJORADO_H
