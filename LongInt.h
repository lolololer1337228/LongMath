//
// Created by Никита on 10.01.2023.
//

#ifndef LONGMATH__LONGINT_H_
#define LONGMATH__LONGINT_H_

#include <string>
#include <vector>
typedef std::vector<int> lnum;

class LongInt {
 public:
  LongInt();
  LongInt(long long n);
  LongInt(const std::string &s);

  friend LongInt operator+(const LongInt &a, const LongInt &b);
  friend LongInt &operator+=(LongInt &a, const LongInt &b);
  friend LongInt operator-(const LongInt &a, const LongInt &b);
  friend LongInt &operator-=(LongInt &a, const LongInt &b);
  friend LongInt operator*(const LongInt &a, const LongInt &b);
  friend LongInt &operator*=(LongInt &a, const LongInt &b);
  friend LongInt operator/(const LongInt &a, const LongInt &b);
  friend LongInt &operator/=(LongInt &a, const LongInt &b);
  friend LongInt operator%(const LongInt &a, const LongInt &b);
  friend LongInt &operator%=(LongInt &a, const LongInt &b);

  std::string str() const;

  friend bool operator<(const LongInt &a, const LongInt &b);
  friend bool operator>(const LongInt &a, const LongInt &b);
  friend bool operator<=(const LongInt &a, const LongInt &b);
  friend bool operator>=(const LongInt &a, const LongInt &b);
  friend bool operator==(const LongInt &a, const LongInt &b);
  friend bool operator!=(const LongInt &a, const LongInt &b);

  LongInt operator-();

  LongInt &operator++();
  LongInt operator++(int);
  LongInt &operator--();
  LongInt operator--(int);
  LongInt &operator=(const LongInt &other);
  std::pair<LongInt, LongInt> divmod(const LongInt &a) const;
  static LongInt abs(const LongInt &a);
  void shift_right();
  void fixup();
 private:
  const int base = 1000000000;
  lnum num;
  bool negative = false;
};

#endif //LONGMATH__LONGINT_H_
