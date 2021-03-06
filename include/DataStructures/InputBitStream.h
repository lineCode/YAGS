//
// Created by qazer on 10.04.2019.
//

#ifndef NETWORK_INPUTBITSTREAM_H
#define NETWORK_INPUTBITSTREAM_H

#include <string>
#include <cstring>
#include "../utils/Constants.h"
#include "../utils/ByteSwap.h"


class InputBitStream {
private:
    bufflen_t mHead;
    byte* mBuffer;
    bool isLittleEndian; // Stream endianness is little endian

    void ReadBits(byte &data, bufflen_t size);
    void ReadBits(void* data, bufflen_t size);

public:
    explicit InputBitStream(const byte* buffer, bufflen_t size);
    ~InputBitStream(){ std::free(mBuffer); }

    template <class T>
    void Read(T& data, bufflen_t size = sizeof(T) * BITS_PER_BYTE)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
                      "Generic BitStream::Read supports only arithmetic or enum types");
        if (isLittleEndian)
        {
            ReadBits(&data, size);
        }
        else
        {
            T tempData;
            ReadBits(&tempData, size);
            data = SwapBytes(tempData);
        }

    };
    void Read(bool& data)  { ReadBits(&data, 1); }
    void Read(std::string& inStr);
};


#endif //NETWORK_INPUTBITSTREAM_H
