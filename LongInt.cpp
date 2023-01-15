#include <stdexcept>
#include "LongInt.h"
typedef std::pair<LongInt, LongInt> lpair;
typedef unsigned long long ull;
typedef long long ll;

LongInt LongInt::operator-() {
  LongInt* res = this;
  res->negative = !this->negative;
  return *res;
}

LongInt &operator+=(LongInt &a, const LongInt &b) {
  a = a + b;
  return a;
}

LongInt LongInt::LongInt::abs(const LongInt &a) {
  LongInt tmp = a;
  tmp.negative = false;
  return tmp;
}

LongInt operator+(const LongInt &a, const LongInt &b) {
  LongInt res;
  if (a.negative == b.negative) {
    res.negative = a.negative;
    int carry = 0;
    res.num[0] = a.num[0] + b.num[0];
    carry = (res.num[0]) / res.base;
    res.num[0] %= res.base;
    for (ull i = 1; i < std::min(a.num.size(), b.num.size()) || carry; ++i) {
      res.num.push_back(carry + a.num[i] + b.num[i]);
      carry = (res.num[i]) / res.base;
      res.num[i] %= res.base;
    }
    for (ull i = std::min(a.num.size(), b.num.size()); i < std::max(a.num.size(), b.num.size()) || carry; ++i) {
      res.num.push_back((a.num.size() > b.num.size() ? a.num[i] : b.num[i]) + carry);
      carry = (res.num[i]) / res.base;
      res.num[i] %= res.base;
    }
  } else if (a.negative) {
    LongInt tmp = a;
    tmp.negative = false;
    res = b - tmp;
  } else {
    LongInt tmp = b;
    tmp.negative = false;
    res = a - tmp;
  }
  return res;
}

LongInt &operator-=(LongInt &a, const LongInt &b) {
  a = a - b;
  return a;
}

LongInt operator-(const LongInt &a, const LongInt &b) {
  LongInt res;
  if (a.negative != b.negative) {
    res = LongInt::abs(a) + LongInt::abs(b);
    res.negative = a.negative;
    return res;
  }
  if (LongInt::abs(a) < LongInt::abs(b)) {
    res = -(b - a);
    return res;
  }
  res.negative = a.negative;
  res.num[0] = a.num[0] - b.num[0];
  int carry;
  if (a.num[0] < b.num[0]) {
    carry = 1;
    res.num[0] += res.base;
  } else carry = 0;
  for (ull i = 1; i < b.num.size(); ++i) {
    res.num.push_back(a.num[i] - b.num[i] - carry);
    if (a.num[i] < b.num[i] + carry) {
      carry = 1;
      res.num[i] += res.base;
    } else carry = 0;
  }
  for (ull i = b.num.size(); i < a.num.size(); ++i) {
    res.num.push_back(a.num[i] - carry);
    if (res.num[i] < 0) {
      res.num[i] += res.base;
      carry = 1;
    } else carry = 0;
  }
  res.fixup();
  return res;
}

LongInt operator*(const LongInt &a, const LongInt &b) {
  LongInt c;
  c.num.resize(a.num.size() + b.num.size());
  for (size_t i = 0; i < a.num.size(); ++i)
    for (int j = 0, carry = 0; j < (int) b.num.size() || carry; ++j) {
      long long cur = c.num[i + j] + a.num[i] * 1ll * (j < (int) b.num.size() ? b.num[j] : 0) + carry;
      c.num[i + j] = int(cur % a.base);
      carry = int(cur / a.base);
    }
  while (c.num.size() > 1 && c.num.back() == 0)
    c.num.pop_back();
  c.negative = a.negative != b.negative;
  return c;
}

LongInt &operator*=(LongInt &a, const LongInt &b) {
  a = a * b;
  return a;
}

LongInt &LongInt::operator=(const LongInt &other) {
  this->num.resize(other.num.size());
  for (int i = 0; i < this->num.size(); ++i) {
    this->num[i] = other.num[i];
  }
  this->negative = other.negative;
  return *this;
}

bool operator<(const LongInt &a, const LongInt &b) {
  if (a.negative && b.negative) {
    if (a.num.size() > b.num.size()) return true;
    if (b.num.size() > a.num.size()) return false;
    for (ll i = a.num.size() - 1; i > -1; --i) {
      if (a.num[i] > b.num[i]) return true;
      if (a.num[i] < b.num[i]) return false;
    }
  } else if (!(a.negative || b.negative)) {
    if (a.num.size() < b.num.size()) return true;
    if (b.num.size() < a.num.size()) return false;
    for (ll i = a.num.size() - 1; i > -1; --i) {
      if (a.num[i] < b.num[i]) return true;
      if (a.num[i] > b.num[i]) return false;
    }
  } else return a.negative && !b.negative;
  return false;
}

bool operator==(const LongInt &a, const LongInt &b) {
  if (a.negative != b.negative) return false;
  if (a.num.size() != b.num.size()) return false;
  for (int i = 0; i < a.num.size(); ++i) {
    if (a.num[i] != b.num[i]) return false;
  }
  return true;
}

bool operator<=(const LongInt &a, const LongInt &b) {
  return (a < b) || (a == b);
}

bool operator>(const LongInt &a, const LongInt &b) {
  return !(a <= b);
}

bool operator>=(const LongInt &a, const LongInt &b) {
  return !(a < b);
}

bool operator!=(const LongInt &a, const LongInt &b) {
  return !(a == b);
}

void LongInt::shift_right() {
  this->num.push_back(this->num[this->num.size() - 1]);
  for (ull i = this->num.size() - 1; i > 0; --i) {
    this->num[i] = this->num[i - 1];
  }
  this->num[0] = 0;
}

void LongInt::fixup() {
  while (this->num[this->num.size() - 1] == 0 && this->num.size() > 1) this->num.pop_back();
  if (this->num.size() == 1 && this->num[0] == 0) this->negative = false;
}

lpair LongInt::divmod(const LongInt &a) const {
  if (a == 0) {
    throw std::runtime_error("Zero is specified as the divisor.");
  }

  if (LongInt::abs(*this) < LongInt::abs(a)) {
    std::pair<LongInt, LongInt> result(0, (*this < 0) ? *this + a : *this);
    return result;
  }

  LongInt abs_a = LongInt::abs(a);
  LongInt div, mod;
  div.num.clear();
  mod.num.clear();
  div.num.resize(this->num.size());
  for (long long i = (long long) (this->num.size()) - 1; i >= 0; --i) {
    mod.shift_right();
    mod.num[0] = this->num[i];
    mod.fixup();
    int x = 0, l = 0, r = a.base;
    while (l <= r) {
      int m = (l + r) / 2;
      LongInt t = abs_a * m;
      if (t <= mod) {
        x = m;
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    div.num[i] = x;
    mod -= abs_a * x;

  }
  div.negative = this->negative ^ a.negative;
  div.fixup();
  std::pair<LongInt, LongInt> result(div, mod);
  return result;
}

LongInt operator/(const LongInt &a, const LongInt &b) {
  return a.divmod(b).first;
}

LongInt &operator/=(LongInt &a, const LongInt &b) {
  a = a.divmod(b).first;
  return a;
}

LongInt operator%(const LongInt &a, const LongInt &b) {
  return a.divmod(b).second;
}

LongInt &operator%=(LongInt &a, const LongInt &b) {
  a = a.divmod(b).second;
  return a;
}

LongInt &LongInt::operator++() {
  *this = *this + 1;
  return *this;
}

LongInt LongInt::operator++(int) {
  *this = *this + (LongInt) (1);
  return (*this - (LongInt) (1));
}

LongInt &LongInt::operator--() {
  *this = *this - 1;
  return *this;
}

LongInt LongInt::operator--(int) {
  *this = *this - (LongInt) (1);
  return (*this + (LongInt) (1));
}

std::string LongInt::str() const {
  std::string res = this->negative ? "-" : "";
  res = res + std::to_string(this->num[this->num.size() - 1]);
  for (ll i = (ll) (this->num.size() - 2); i > -1; --i) {
    std::string tmp = std::to_string(this->num[i]);
    while (tmp.size() < 9) {
      tmp = "0" + tmp;
    }
    res += tmp;
  }
  return res;
}

LongInt::LongInt() {
  this->num.push_back(0);
  this->negative = false;
}

LongInt::LongInt(ll n) {
  this->negative = n < 0;
  n = std::abs(n);
  n %= this->base;
  this->num.push_back(n);
  if (n > this->base) this->num[1] = std::abs(n) / this->base;
}

LongInt::LongInt(const std::string &s) {
  this->negative = s[0] == '-';
  std::string tmp;
  int temp;
  for (ull i = (this->negative ? 1 : 0); i < s.size(); ++i) {
    tmp += s[i];
  }
  this->num.push_back(0);
  temp = (unsigned char) (tmp[0]) - 48;
  for (int i = 1; i < tmp.size() % 9; ++i) {
    temp *= 10;
    temp += (unsigned char) (tmp[i]) - 48;
  }
  if (tmp.size() % 9) this->num.push_back(temp);
  for (ull i = tmp.size() % 9; i < tmp.size(); i += 9) {
    temp = (unsigned char) (tmp[i]) - 48;
    for (int j = 1; j < 9; ++j) {
      temp *= 10;
      temp += (unsigned char) (tmp[i + j]) - 48;
    }
    this->shift_right();
    this->num[0] = temp;
  }
  this->fixup();
}
