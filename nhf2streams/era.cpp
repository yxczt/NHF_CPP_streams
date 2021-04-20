//
// Created by elozsombor on 12/6/2020.
//

#include "era.h"

int Era::next() {
    int next = stream->next();
    // plusz "szita" (filter), minden egyes lépésnél
    FilterStream<int> filter = FilterStream<int>(std::make_shared<FilterStream<int>>(*stream), [next] (int x) {return x % next != 0;});
    std::shared_ptr<FilterStream<int>> filterp = std::make_shared<FilterStream<int>>(filter);
    stream.swap(filterp);
    return next;
}

bool Era::hasNext() {
    return true;
}

Era::Era() {
    IntStream intStream = IntStream(2); // az alapstream
    FilterStream<int> filter = FilterStream<int>(std::make_shared<IntStream>(intStream), [] (int x) {return true;}); // szükséges, hogy lehessen rá pakolni még filtert
    stream = std::make_shared<FilterStream<int>>(filter);
}
