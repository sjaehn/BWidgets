/* Any.hpp
 * Copyright (C) 2019 - 2022  Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BUTILITIES_ANY_HPP_
#define BUTILITIES_ANY_HPP_

#include <typeinfo>
#include <iostream>

namespace BUtilities
{

class Any
{
protected:
        struct Envelope
        {
                virtual ~Envelope () {}
                virtual Envelope* clone () {return new Envelope (*this);}
        };

        template <class T> struct Data : Envelope
        {
                Data (const T& t) : data (t) {}
                virtual ~Data () {}
                virtual Envelope* clone () override {return new Data<T> (*this);}
                T data;
        };

        Envelope* dataptr_ = nullptr;
        size_t dataTypeHash_ = typeid (void).hash_code ();

        Envelope* clone () const
        {
                if (dataptr_ == nullptr) return nullptr;
                return dataptr_->clone ();
        }

public:
        Any () {}
        Any (const Any& that) : dataTypeHash_ (that.dataTypeHash_)
        {dataptr_ = that.clone ();}

        ~Any () {if (dataptr_) delete dataptr_;}

        Any& operator= (const Any& that)
        {
                if (dataptr_) delete dataptr_;
                dataptr_ = that.clone ();
                dataTypeHash_ = that.dataTypeHash_;
                return *this;
        }

        size_t dataTypeHash () const {return dataTypeHash_;}

        template <class T> void set (const T& t)
        {
                if (dataptr_) delete dataptr_;
                dataptr_ = new Data<T> (t);
                dataTypeHash_ = typeid (T).hash_code ();
        }

        template <class T> T get () const
        {
                if ((!dataptr_) || (typeid (T).hash_code () != dataTypeHash_)) return T ();        // Return () better throw exception
                return ((Data<T>*)dataptr_)->data;
        }

};

template <class T> Any makeAny (const T& t)
{
        Any a;
        a.set<T> (t);
        return a;
}

}

#endif /* BUTILITIES_ANY_HPP_ */
