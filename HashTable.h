#pragma once
#include "sha1.h"
#include "string.h"

#define LOGINLENGTH 10


class HashTable { // хеш-таблица
public:
    HashTable();
    ~HashTable();

    enum enPairStatus {
        free,
        engaged,
        deleted
    };
    struct Pair {
        Pair() :
            login(""),
            pass_sha1_hash(0),
            status(enPairStatus::free) {
        }
        ~Pair() {
            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
        }
        Pair(char _login[LOGINLENGTH], uint* sh1) : status(enPairStatus::engaged) {
            strcpy_s(login, _login);
            pass_sha1_hash = sh1;
        }
        Pair& operator = (const Pair& other) {
            strcpy_s(login, other.login);
            status = other.status;
            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
            return *this;
        }
        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
        enPairStatus status; // состояние ячейки
    };
    void add(char _login[LOGINLENGTH], uint* sh1);
    void del(char _login[LOGINLENGTH], uint* sh1);
    void resize();
    int hash_func(char _login[LOGINLENGTH], int offset)const;

    Pair* array;
    int mem_size;
    int count;
};