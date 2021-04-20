//
// Created by elozsombor on 12/6/2020.
//

#ifndef NHF2STREAMS_LINKEDLIST_H
#define NHF2STREAMS_LINKEDLIST_H


#include <memory>
// egy listaelem osztálya
template <class T>
struct Node
{
    T data; // adat
    std::unique_ptr<Node<T>> next; // okospointer a következő elemre
    explicit Node(T data) : data(data), next(nullptr){}; // konstruktor
    T getData(); // visszaadja az adatot
    Node<T>* getNext(); // visszaad egy sima pointert a következő elemére
};

template<class T>
T Node<T>::getData() {
    return data;
}

template<class T>
Node<T>* Node<T>::getNext() {
    return next.get();
}

// a láncolt lista osztály
template<class T>
class LinkedList {
private:
    std::unique_ptr<Node<T>> first; // a lista
public:
    LinkedList() : first(nullptr){}; // üres konstruktor
    void add(const T& data); // hozzáfűz a végére egy elemet
    int size(); // a mérete a listának
    void removeif(std::function<bool(T)> filter); // kifilterezi a listát filter szerint
    Node<T>* getFirst(); // visszaadja a listát
};


template<class T>
void LinkedList<T>::add(const T &data) {
    if (first == nullptr)
    {
        first = std::make_unique<Node<T>>(data);
    } else
    {
        auto* last = first.get();
        for (; last->next != nullptr; last = last->next.get()) {
        }
        last->next = std::make_unique<Node<T>>(data);
    }
}

template<class T>
int LinkedList<T>::size() {
    int i = 0;
    auto* last = first.get();
    for (; last->next != nullptr; last = last->next.get()) {
        i++;
    }
    return i;
}

template<class T>
void LinkedList<T>::removeif(std::function<bool(T)> filter) {
    if (first == nullptr)
        return;
    if (filter(first->data))
    {

        first = std::move(first->next);

    }
    auto* i = first->next.get();
    for (; i->next != nullptr; i = i->next.get()) {
        if (filter(i->next->data))
        {
            i->next = std::move(i->next->next);
        }
        if (i->next == nullptr)
            break;
    }
}

template<class T>
Node<T>* LinkedList<T>::getFirst() {
    return first.get();
}


#endif //NHF2STREAMS_LINKEDLIST_H
