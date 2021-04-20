//
// Created by elozsombor on 12/5/2020.
//

#ifndef NHF2STREAMS_STREAM_H
#define NHF2STREAMS_STREAM_H

#include <memory>
#include <functional>
#include <iostream>
// abstract Stream osztály
template<class T>
class Stream {
public:
    virtual T next() = 0; // visszaadja a következő értéket
    virtual bool hasNext() = 0; // visszadja, van-e következő érték
    virtual ~Stream() = default; // default destruktor
    void foreach(std::function<void(T)> fun); // ha van következő -> fun-t végrehajtja rajta
};

template<class T>
void Stream<T>::foreach(std::function<void(T)> fun) {
    while (hasNext())
    {
        fun(next());
    }
}

//"végtelen sok" egész, növekedő stream osztály
class IntStream : public Stream<int> {
private:
    int current; // aktuális érték
public:
    int next() override;
    bool hasNext() override;
    explicit IntStream(); // üres konstruktor
    explicit IntStream(int cur); // minimumot megadó konstruktor
    IntStream(const IntStream& intStream); // másoló konstruktor
    IntStream& operator=(const IntStream& intStream); // értékadás
};

//filterező stream osztály
template <class T>
class FilterStream : public Stream<T> {
private:
    std::shared_ptr<Stream<T>> stream; // a stream, amiből "átveszi" majd az értékeket (okospointerrel)
    std::function<bool(T)> filter; // predikátum
public:
    int next() override;
    bool hasNext() override;
    FilterStream(std::shared_ptr<Stream<T>> stream,
                 const std::function<bool(int)>& filter); // konstruktor, megadott értékekkel
    FilterStream(const FilterStream& filterStream); // másoló konstruktor
    FilterStream& operator=(const FilterStream& filterStream); // értékadás
};

template<class T>
int FilterStream<T>::next() {
    int val = stream->next();
    while (!filter(val))
    {
        val = stream->next();
    }
    return val;
}

template<class T>
bool FilterStream<T>::hasNext() {
    return stream->hasNext();
}

template<class T>
FilterStream<T>::FilterStream(std::shared_ptr<Stream<T>> stream, const std::function<bool(int)>& filter) {
    this->stream = stream;
    this->filter = filter;
}

template<class T>
FilterStream<T>::FilterStream(const FilterStream &filterStream) {
    stream = filterStream.stream;
    filter = filterStream.filter;
}

template<class T>
FilterStream<T>& FilterStream<T>::operator=(const FilterStream &filterStream) {
    stream = filterStream.stream;
    filter = filterStream.filter;
    return *this;
}
//értékatugró stream (note: azért nincs ennek megírva a másoló konstruktor / értékadás, mert egyszerhasználatos az osztály)
template <class T>
class SkipStream : public Stream<T>{
private:
    std::shared_ptr<Stream<T>> stream; // a stream, amiből "átveszi" majd az értékeket (okospointerrel)
    int n; // hányat ugorjon át?
public:
    explicit SkipStream(std::shared_ptr<Stream<T>> stream); // így csak egyet ugrik át
    SkipStream(std::shared_ptr<Stream<T>> stream, int n); // így n-et ugrik át
    T next();
    bool hasNext();
};

template<class T>
SkipStream<T>::SkipStream(std::shared_ptr<Stream<T>> stream) {
    this->stream = stream;
    n = 1;
    stream->next();
}

template<class T>
SkipStream<T>::SkipStream(std::shared_ptr<Stream<T>> stream, int n) {
    this->stream = stream;
    this->n = n;
    for (int i = 0; i < n; ++i) {
        stream->next();
    }
}

template<class T>
T SkipStream<T>::next() {
    return stream->next();
}

template<class T>
bool SkipStream<T>::hasNext() {
    return stream->hasNext();
}

// kivevő stream (note: mint a skipnél)
template <class T>
class TakeStream : public Stream<T>
{
private:
    int n = 0; // hányat vegyen ki?
    int taken = 0; // mennyit vett ki eddig?
    std::shared_ptr<Stream<T>> stream; // a stream, amiből "átveszi" majd az értékeket (okospointerrel)
public:
    explicit TakeStream(std::shared_ptr<Stream<T>> stream); // így 1-et vesz ki
    TakeStream(std::shared_ptr<Stream<T>> stream, int n); // így n-et vesz ki
    T next();
    bool hasNext();
};

template<class T>
TakeStream<T>::TakeStream(std::shared_ptr<Stream<T>> stream) {
    this->stream = stream;
    n = 1;
}

template<class T>
TakeStream<T>::TakeStream(std::shared_ptr<Stream<T>> stream, int n) {
    this->stream = stream;
    this->n = n;
}

template<class T>
T TakeStream<T>::next() {
        taken++;
        return stream->next();
}

template<class T>
bool TakeStream<T>::hasNext() {
    return taken < n;
}


#endif //NHF2STREAMS_STREAM_H
