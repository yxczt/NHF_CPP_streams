#include <iostream>
#include "stream.h"
#include "era.h"
#include "linkedlist.h"


bool isPrime(int temp) {  // visszaadja, hogy prím-e a temp
    for (int i = 2; i <= temp/2; i++)
    {
        if (temp % i == 0)
            return false;
    }
    return true;
}

int getPrime(int no)  // visszaadja a no-ik prímet (korlátos)
{
    auto list = LinkedList<int>(); // láncolt lista
    for (int i = 2; i < 10000; ++i) {
        list.add(i);
    }
    int primeno = 0;
    auto element = list.getFirst();
    if (isPrime(element->getData()))
    {
        primeno++;
    }
    while (primeno != no)
    {
        element = element->getNext();
        if (isPrime(element->getData()))
        {
            primeno++;
        }
    }
    return element->getData();
}



int getPrimeEra(int no) // visszaadja a no-ik prímet, Erasztothenész szitájával (korlátos)
{

    auto list = LinkedList<int>();
    for (int i = 2; i < 10000; ++i) {
        list.add(i);
    }
    for (int i = 2; i < 10000 / 2 + 1; ++i) {
        list.removeif([i] (int x) {return x % i == 0 && x != i;});
    }
    if (no == 1) return list.getFirst()->getData();
    auto element = list.getFirst();
    for (int i = 0; i < no - 1; ++i) {
        element = element->getNext();
    }
    return element->getData();
}


int main() {
        std::cout << getPrime(1000) << std::endl; // 1000. prím -> 7919
        std::cout << getPrimeEra(1000) << std::endl; // 1000. prím

    // 1000. prím stream-mel
    IntStream intStream = IntStream(2); // "végtelen sok 2-nél nagyobb szám"
    FilterStream<int> filter = FilterStream<int>(std::make_shared<IntStream>(intStream), [] (int x) {
        for (int i = 2; i <= x/2; i++)
        {
            if (x % i == 0)
                return false;
        }
        return true;
    }); // lambdával filterez a prímekre
    SkipStream<int> skip = SkipStream<int>(std::make_shared<FilterStream<int>>(filter), 999); // átugrik 999 értéket
    TakeStream<int> take = TakeStream<int>(std::make_shared<SkipStream<int>>(skip), 1); // 1-et kivesz
    take.foreach([] (int i) {std::cout << i << std::endl;}); // kiír
    // 1000. prím stream-mel (Eratoszthenész)
    Era era = Era(); // Eratoszthenész szitája
    SkipStream<int> skipera = SkipStream<int>(std::make_shared<Era>(era), 999); // átugrik 999 értéket
    TakeStream<int> takeera = TakeStream<int>(std::make_shared<SkipStream<int>>(skipera), 1); // 1-et kivesz
    takeera.foreach([] (int i) {std::cout << i << std::endl;}); // kiír
    return 0;
}
