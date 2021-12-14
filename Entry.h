
#ifndef ENTRY_H
#define ENTRY_H

#include <fstream>
#include <iostream>
#include <ostream>

/**
 * @brief This class represents a general *entry*, which is composed from a
 *        *key* and a *value*.
 *
 * `Entries` are compared to each other, by the comparable `key` field
 * located in each `Entry` element.
 * @attention the `key` **must** be `comparable`.
 * @tparam K the type of *key* in the entry.
 * @tparam V the type of *value* in the entry.
 * @version 1.0.1
 */
template<typename K, typename V> class Entry {
  private:
    /// The *key* of the entry. @attention **Must** be `comparable`.
    K _key;

  private:
    /// The *value* of the entry.
    V _value;

  public:
    /**
     * @brief Initializer constructor.
     *
     * @param key the key to set the entry with.
     * @param value the value to set the entry with.
     */
    Entry(K key, V value) {
        this->_key   = key;
        this->_value = value;
    }

  public:
    Entry() = default;

  public:
    virtual ~Entry() = default;

  public:
    K getKey() const { return _key; }

  public:
    void setKey(K key) { this->_key = key; }

  public:
    V getValue() const { return _value; }

  public:
    void setValue(V value) { this->_value = value; }

  public:
    friend std::ostream &operator<<(std::ostream &os, const Entry &entry) {
        // os << "(key: " << entry._key << ", value: " << entry._value << ")";
        os << entry._key << " " << entry._value;
        return os;
    }

    bool operator<(const Entry &other) const { return (_key < other._key); }

    bool operator>(const Entry &other) const { return (_key > other._key); }

    bool operator<=(const Entry &other) const { return !(other < *this); }

    bool operator>=(const Entry &other) const { return !(*this < other); }

    bool operator==(const Entry &other) const { return _key == other._key; }

    bool operator!=(const Entry &other) const { return !(other == *this); }
};


#endif // ENTRY_H