//
// Created by Gabriel Spranger Rojas on 9/6/20.
//

#ifndef TESTENTRADA_LISTAENLAZADA_H
#define TESTENTRADA_LISTAENLAZADA_H

#include <iostream>

namespace LINKEDLIST {

    #define node Node<U, T>

    using namespace std;

    template<typename U, typename T>
    class Node;

    template<typename U, typename T>
    class ListaEnlazada {
        node *head;
        node *tail;
    public:
        ListaEnlazada() : head{nullptr}, tail{nullptr} {}

        node *getHead() { // O(1)
            return head;
        }

        void pushFront(node *newNode) { // O(1)
            if (!newNode) return;
            node *aux = head;
            newNode->next = head;
            if (head) {
                head->prev = newNode;
            }
            head = newNode;
            if (!aux) { // first element was inserted
                tail = newNode;
            }
        }

        void pushBack(node *newNode) { // O(1)
            if (tail) {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            } else {
                head = newNode;
                tail = newNode;
            }
        }

        U getTailKey() {
            return tail->key.first;
        }

        U getHeadKey() {
            return head->key.second;
        }

        void deleteByAddress(node *nodeToDelete) { // O(1)
            // ojo que este metodo no llama a delete
            // por lo q si se quiere borrar el nodo definitivamente
            // el usuario del API debe hacerlo manualmente
            if (!nodeToDelete) return;
            if (nodeToDelete->prev) {
                nodeToDelete->prev->next = nodeToDelete->next;
            } else {
                head = nodeToDelete->next;
            }
            if (nodeToDelete->next) {
                nodeToDelete->next->prev = nodeToDelete->prev;
            }
        }

        void deleteTail() {
            deleteByAddress(tail);
        }

        void deleteHead() {
            deleteByAddress(head);
        }

        // used for debug purposes
        void print() {
            node *it = head;
            while (it) {
                cout << it->key.first << " ";
                it = it->next;
            }
            cout << "\n";
        }

        ~ListaEnlazada() { // O(CacheMejorado.maxSize)
            node *aux1 = head;
            node *aux2 = head;
            while (aux2) {
                aux2 = aux1->next;
                delete aux1;
                aux1 = aux2;
            }
        }

    };

    template<typename U, typename T>
    class Node {
        pair<U, T> key;
        node *prev;
        node *next;
    public:
        explicit Node(pair<U, T> v) : key{v}, prev{nullptr}, next{nullptr} {}

        void updateKey(pair<U, T> newKey) {
            key = newKey;
        }

        pair<U, T> getKey() {
            return key;
        }

        template<typename V, typename W>
        friend
        class ListaEnlazada;
    };

}

#endif //TESTENTRADA_LISTAENLAZADA_H
