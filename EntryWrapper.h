
#ifndef ENTRY_WRAPPER_H
#define ENTRY_WRAPPER_H

#include "Entry.h"

/**
 * @brief This class is designed to wrap an `Entry` with two indexes.
 *        @li the first index tells at which index this `entry` is placed on
 * @tparam K
 * @tparam V
 */
template<typename K, typename V> class EntryWrapper {

  public:
    EntryWrapper() = default;

  private:
    Entry<K, V> *_entry = nullptr;

  private:
    long int _maxHeapIndex = 0;

  private:
    long int _minHeapIndex = 0;

  public:
    Entry<K, V> *getEntry() const { return _entry; }

  public:
    void setEntry(Entry<K, V> *entry) { _entry = entry; }

  public:
    long getMaxHeapIndex() const { return _maxHeapIndex; }

  public:
    void setMaxHeapIndex(long maxHeapIndex) { _maxHeapIndex = maxHeapIndex; }

  public:
    long getMinHeapIndex() const { return _minHeapIndex; }

  public:
    void setMinHeapIndex(long minHeapIndex) { _minHeapIndex = minHeapIndex; }
};

#endif // ENTRY_WRAPPER_H
