//
// Created by elozsombor on 12/5/2020.
//

#include "stream.h"

int IntStream::next() {
    return current++;

}

bool IntStream::hasNext() {
    return true;
}

IntStream::IntStream() {
    current = 0;
}

IntStream::IntStream(int cur) {
    current = cur;
}

IntStream::IntStream(const IntStream &intStream) {
    current = intStream.current;
}

IntStream& IntStream::operator=(const IntStream &intStream) {
    current = intStream.current;
    return *this;
}
