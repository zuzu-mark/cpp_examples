#ifndef __blocking_ring_H__
#define __blocking_ring_H__

#include "ring.h"
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <chrono>
#include <functional>

template <typename T, size_t N>
class BlockingRing : public Ring<T, N>{
public:
    using Super = Ring<T, N>;
    using Mutex = std::mutex;
    using Condv = std::condition_variable;
    using LockS = std::lock_guard<Mutex>;           // lock in scope
    using LockC = std::unique_lock<Mutex>;          // lock by condition
private:
    Mutex _mutex;
    Condv _condv;
public:
    template <typename... Args>
    void emplace_back(Args&&... args);
    void push_back(T&& item);
    T pop_back();
    void push_front(T&& item);
    T pop_front();
    bool try_pop_front(T&);
    bool empty();
    bool not_empty();
    bool full();
    bool not_full();
};

#include "blocking_ring.cc"

#endif //__blocking_ring_H__
