//
// Created by elozsombor on 12/6/2020.
//

#ifndef NHF2STREAMS_ERA_H
#define NHF2STREAMS_ERA_H

#include "stream.h"

// Eratoszthenész szitája, stream-mel megvalósítva (note: csak egy konstruktora van, mert használat után nem működne amúgy sem, valamint csak
//                                                        1 variációja van)
class Era : public Stream<int>{
private:
    int next() override;
    bool hasNext() override;
    std::shared_ptr<FilterStream<int>> stream; // a saját streamje, mindig épül filterekkel
public:
    Era();
};


#endif //NHF2STREAMS_ERA_H
