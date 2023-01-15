//
// Created by Никита on 15.01.2023.
//

#ifndef LONGMATH__LONGDOUBLE_H_
#define LONGMATH__LONGDOUBLE_H_
#include "LongInt.h"

class LongDouble {
 public:
  LongDouble();
  LongDouble(const LongInt &n);
  LongDouble(const LongInt &a, const LongInt &b);
  LongDouble(const std::string &s);
  LongDouble(double n) : LongDouble(std::to_string(n)) {};

  friend LongDouble operator+(const LongDouble &a, const LongDouble &b);
  friend LongDouble &operator+=(LongDouble &a, const LongDouble &b);
  friend LongDouble operator-(const LongDouble &a, const LongDouble &b);
  friend LongDouble &operator-=(LongDouble &a, const LongDouble &b);
  friend LongDouble operator*(const LongDouble &a, const LongDouble &b);
  friend LongDouble &operator*=(LongDouble &a, const LongDouble &b);
  friend LongDouble operator/(const LongDouble &a, const LongDouble &b);
  friend LongDouble &operator/=(LongDouble &a, const LongDouble &b);
  friend LongDouble operator%(const LongDouble &a, const LongDouble &b);
  friend LongDouble &operator%=(LongDouble &a, const LongDouble &b);

  std::string str() const;

  friend bool operator<(const LongDouble &a, const LongDouble &b);
  friend bool operator>(const LongDouble &a, const LongDouble &b);
  friend bool operator<=(const LongDouble &a, const LongDouble &b);
  friend bool operator>=(const LongDouble &a, const LongDouble &b);
  friend bool operator==(const LongDouble &a, const LongDouble &b);
  friend bool operator!=(const LongDouble &a, const LongDouble &b);

  LongDouble operator-();

  LongDouble &operator++();
  LongDouble operator++(int);
  LongDouble &operator--();
  LongDouble operator--(int);
  LongDouble &operator=(const LongDouble &other);
  static LongDouble abs(const LongDouble &a);
  void fixup();
  static LongInt gcd(LongInt a, LongInt b);
 private:
  LongInt num, denum;
};

#endif //LONGMATH__LONGDOUBLE_H_
