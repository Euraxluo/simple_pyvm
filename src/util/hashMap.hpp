//
// Created by euraxluo on 2021/1/5.
//

#ifndef SIMPLE_PYVM_HASHMAP_HPP
#define SIMPLE_PYVM_HASHMAP_HPP
#define MAXSIZE  1<<30
#define MINSIZE  1<<2


#include <assert.h>
#include "stdio.h"

template<typename K, typename V>
class MapEntry {
public:
    K _k= nullptr;
    V _v= nullptr;
    unsigned int _hash=0;
    MapEntry<K, V> *_next = nullptr;
public:
    MapEntry(const MapEntry<K, V> &entry) {
        _k = entry._k;
        _v = entry._v;
        _hash = entry._hash;
    };

    MapEntry(K k= nullptr, V v= nullptr, unsigned int hash=0) : _k(k), _v(v), _hash(hash) {}

    MapEntry(K k, unsigned int hash) : _k(k), _v(nullptr), _hash(hash) {}

    ~MapEntry() {
//        printf("~MapEntry v %d  ;",_v);
//        printf("~MapEntry _hash %u ;",_hash);
        _k = (K)NULL;
        _v = (V)NULL;
        _hash = 0;
        _next = nullptr;
//        printf("~MapEntry done\n");
    }
};

template<typename K, typename V>
class HashTable {
public:
    MapEntry<K, V> **_table = nullptr;//初始化
    size_t _size;
    size_t _sizeMask;
    size_t _used;

    HashTable(size_t initSize = 0) {
        _size = initSize;
        _sizeMask = _size == 0 ? 0 : _size - 1;
        _used = 0;
        _init_table();
//        printf(" HashTable done\n");
    }

    ~HashTable() {
        _del_table();
        _size = 0;
        _sizeMask = _size == 0 ? 0 : _size - 1;
        _used = 0;
//        printf("~HashTable done\n");
    }

    /**
     * MapEntry<K, V> **_table=nullptr
     * 初始化时，_table为nullptr，保证不用的时候，他都是nullptr
     * new MapEntry<K, V> *[_size]，这时候就是一个可以访问的对象了，索引项都是null
     * 需要迭代这个可以访问的地址，把对应索引的null变成空的mapEntry
     * _table[i] = new MapEntry<K, V>;
     * 空的MapEntry形式：{_k=null,_v=0,_hash=0,_next=null}
     *
     */
    void _init_table() {
        _table = _size == 0 ? nullptr : new MapEntry<K, V> *[_size];
        for (int i = 0; i < _size; i++) {
            _table[i] = nullptr;
//            printf("_table %d\n", i);
        }
//        printf("_table done\n");
    }

    /**
     * _table这时候就是一个可以访问的对象了，索引项都是空的mapEntry对象
     * 需要迭代这个可以访问的地址，把对应索引的空的mapEntry变成null
     * _table[i] = nullptr;
     * 空的MapEntry形式：{_k=null,_v=0,_hash=0,_next=null}
     *
     * 最后记得把_table设置为nullptr，如果是delete[] _table,则会生成一个默认为空的 ew MapEntry<K, V>*;
     */
    void _del_table() {
//        printf("del_table  begin;table %lu;entry: %lu\n",_size,_used);
        for (int i = 0; i < _size; ++i) {
//            printf("del_table %d\n", i);
            _table[i] = nullptr;
        }
        _table= nullptr;
//        printf("del_table  done\n");
    }
};


/**内置几种hash函数*/
/**int型hash，Thomas Wang's 32 bit Mix Function*/
template<typename K>
unsigned int intHash(K key) {
    key = (unsigned int) key;
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key << 3);
    key ^= (key >> 6);
    key += ~(key << 11);
    key ^= (key >> 16);
    return key;
}

/** id 型KEY*/
template<typename K>
unsigned int IdentityHash(K key) {
    key = (unsigned int) key;
    return key;
}

/**字符串hash,djb hash*/
template<typename K>
unsigned int DJBHash(K key) {
    unsigned int hash = 5381;

    while (*key) {
        hash = ((hash << 5) + hash) + (*key++); /* times 33 */
    }
    hash &= ~(1 << 31); /* strip the highest bit */
    return hash;
}


/**使用K的hashCode函数*/
template<typename K>
unsigned int hashCode(K key) {
    return (key == nullptr) ? 0 : key.hashCode();
}

template<typename K>
unsigned int hashCode(K *key) {
    return (key == nullptr) ? 0 : key->hashCode();
}

template<typename K, typename V>
class HashMap {
private:
    int _rehashidx=-1;
    HashTable<K, V> *_hashTable = nullptr;

    unsigned int (*_hashFunc)(K k);

    /**
     * resize 相关
     * @param size
     * @return
     */
    inline size_t sizeNextPower(size_t size) {
        size_t newSize = size - 1;
        newSize |= newSize >> 1;
        newSize |= newSize >> 2;
        newSize |= newSize >> 4;
        newSize |= newSize >> 8;
        newSize |= newSize >> 16;
        return (newSize < 0) ? 1 : (newSize >= MAXSIZE) ? MAXSIZE : newSize + 1;
    }

    inline size_t _tableSizeToBig(size_t size) {
        return sizeNextPower(size << 2);
    }

    inline size_t _tableSizeToSmall(size_t size) {
        if (size < MINSIZE) {
            size = MINSIZE;
        }
        return sizeNextPower(size);
    }

    /**
     * hashTable about
     */
    inline unsigned int _hashTableKeyIndex(HashTable<K, V> *ht, K k) {
        //获取hash值
        unsigned int hash = (*_hashFunc)(k);
        //返回计算出应该放在哪个索引处
        return (unsigned) (hash & ht->_sizeMask);
    }

    inline void _swap() {
        //将新的设置为常用table

        auto oldTable = *_hashTable;
        *_hashTable = *(_hashTable + 1);
        //将原来的地方设置为旧的那个
        *(_hashTable + 1) = oldTable;
//        printf("_swap done\n");
    }

    /**
     * 返回一个Key对应的应该放置在hashTable中的一个位置，直接返回一个类型指针
     * @param ht
     * @param k
     * @return
     */
    MapEntry<K, V> *_keyAtHashTable(HashTable<K, V> *ht, K k) {
        if (ht->_size == 0)
            return nullptr;
        //计算出在这个ht中的插入位置
        size_t index = _hashTableKeyIndex(ht, k);
        //判断该位置出处有没有key
        MapEntry<K, V> *mapEntry = ht->_table[index];
        while (mapEntry) {
            if (mapEntry->_hash == (*_hashFunc)(k))
                return mapEntry;
            mapEntry = mapEntry->_next;
        }
        return mapEntry;
    }

    /**
     * 从hashTable中删除一个key
     * @param ht
     * @param k
     * @return
     */
    bool _keyRemoveFromHashTable(HashTable<K, V> *ht, K k) {
        if (ht->_size == 0)
            return false;
        //计算出在这个ht中的插入位置
        size_t index = _hashTableKeyIndex(ht, k);
        //判断该位置出处有没有key
        MapEntry<K, V> *mapEntry = ht->_table[index];
        MapEntry<K, V> *preMapEntry = nullptr;
        while (mapEntry) {
            if (mapEntry->_hash == (*_hashFunc)(k)) {
                if (preMapEntry)
                    preMapEntry->_next = mapEntry->_next;
                else
                    ht->_table[index] = mapEntry->_next;
                delete mapEntry;
                ht->_used--;
                return true;
            }

            //首先将前置指针保存下来
            preMapEntry = mapEntry;
            //推进后置指针
            mapEntry = mapEntry->_next;
        }
        return false;
    }

    /**
     * 计算装载因子
     * @param table
     * @return
     */
    inline float _loadFactor(HashTable<K, V> *table) {
        if (table->_size == 0) return 0.0;
        return float(table->_used) / table->_size;
    }

    /**
     * 传入装载因子，得到新的size
     * @param load_factor
     * @return
     */
    inline unsigned int _reSize(HashTable<K, V> *table) {
        //如果小于0.1,那么需要将tableSize变小
        size_t newSize = _loadFactor(table) <= 0.1 ? _tableSizeToSmall(table->_used) : table->_size;
        //如果小于0.1,那么需要将tableSize变小
        newSize = _loadFactor(table) >= 0.75 ? _tableSizeToBig(table->_used) : newSize;
        return (unsigned int)newSize;
    }

    /**
     * hashTable重置
     * @param table
     */
    void _tableReset(HashTable<K, V> *table) {

        table->_del_table();
        table->_size = 0;
        table->_sizeMask = 0;
        table->_used = 0;
//        printf("_tableReset done\n");
    }

    void _tableInit(HashTable<K, V> *table, size_t newSize) {
        table->_size = newSize;
        table->_sizeMask = newSize - 1;
        table->_used = 0;
        table->_init_table();
//        printf("_tableInit done\n");
    }

    /**
     * 自动将table扩容或者缩容，如果不需要进行任何变化，那么就会直接返回
     * @param table
     */
    void _tableExpand(HashTable<K, V> *table) {
        //如果当前正在rehash中，那么就进行单步rehash
        //如果执行单步rehash后，并且没有结束rehash，那就直接退出
        if (_rehashidx != -1) {
            if (_reHash(&_hashTable[0], &_hashTable[1], 1) == 0) {
                _swap();
            }
            return;
        }

        size_t newSize = _reSize(table);
        //如果计算出不需要进行任何变化，那么就是直接退出
        if (newSize == table->_size) {
            return;
        }
        //如果size发生了变化，但是当前table没有被初始化，那么就进行初始化
        if (table->_size == 0) {
//            printf("\ninit table\n");
            _tableInit(table, newSize);
            return;
        } else {
//            printf("\ninit table\n");
            _tableInit(&_hashTable[1], newSize);
        }
        //否则需要进行rehash，需要新创建一个table，或者直接使用1号table进行rehash操作
        /**
         * rehash
         * 这里执行一次性rehash
         * 要求一次性hash开始条件是现在没有进行rehash
         */

        if (_rehashidx == -1 && _reHash(table, &_hashTable[1], table->_size) == 0) {
            _swap();
        }
        return;
    }

    /**
     * 将oldTable中的数据rehash到新的table中
     * @param oldTable
     * @param newTable
     * @param step
     */
    inline int _reHash(HashTable<K, V> *oldTable, HashTable<K, V> *newTable, int step) {
        _rehashidx = _rehashidx == -1 ? 0 : _rehashidx;
        //执行step步rehash
        while (step--) {
            //如果老的tablereHash完毕，那么返回0，并且将reHashIdx置为-1，并且释放掉oldTab
            if (oldTable->_used == 0) {
                //释放oldTable的_table
//                delete[] oldTable->_table;
                //重置oldTable
                _tableReset(oldTable);
                _rehashidx = -1;
                return 0;
            }
            //rehashIdx 必须小于table的_size
            assert(_rehashidx < int(oldTable->_size));

            //开始rehash
            //1. 将rehashIdx移动到第一个不为空的索引处
            while (oldTable->_table[_rehashidx] == nullptr)_rehashidx++;
            //2. 获取该索引处的头指针
            MapEntry<K, V> *mapEntry, *nextEntry;
            mapEntry = oldTable->_table[_rehashidx];
            nextEntry = nullptr;
            //3. 将这个索引处的所有数据移动到新的table中
            while (mapEntry && mapEntry->_k) {
                unsigned int newIdx;
                //这个节点的下一个节点
                nextEntry = mapEntry->_next && mapEntry->_next->_k ? mapEntry->_next : nullptr;
                //计算出当前节点应该放在新的table中的哪一个索引处
                newIdx = _hashTableKeyIndex(newTable, mapEntry->_k);
                mapEntry->_next = newTable->_table[newIdx];
                newTable->_table[newIdx] = mapEntry;
                //更新两个table的计数器
                oldTable->_used--;
                newTable->_used++;
                //继续处理系啊一个，直到当前节点为nullptr
                mapEntry = nextEntry;
            }
            //4.该索引迁移完毕，将oldTable索引出置为null，方便下一次
            oldTable->_table[_rehashidx] == nullptr;
            //5.rehashidx +1
            _rehashidx++;
        }
        if (oldTable->_used == 0) {
            //释放oldTable的_table
//            delete[] oldTable->_table;
            //重置oldTable
            _tableReset(oldTable);
            _rehashidx = -1;
            return 0;
        } else {
            return oldTable->_used;
        }
    }

private:
    /**
     * 将K在hashTable中找个位置插入，然后返回这个节点
     * @param k
     * @return
     */
    MapEntry<K, V> *putRaw(K k, V v) {
        //判断应该使用哪一个hashTabe
        //如果现在还在rehash中，那么这时候使用新的，否则就使用默认的
        //并且我们还需要进行一下单步rehash
        HashTable<K, V> *ht = (_rehashidx == -1) ? &_hashTable[0] : &_hashTable[1];
        //初始化或者rehash这个hashTable
        _tableExpand(ht);
        //再次校验
        ht = (_rehashidx == -1) ? &_hashTable[0] : &_hashTable[1];

        MapEntry<K, V> *mapEntry = _keyAtHashTable(ht, k);
        if (mapEntry == nullptr) {
            //创建出键值对
            unsigned int hash = (*_hashFunc)(k);
            mapEntry = new MapEntry<K, V>(k, hash);
            //将这个键值对放在链子的头部
            mapEntry->_next = ht->_table[_hashTableKeyIndex(ht, k)];
            ht->_table[_hashTableKeyIndex(ht, k)] = mapEntry;
            ht->_used++;
        }
        //设置节点的值
        mapEntry->_v = v;
        //返回这个节点
        return mapEntry;
    }

    bool rehashIdxNotInit() {
        return _rehashidx != -1;
    }
public:
    /**
     * 默认hashFunc是K的hashCode函数
     */
    HashMap() {
        _hashTable = new HashTable<K, V>[2];
        _tableReset(&_hashTable[0]);
        _tableReset(&_hashTable[1]);
        _rehashidx = -1;
        _hashFunc = &hashCode;
    }
    /**
     * 需要传入一个函数指针
     * @param hashFunc unsigned int (*hashFunc )(K k)
     */
    HashMap(unsigned int (*hashFunc )(K k)) {
        _hashTable = new HashTable<K, V>[2];
        _tableReset(&_hashTable[0]);
        _tableReset(&_hashTable[1]);
        _rehashidx = -1;
        _hashFunc = hashFunc;
    }

    ~HashMap(){
//        printf("~HashMap\n");
        delete[] _hashTable;
        _hashTable= nullptr;
        _rehashidx = -1;
        _hashFunc = nullptr;
//        printf("~HashMap done\n");
    }
    void setHashFunction(unsigned int (*hashFunc)(K k)) {
        _hashFunc = hashFunc;
    }

    MapEntry<K, V> *put(K k, V v) {
        if (rehashIdxNotInit() && _reHash(&_hashTable[0], &_hashTable[1], 1) == 0) {
            //将新的设置为常用table
            HashTable<K, V> *tmpTable = &_hashTable[0];
            _hashTable[0] = _hashTable[1];
            //将原来的地方设置为旧的那个
            _hashTable[1] = *tmpTable;
        }
        return putRaw(k, v);
    }

    /**
     * 判断hashMap中是不是有这个key
     * @param k
     * @return
     */
    bool hash_key(K k) {
        for (int table = 0; table <= 1; ++table) {
            HashTable<K, V> *ht = &_hashTable[table];
            MapEntry<K, V> *mapEntry = _keyAtHashTable(ht, k);
            if (mapEntry)
                return true;
            //如果此时在进行rehash，那么我们这里也进行单步rehash
            if (rehashIdxNotInit() && _reHash(&_hashTable[0], &_hashTable[1], 1) == 0) {
                //将新的设置为常用table
                HashTable<K, V> *tmpTable = &_hashTable[0];
                _hashTable[0] = _hashTable[1];
                //将原来的地方设置为旧的那个
                _hashTable[1] = *tmpTable;
            }
        }
        return false;

    }

    V get(K k, V defaultV = nullptr) {
        //如果此时在进行rehash，那么我们这里也进行单步rehash
        if (rehashIdxNotInit() && _reHash(&_hashTable[0], &_hashTable[1], 1) == 0) {
            //将新的设置为常用table
            HashTable<K, V> *tmpTable = &_hashTable[0];
            _hashTable[0] = _hashTable[1];
            //将原来的地方设置为旧的那个
            _hashTable[1] = *tmpTable;
        }
        for (int table = 0; table <= 1; ++table) {
            HashTable<K, V> *ht = &_hashTable[table];
            MapEntry<K, V> *mapEntry = _keyAtHashTable(ht, k);
            if (mapEntry)
                return mapEntry->_v;
        }
        return defaultV;
    }

    void remove(K k) {
        for (int table = 0; table <= 1; ++table) {
            HashTable<K, V> *ht = &_hashTable[table];
            if (_keyRemoveFromHashTable(ht, k))
                return;
            //如果此时在进行rehash，那么我们这里也进行单步rehash
            if (rehashIdxNotInit() && _reHash(&_hashTable[0], &_hashTable[1], 1) == 0) {
                //将新的设置为常用table
                HashTable<K, V> *tmpTable = &_hashTable[0];
                _hashTable[0] = _hashTable[1];
                //将原来的地方设置为旧的那个
                _hashTable[1] = *tmpTable;
            }
        }
        return;
    }
};



#endif //SIMPLE_PYVM_HASHMAP_HPP
