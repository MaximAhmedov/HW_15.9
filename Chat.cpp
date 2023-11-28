#include "Chat.h"
#include "iostream"
#include "string.h"


void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    data[data_count++] = AuthData(_login, sha1(_pass, pass_length));
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // ¬аш код
    // Ќужно вернуть true в случае успешного логина
    int i = 0;
    for (; i < data_count; i++) {
        AuthData& ad = data[i];
        if (!strcmp(ad.login, _login)) {
            break;
        }
    }
    if (i >= data_count) return false;

    uint* digest = sha1(_pass, pass_length);

    bool cmpHashes = !memcmp(
        data[i].pass_sha1_hash,
        digest,
        SHA1HASHLENGTHBYTES);
    delete[] digest;

    return cmpHashes;
}

Chat::HashTable::HashTable()
{
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}

Chat::HashTable::~HashTable()
{
    delete[] array;
}

void Chat::HashTable::add(char _login[LOGINLENGTH], uint* sh1)
{
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status == enPairStatus::free) {
            // найдена пуста€ €чейка, занимаем ее
            break;
        }
    }

    if (i >= mem_size) {
        resize();
        add(_login, sh1);
    }
    else {
        array[index] = Pair(_login, sh1);
        count++;
    }
}

void Chat::HashTable::resize()
{
    Pair* save = array;
    int save_ms = mem_size;

    mem_size *= 2;
    array = new Pair[mem_size];
    count = 0;

    for (int i = 0; i < save_ms; i++) {
        Pair& old_pair = save[i];
        if (old_pair.status == enPairStatus::engaged) {
            add(old_pair.login, old_pair.pass_sha1_hash);
        }
    }

    delete[] save;
}

int Chat::HashTable::hash_func(char _login[LOGINLENGTH], int offset)
{
    const double A = 0.7;
    int sum = 0, i = 0;
    for (; i < strlen(_login); i++) {
        sum += _login[i];
    }
    // квадратичные пробы
    return int((mem_size + offset * offset) * (sum * A - int(sum * A)));
}
