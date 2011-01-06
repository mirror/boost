//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//  Adaptation to Boost of the libcxx
//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef REP_H
#define REP_H

class Rep
{
public:
    int data_;
    Rep() : data_(-1) {}
    explicit Rep(int i) : data_(i) {}

    bool operator==(int i) const {return data_ == i;}
    bool operator==(const Rep& r) const {return data_ == r.data_;}

    Rep& operator*=(Rep x) {data_ *= x.data_; return *this;}
    Rep& operator/=(Rep x) {data_ /= x.data_; return *this;}
};

#endif  // REP_H
