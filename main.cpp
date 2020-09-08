#include "CacheMejorado.h"

using namespace std;
// using namespace CACHE;

int main() {

//  CACHE::CacheMejorado<CACHE::FIFO, string, int> lruCache(3);
    // int porque nuestro cache tendra keys de tipo string, guardara int's como values y usara el policy de LRU:
    CACHE::CacheMejorado<CACHE::LRU, string, int> lruCache(3);

    cout << lruCache.getMostRecentKey().value_or("No recent key") << endl; //

    // testear operaciones
    lruCache.insertKeyValuePair("b", 2);
    lruCache.insertKeyValuePair("a", 1);
    lruCache.insertKeyValuePair("c", 3);

    cout << lruCache.getMostRecentKey().value_or("No recent key") << endl; // c

    cout << lruCache.getValueFromKey("a").value_or(INT_MIN) << endl; // 1

    cout << lruCache.getMostRecentKey().value_or("No recent key") << endl; // a

    lruCache.insertKeyValuePair("d", 4);

    cout << lruCache.getMostRecentKey().value_or("No recent key") << endl; // d

    cout << lruCache.getValueFromKey("b").value_or(INT_MIN) << endl;

    lruCache.insertKeyValuePair("a", 5);

    cout << lruCache.getValueFromKey("a").value_or(INT_MIN) << endl; // 5


////    Probando la implementacion de la lista enlazada
//    ListaEnlazada<string, int> listaEnlazada;
//
//    auto* node1 = new Node<string, int>(make_pair("a", 1));
//    listaEnlazada.pushBack(node1);
//    auto* node2 = new Node<string, int>(make_pair("b", 2));
//    listaEnlazada.pushBack(node2);
//    auto* node3 = new Node<string, int>(make_pair("c", 3));
//    listaEnlazada.pushFront(node3);
//    auto* node4 = new Node<string, int>(make_pair("d", 4));
//    listaEnlazada.pushBack(node4);
//    auto* node5 = new Node<string, int>(make_pair("e", 5));
//    listaEnlazada.pushBack(node5);
//
//    listaEnlazada.print();
//    listaEnlazada.deleteByAddress(node3);
//    listaEnlazada.print();
//    listaEnlazada.pushFront(node3);
//    listaEnlazada.print();

    return 0;
}