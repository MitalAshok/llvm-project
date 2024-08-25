// RUN: %clang_cc1 -std=c++20 -verify %s
// RUN: %clang_cc1 -std=c++20 -verify %s -fexperimental-new-constant-interpreter

// Make sure all the subexpressions of an immediate invocation are found

namespace GH105558 {
struct A {
    char* x = new char[1];
    constexpr ~A() { delete[] x; }
};

consteval void f(const A& str) {}

consteval A g() { return A(); }

void main() {
    f(g());
}
}

consteval int* alloc() { return new int(0); }
template<typename T = int*>
consteval void f(T p) { delete p; }
struct X {
  int* p;
  explicit(false) constexpr X(int* p) : p(p) {}
};
consteval void g(X x) { delete x.p; }

void test() {
  f<int*>(alloc());
  f<int*&&>(alloc());
  f<const int*&&>(alloc());
  f<const int*>(alloc());
  f<int*const&>(alloc());
  g(alloc());
  f((alloc()));
  f(_Generic(0, int: alloc()));
  f(_Generic(0, int: alloc)());
  f(static_cast<int*>(alloc()));
  using T = const int*;
  f<const int*>(T(alloc()));
  f<const int*>(T{alloc()});
}
