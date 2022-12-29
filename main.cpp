#include <iostream>
#include <string>
#include <vector>

class A {
public:
  void alpha(std::string s) { std::cout << "Alpha (of string) (in A)\n"; }
  void alpha(std::vector<std::string> vec) {
    std::cout << "Alpha (of vector) (in A)\n";
  }
  void beta(std::string s) { std::cout << "Beta (of string) (in A)\n"; }
  void beta(std::vector<std::string> vec) {
    std::cout << "Beta (of vector) (in A)\n";
  }
};

class AA : public A {
public:
};

class AAA : public AA {
public:
  void beta(std::string s) { std::cout << "Beta (of string) in AAA\n"; }
  void beta(std::vector<std::string> vec) {
    std::cout << "Beta (of vector) in AAA\n";
  }
  void alpha(std::string s) { std::cout << "Alpha (of string) in AAA\n"; }
};

void overload_resolution_example() {
  std::string s{};
  std::vector<std::string> v{};

  A a;
  AA aa;
  AAA aaa;

  aaa.alpha(s); // S(alpha, AAA) = { { alpha(std::string) }, { AAA } }
  // aaa.alpha(v); // error: S(alpha, AAA) = { { alpha(std::string) }, { AAA } }
  // only. The search stops there.

  aaa.beta(s); // S(beta, AAA) = { { beta(std::string),
               // beta(std::vector<std::string>) }, { AAA } } (those are
               // immediately available and no subclasses are considered.)
  aaa.beta(v); // S(beta, AAA) = { { beta(std::string),
               // beta(std::vector<std::string>) }, { AAA } } (those are
               // immediately available and no subclasses are considered.)

  aa.alpha(s); // S(alpha, AA) = S(alpha, A) (because S(alpha, AA)
               // is empty, search continues in base classes!)
               // ie, S(alpha, AA) = { { alpha(std::string),
               // alpha(std::vector<std::string> }, { A } }.
  aa.alpha(v); // S(alpha, AA) = S(alpha, A) (because S(alpha, AA)
               // is empty, search continues in base classes!)
               // ie, S(alpha, AA) = { { alpha(std::string),
               // alpha(std::vector<std::string> }, { A } }.
}

template <class T> class Base {
public:
  virtual void setter(const T &) { std::cout << "Setter in Base\n"; }
  virtual void getter() { std::cout << "Getter in Base\n"; }
};

template <class T> class Derived : public Base<T> {
public:
  virtual void setter(const T &) { std::cout << "Setter in Derived\n"; }
  virtual void getter() { std::cout << "Getter in Derived\n"; }
};

void virtual_function_example() {

  Derived<int> d{};
  Base<int> b{d};
  Base<int> &bv{d};

  b.setter(5);
  b.getter();
  bv.setter(5);
  bv.getter();
}

int main() {
  overload_resolution_example();
  virtual_function_example();
  return 0;
}