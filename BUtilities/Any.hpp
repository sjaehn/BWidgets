/* Any.hpp
 * Copyright (C) 2019 - 2023  Sven Jähnichen
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

/**
 *  @brief  Container to type-safely take up the content of any copy 
 *  constructible type.
 *
 *  @note  Similar classes are in the std (C++>=17) and boost.
 */
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
        /**
         *  @brief  Constructs an empty Any object.
         * 
         */
        Any () {}

        /**
         *  @brief  Constructs a new Any object from another object.
         *  @param that  Other object.
         */
        Any (const Any& that) : dataTypeHash_ (that.dataTypeHash_)
        {dataptr_ = that.clone ();}

        ~Any () {if (dataptr_) delete dataptr_;}

        /**
         *  @brief  Copy assigns to the content of another object.
         *  @param that  Other object.
         *  @return  Content of this object.
         */
        Any& operator= (const Any& that)
        {
                if (dataptr_) delete dataptr_;
                dataptr_ = that.clone ();
                dataTypeHash_ = that.dataTypeHash_;
                return *this;
        }

        /**
         *  @brief  Gets the hash code of the containing data.
         *  @return  Hash code.
         */
        size_t dataTypeHash () const {return dataTypeHash_;}

        /**
         *  @brief  Sets the content of this Any object.
         *  @tparam T  Data type of the content.
         *  @param t  Data.
         */
        template <class T> 
        void set (const T& t)
        {
                if (dataptr_) delete dataptr_;
                dataptr_ = new Data<T> (t);
                dataTypeHash_ = typeid (T).hash_code ();
        }

        /**
         *  @brief  Gets the content of this Any object.
         *  @tparam T  Data type of the content.
         *  @return  Containing data or default constructed data object if
         *  data types don't match.
         */
        template <class T> 
        T get () const
        {
                if ((!dataptr_) || (typeid (T).hash_code () != dataTypeHash_)) return T ();        // Return () better throw exception
                return ((Data<T>*)dataptr_)->data;
        }

};

/**
 *  @brief  Creates and defines an Any object. 
 *  @tparam T  Data type.
 *  @param t  Data.
 *  @return  Content of the created object.
 */
template <class T> 
Any makeAny (const T& t)
{
        Any a;
        a.set<T> (t);
        return a;
}

}

#endif /* BUTILITIES_ANY_HPP_ */
