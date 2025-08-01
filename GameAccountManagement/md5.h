#ifndef MD5_H
#define MD5_H

#include <string>
#include <cstring>
#include <iostream>

class MD5 {
public:
    MD5();
    void update(const unsigned char* input, size_t length);
    void update(const char* input, size_t length);
    MD5& finalize();
    std::string hexdigest() const;
private:
    void transform(const unsigned char block[64]);
    void encode(unsigned char* output, const uint32_t* input, size_t length);
    void decode(uint32_t* output, const unsigned char* input, size_t length);

    bool finalized;
    unsigned char buffer[64];
    uint32_t state[4];
    uint32_t count[2];
    unsigned char digest[16];

    static const unsigned char PADDING[64];
};

std::string md5(const std::string str);

#endif