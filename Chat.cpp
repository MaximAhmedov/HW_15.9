#include "Chat.h"
#include "iostream"
#include "string.h"





void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    uint* sh1 = sha1(_pass, pass_length);
    table.add(_login, sh1);
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    int i = 0;
    for (; i < table.mem_size; i++) {
        Pair& ad = table.array[i];
        if (!strcmp(ad.login, _login)) {
            break;
        }
    }
    if (i >= table.mem_size) return false;
    uint* digest = sha1(_pass, pass_length);
    bool cmpHashes = !memcmp(
        table.array[i].pass_sha1_hash,
        digest,
        SHA1HASHLENGTHBYTES);
    delete[] digest;
    return cmpHashes;
}



