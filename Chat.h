#pragma once

#include "sha1.h"
#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
public:
    Chat() = default;
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

private:
    class HashTable { // ���-�������
    public:
        HashTable();
        ~HashTable();
    private:
        enum enPairStatus {
            free, // ��������
            engaged, //�����
            deleted //������
        };
        struct Pair { // ���� ����-��������
            Pair() : // ����������� �� ���������
                login(""),
                pass_sha1_hash(0),
                status(enPairStatus::free) {

            }
            ~Pair() {
                if (pass_sha1_hash != 0)
                    delete[] pass_sha1_hash;
            }
            Pair(char _login[LOGINLENGTH], uint* sh1) : status(enPairStatus::engaged) {
                strcpy(login, _login);
                pass_sha1_hash = sh1;
            }
            Pair& operator = (const Pair& other) {
                strcpy(login, other.login);
                status = other.status;
                if (pass_sha1_hash != 0)
                    delete[] pass_sha1_hash;
                pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

                memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);

                return *this;
            }
            char login[LOGINLENGTH];
            uint* pass_sha1_hash;
            enPairStatus status; // ��������� ������
        };
        void add(char _login[LOGINLENGTH], uint* sh1);
        void resize();
        int hash_func(char _login[LOGINLENGTH], int offset);

        Pair* array;
        int mem_size;
        int count;
    };
};