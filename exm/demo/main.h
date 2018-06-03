#pragma once

#ifdef __cplusplus
#include <iostream>
#include <thread>
template <class T>
int print(T t) { std::cout << t; return 1; }
template <class T, class... Args>
int print(T t, Args... args) { std::cout << t << ' '; return 1; }
template <class... Args>
int println(Args... args) { print(args...); std::cout << std::endl; return 1; }
template<class Func, class... Args>
void async(Func f, Args... args) { std::thread t(f, args...); t.detach(); }
#endif
