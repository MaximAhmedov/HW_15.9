#include "HashTable.h"

HashTable::HashTable()
{
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}

HashTable::~HashTable()
{
    delete[] array;
}

void HashTable::add(char _login[LOGINLENGTH], uint* sh1)
{
    int index = -1, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status == enPairStatus::free) {
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

void HashTable::del(char _login[LOGINLENGTH], uint* sh1)
{
    int index = -1, i = 0;
    for (; i < mem_size; i++) {
        index = hash_func(_login, i);
        if (array[index].status == enPairStatus::engaged) {
            break;
        }
    }
    if (i >= mem_size) {
        return;
    }
    else {
        array[index].status = deleted;
        count--;
    }
}

void HashTable::resize()
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

int HashTable::hash_func(char _login[LOGINLENGTH], int offset)const
{
    const double A = 0.7;
    int sum = 0, i = 0;
    for (; i < strlen(_login); i++) {
        sum += _login[i];
    }
    return int((mem_size + offset * offset) * (sum * A - int(sum * A)));
}