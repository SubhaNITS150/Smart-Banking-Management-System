#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

class PasswordManager {
public:
    PasswordManager() {
        srand(static_cast<unsigned int>(time(nullptr))); // Seed for salt generation
    }

    std::string generateSalt(int length = 16) {
        const char charset[] =
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789";
        std::string salt;
        for (int i = 0; i < length; ++i) {
            salt += charset[rand() % (sizeof(charset) - 1)];
        }
        return salt;
    }

    unsigned int rotateLeft(unsigned int x, int n) {
        return (x << n) | (x >> (32 - n));
    }

    std::string toHex(unsigned int val) {
        std::stringstream ss;
        ss << std::hex << std::setw(8) << std::setfill('0') << val;
        return ss.str();
    }

    std::string secureHash(const std::string& input, int rounds = 2000) {
        unsigned int h0 = 0x67452301;
        unsigned int h1 = 0xEFCDAB89;
        unsigned int h2 = 0x98BADCFE;
        unsigned int h3 = 0x10325476;

        for (int r = 0; r < rounds; ++r) {
            for (size_t i = 0; i < input.size(); ++i) {
                unsigned int c = static_cast<unsigned char>(input[i]);
                h0 ^= rotateLeft(h1, 5) + c;
                h1 ^= rotateLeft(h2, 7) + c;
                h2 ^= rotateLeft(h3, 13) + c;
                h3 ^= rotateLeft(h0, 17) + c;
            }
        }

        return toHex(h0) + toHex(h1) + toHex(h2) + toHex(h3);
    }

    std::string hashPassword(const std::string& password) {
        std::string salt = generateSalt();
        std::string hash = secureHash(salt + password);
        return salt + "$" + hash;  // Salt and hash are returned together
    }

    bool checkPassword(const std::string& password, const std::string& stored) {
        size_t pos = stored.find('$');
        if (pos == std::string::npos) return false;
        std::string salt = stored.substr(0, pos);
        std::string expected = stored.substr(pos + 1);
        std::string computed = secureHash(salt + password);
        return computed == expected;
    }
};


#endif