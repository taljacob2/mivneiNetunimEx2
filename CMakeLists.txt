cmake_minimum_required(VERSION 3.16)
project(mivneiNetunimEx2)

set(CMAKE_CXX_STANDARD 14)

add_executable(mivneiNetunimEx2 main.cpp Constants.h
        Entry.h Input.h
        TestRunner.h MinHeap.h MaxHeap.h BasicAlgorithms.h
        HeapAdt.h Heap.h ElementInMinHeapAndMaxHeap.h
        BaseArray.h
        MinHeapWhenAlsoHavingMaxHeap.h MaxHeapWhenAlsoHavingMinHeap.h
        DoublePointerMinHeapAndMaxHeapComponent.h Unique.h Object.h
        PriorityQueueKv.h PriorityQueueKvAdt.h)