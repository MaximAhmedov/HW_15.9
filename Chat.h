#pragma once
#include <iostream>
#include "HashTable.h"

#define LOGINLENGTH 10


class Chat : private HashTable{
public:
    Chat() = default;
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    void logout(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);
private:
    HashTable table;
};