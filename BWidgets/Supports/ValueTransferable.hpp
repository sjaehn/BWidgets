/* ValueTransferable.hpp
 * Copyright (C) 2018 - 2022  Sven Jähnichen
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

#ifndef BWIDGETS_VALUETRANSFERABLE_HPP_
#define BWIDGETS_VALUETRANSFERABLE_HPP_

#include "Support.hpp"
#include <functional>

namespace BWidgets
{

/**
 *  @brief  Support of transfer functions.
 *  @tparam T  Value type.
 *
 *  Transfer functions are intented to be used to transfer values from an
 *  external context (e. g., frequencies with a logarithmic distribution) to
 *  an internal context (e. g., a slider with linear distribution). Transfer
 *  functions MUST be biunique. Transfer functions are called from the 
 *  Widget visualization methods (e. g. @c draw() ). 
 *
 *  Value type MUST be the same type as in Valuable.
 */
template <class T>
class ValueTransferable : public Support
{

public:

    /**
     *  @brief  Default function which passes a value. 
     *  @param x  Value.
     *  @return  Value (= @a x ).
     */
    static T noTransfer (const T& x);

protected:
    std::function<T (const T& x)> transfer_ = noTransfer;
    std::function<T (const T& x)> reTransfer_ = noTransfer;

public:

    /**
     *  @brief Constructs a ValueTransferable object.
     *  @param transferFunc  Transfer function.
     *  @param reTransferFunc  Re-transfer function.
     */
    ValueTransferable (std::function<T (const T& x)> transferFunc = noTransfer, std::function<T (const T& x)> reTransferFunc = noTransfer);

    /**
     *  @brief  Switch the support for value transfer on/off.
     *  @param status  True if on, otherwise false.
     */
    void setValueTransferable (const bool status);

    /**
     *  @brief  Information about the support for value transfer.
     *  @return  True if on, otherwise false.
     */
    bool isValueTransferable () const;

    /**
     *  @brief  Sets the transfer function.
     *  @param func  Transfer function.
     *
     *  The transfer function is used
     *  to transfer a value from an external context (e. g., frequencies with a
     *  logarithmic distribution) to an internal context (e. g., a slider with 
     *  linear distribution). In this case a possible transfer function would be:
     *  @code
     *  [] (const double& x) {return log10 (x);}
     *  @endcode
     *
     *  The transfer function (and its re-transfer function) MUST be biunique.
     */
    virtual void setTransferFunction (std::function<T (const T& x)> func);

    /**
     *  @brief  Gets the transfer function.
     *  @param func  Transfer function.
     */
    virtual std::function<T (const T& x)> getTransferFunction () const;

    /**
     *  @brief  Sets the re-transfer function.
     *  @param func  Re-transfer function.
     *
     *  The re-transfer function is used to transfer a value from an internal 
     *  context (e. g., a
     *  position within a slider with linear distribution) to an external
     *  context (e. g., frequencies with a logarithmic distribution). In this
     *  case a possible re-transfer function would be:
     *  @code
     *  [] (const double& x) {return pow (10, x);}
     *  @endcode
     *
     *  The transfer function (and its re-transfer function) MUST be biunique.
     */
    virtual void setReTransferFunction (std::function<T (const T& x)> func);

    /**
     *  @brief  Gets the re-transfer function.
     *  @param func  Re-transfer function.
     */
    virtual std::function<T (const T& x)> getReTransferFunction () const;

    /**
     *  @brief  Transfers a value.
     *  @param x  Value
     *  @return  Transfered value. 
     *
     *  The transfer function is used to transfer
     *  a value from an external context (e. g., frequencies with a logarithmic
     *  distribution) to an internal context (e. g., a slider with linear 
     *  distribution). In this case a possible transfer function would be:
     *  @code
     *  [] (const double& x) {return log10 (x);}
     *  @endcode
     */
    T transfer (const T& x);

    /**
     *  @brief  Re-transfers a value.
     *  @param x  Value
     *  @return  Re-transfered value. 
     *
     *  The re-transfer function is used to transfer
     *  a value from an internal context (e. g., a slider with linear 
     *  distribution) to an external context (e. g., frequencies with a 
     *  logarithmic distribution). In this case a possible re-transfer function 
     *  would be:
     *  @code
     *  [] (const double& x) {return pow (10, x);}
     *  @endcode
     */
    T reTransfer (const T& x);

};

template <class T>
inline ValueTransferable<T>::ValueTransferable (std::function<T (const T& x)> transferFunc, std::function<T (const T& x)> reTransferFunc) :
    Support(),
    transfer_ (transferFunc),
    reTransfer_ (reTransferFunc)
{

}

template <class T>
inline void ValueTransferable<T>::setValueTransferable (const bool status)
{
    setSupport(status);
}

template <class T>
inline bool ValueTransferable<T>::isValueTransferable () const 
{
    return getSupport();
}

template <class T>
inline T ValueTransferable<T>::noTransfer (const T& x)
{
    return x;
}

template <class T>
inline void ValueTransferable<T>::setTransferFunction (std::function<T (const T& x)> func)
{
    transfer_ = func;
}

template <class T>
inline std::function<T (const T& x)> ValueTransferable<T>::getTransferFunction () const
{
    return transfer_;
}

template <class T>
inline void ValueTransferable<T>::setReTransferFunction (std::function<T (const T& x)> func)
{
    reTransfer_ = func;
}

template <class T>
inline std::function<T (const T& x)> ValueTransferable<T>::getReTransferFunction () const
{
    return reTransfer_;
}

template <class T>
inline T ValueTransferable<T>::transfer (const T& x)
{
    return transfer_ (x);
}

template <class T>
inline T ValueTransferable<T>::reTransfer (const T& x)
{
    return reTransfer_ (x);
}

}
#endif /* BWIDGETS_VALUETRANSFERABLE_HPP_ */