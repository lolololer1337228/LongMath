//
// Created by Никита on 15.01.2023.
//

#include "LongDouble.h"
typedef unsigned long long ull;
typedef long long ll;

LongInt LongDouble::gcd(LongInt a, LongInt b) {
  while (a != 0 && b != 0) {
    if (a > b) a %= b;
    else b %= a;
  }
  return a + b;
}

void LongDouble::fixup() {
  LongInt res = gcd(LongInt::abs(this->num), this->denum);
  this->num /= res;
  this->denum /= res;
  if (num == 0) denum = 1;
  else if (denum < 0) {
    num = -num;
    denum = -denum;
  }
}

LongDouble operator+(const LongDouble &a, const LongDouble &b) {
  LongDouble res;
  res.num = a.num * b.denum + a.denum * b.num;
  res.denum = a.denum * b.denum;
  res.fixup();
  return res;
}

LongDouble &operator+=(LongDouble &a, const LongDouble &b) {
  a = a + b;
  return a;
}

LongDouble operator-(const LongDouble &a, const LongDouble &b) {
  LongDouble res;
  res.num = a.num * b.denum - a.denum * b.num;
  res.denum = a.denum * b.denum;
  res.fixup();
  return res;
}

LongDouble &operator-=(LongDouble &a, const LongDouble &b) {
  a = a - b;
  return a;
}

LongDouble operator*(const LongDouble &a, const LongDouble &b) {
  LongDouble res;
  res.num = a.num * b.num;
  res.denum = a.denum * b.denum;
  res.fixup();
  return res;
}

LongDouble &operator*=(LongDouble &a, const LongDouble &b) {
  a = a * b;
  return a;
}

LongDouble operator/(const LongDouble &a, const LongDouble &b) {
  LongDouble tmp;
  tmp.num = b.denum;
  tmp.denum = b.num;
  return a * tmp;
}

LongDouble &operator/=(LongDouble &a, const LongDouble &b) {
  a = a / b;
  return a;
}

LongDouble operator%(const LongDouble &a, const LongDouble &b) {
  LongDouble res = a / b;
  res.num %= res.denum;
  return res;
}

LongDouble &operator%=(LongDouble &a, const LongDouble &b) {
  a = a % b;
  return a;
}

bool operator<(const LongDouble &a, const LongDouble &b) {
  LongInt num1, num2;
  num1 = a.num * b.denum;
  num2 = b.num * a.denum;
  return num1 < num2;
}

bool operator==(const LongDouble &a, const LongDouble &b) {
  return a.num == b.num && a.denum == b.denum;
}

bool operator>(const LongDouble &a, const LongDouble &b) {
  return !(a < b || a == b);
}

bool operator<=(const LongDouble &a, const LongDouble &b) {
  return a < b || a == b;
}

bool operator>=(const LongDouble &a, const LongDouble &b) {
  return !(a < b);
}

bool operator!=(const LongDouble &a, const LongDouble &b) {
  return !(a == b);
}

LongDouble LongDouble::operator-() {
  LongDouble tmp = *this;
  tmp.num = -tmp.num;
  return tmp;
}

LongDouble &LongDouble::operator++() {
  *this = *this + 1;
  return *this;
}

LongDouble LongDouble::operator++(int) {
  *this = *this + (LongDouble) (1);
  return (*this - (LongDouble) (1));
}

LongDouble &LongDouble::operator--() {
  *this = *this - 1;
  return *this;
}

LongDouble LongDouble::operator--(int) {
  *this = *this - (LongDouble) (1);
  return (*this + (LongDouble) (1));
}

LongDouble &LongDouble::operator=(const LongDouble &other) {
  this->num = other.num;
  this->denum = other.denum;
  return *this;
}

LongDouble::LongDouble() {
  this->num = 0;
  this->denum = 1;
}

LongDouble::LongDouble(const std::string &s) {
  if (s.find('.') < s.size()) {
    ull ind = s.find('.');
    std::string tmp;
    for (ull i = 0; i < ind; ++i) {
      tmp += s[i];
    }
    this->num = tmp;
    tmp = "";
    std::string nulls;
    for (ull i = ind + 1; i < s.size(); ++i) {
      tmp += s[i];
      nulls += "0";
    }
    this->denum = "1" + nulls;
    this->num = this->num * this->denum + tmp;
  } else if (s.find('/') < s.size()) {
    ull ind = s.find('/');
    std::string tmp;
    for (ull i = 0; i < ind; ++i) {
      tmp += s[i];
    }
    this->num = tmp;
    tmp = "";
    for (ull i = ind + 1; i < s.size(); ++i) {
      tmp += s[i];
    }
    this->denum = tmp;
  }
  this->fixup();
}

std::string LongDouble::str() const {
  LongInt mod = this->num % this->denum;
  LongInt div = this->denum;
  std::string whole = (this->num / this->denum).str();
  std::vector<std::pair<LongInt, LongInt>> history;
  mod = (mod % div) * 10;
  ull period_index;
  while (true) {
    std::pair<LongInt, LongInt> act(mod / div, mod);
    bool exit = false;
    for (ull i = 0; i < history.size(); ++i) {
      if (history[i] == act) {
        exit = true;
        period_index = i;
        break;
      }
    }
    if (exit) break;
    history.push_back(act);
    mod = (mod % div) * 10;
  }
  std::string fractional;
  for (ull i = 0; i < period_index; ++i) {
    fractional += history[i].first.str();
  }
  if (history[period_index].first.str() != "0") {
    fractional += "(";
    for (ull i = period_index; i < history.size(); ++i) {
      fractional += history[i].first.str();
    }
    fractional += ")";
  }
  if (fractional.empty()) fractional = "0";
  std::string res = whole + "." + fractional;
  return res;
}

LongDouble::LongDouble(const LongInt &n) {
  this->num = n;
  this->denum = 1;
}

LongDouble::LongDouble(const LongInt &a, const LongInt &b) {
  this->num = a;
  this->denum = b;
}

LongDouble LongDouble::abs(const LongDouble &a) {
  LongDouble tmp = a;
  tmp.num = LongInt::abs(tmp.num);
  return tmp;
}