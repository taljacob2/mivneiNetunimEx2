
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

  private:
    Entry<K, V> entry = nullptr;

  private:
    long int maxHeapIndex = 0;

  private:
    long int minHeapIndex = 0;

  public:
    const Entry < K, &getEntry() const { return entry; }

  public:
    void setEntry(const Entry < K, &entry) { EntryWrapper::entry = entry; }

  public:
    long getMaxHeapIndex() const { return maxHeapIndex; }

  public:
    void setMaxHeapIndex(long maxHeapIndex) {
        EntryWrapper::maxHeapIndex = maxHeapIndex;
    }

  public:
    long getMinHeapIndex() const { return minHeapIndex; }

  public:
    void setMinHeapIndex(long minHeapIndex) {
        EntryWrapper::minHeapIndex = minHeapIndex;
    }
};

#endif // ENTRY_WRAPPER_H
