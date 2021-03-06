#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <ctime>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <unistd.h>
#include <string>
#include <iostream>

namespace Encryption
{

    //generate random salt of predefined letters and numbers
    inline std::string genSalt(const int len)
    {

        std::string tmp_s;
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "%&/()=?{[]}*+#";

        srand((unsigned)time(NULL) * getpid());

        for (int i = 0; i < len; ++i)
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

        return tmp_s;
    }

    using namespace CryptoPP;

    //hash password with random generated salt
    inline std::string hashPassword(std::string password, std::string salt)
    {

        const int MAX_PHRASE_LENGTH = 250;
        std::string msg = password + std::string(salt);
        CryptoPP::SHA256 hash;
        byte digest[CryptoPP::SHA256::DIGESTSIZE];

        hash.CalculateDigest(digest, (const byte *)msg.c_str(), msg.length());

        CryptoPP::HexEncoder encoder;
        std::string output;
        encoder.Attach(new CryptoPP::StringSink(output));
        encoder.Put(digest, sizeof(digest));
        encoder.MessageEnd();

        return output;
    }
} // namespace Encryption

#endif