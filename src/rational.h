/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the class library                   */
/*       SoPlex --- the Sequential object-oriented simPlex.                  */
/*                                                                           */
/*    Copyright (C) 1996-2013 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SoPlex is distributed under the terms of the ZIB Academic Licence.       */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SoPlex; see the file COPYING. If not email to soplex@zib.de.  */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file  rational.h
 * @brief Wrapper for GMP types.
 */
#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <math.h>
#include <assert.h>
#include <iostream>
#include <string>

#include "spxdefines.h"

#ifdef SOPLEX_WITH_GMP
#include "gmp.h"
#endif

#ifdef SOPLEX_WITH_GMPXX
#include "gmp.h"
#include "gmpxx.h"
#endif

namespace soplex
{
/**@brief   Wrapper for GMP type mpq_class.
 * @ingroup Algebra
 *
 * We wrap mpq_class so that we can replace it by a double type if GMP is not available.
 */

/// If compiled with GMP support, Rational is defined as mpq_class.
   class Rational
   {
   private:
      class Private;
      Private* dpointer;

   public:

      //**@name Construction and destruction */
      //@{

      /// default constructor
      Rational();

      /// copy constructor
      Rational(const Rational& r);

      /// copy assignment operator
      Rational& operator=(const Rational&);

      /// constructor from long double
      Rational(const long double& r);

      /// constructor from double
      Rational(const double& r);

      ///constructor from int
      Rational(const int& i);

#ifdef SOPLEX_WITH_GMP

      /// constructor from mpq_t
      Rational(const mpq_t& q);

#endif

#ifdef SOPLEX_WITH_GMPXX

      /// constructor from mpq_class
      Rational(const mpq_class& q);

      /// constructor from mpq_t
      Rational(const mpq_t& q);
#endif

      /// destructor
      ~Rational();

      //@}


      //**@name Typecasts */
      //@{

      /// typecasts Rational to double (only allows explicit typecasting)
      explicit operator double() const;

      /// typecasts Rational to long double (only allows explicit typecasting)
      explicit operator long double() const;

      //@}


      //**@name Arithmetic operators */
      //@{

      /// addition operator
      Rational operator+(const Rational& r) const;

      /// addition assignment operator
      Rational operator+=(const Rational& r) const;

      /// addition operator for doubles
      Rational operator+(const double& r) const;

      /// addition assignment operator  for doubles
      Rational operator+=(const double& r) const;

      /// subtraction operator
      Rational operator-(const Rational& r) const;

      /// subtraction assignment operator
      Rational operator-=(const Rational& r) const;

      /// subtraction operator for doubles
      Rational operator-(const double& r) const;

      /// subtraction assignment operator for doubles
      Rational operator-=(const double& r) const;

      /// multiplication operator
      Rational operator*(const Rational& r) const;

      /// multiplication assignment operator operator
      Rational operator*=(const Rational& r) const;

      /// multiplication operator for doubles
      Rational operator*(const double& r) const;

      /// multiplication assignment operator for doubles
      Rational operator*=(const double& r) const;

      /// division operator
      Rational operator/(const Rational& r) const;

      /// division assignment operator
      Rational operator/=(const Rational& r) const;

      /// division operator for doubles
      Rational operator/(const double& r) const;

      /// division assignment operator for doubles
      Rational operator/=(const double& r) const;

      //@}


      //**@name Methods for checking exactness of doubles  */
      //@{

      /// checks if \p d is the closest number that can be represented by double
      bool isNextTo(const double& d);

      /// checks if \p d is exactly equal to the Rational and if not, if it is one of the two adjacent doubles
      bool isAdjacentTo(const double& d);

      //@}


      //**@name Conversion from and to String */
      //@{

      /// read Rational from string
      bool readString(const char* s);

      friend std::string rationalToString(const Rational& r, const bool asfloat);
      friend bool readStringRational(const char* s, Rational& value);
      friend std::ostream& operator<<(std::ostream& os, const Rational& q);

      friend bool operator!=(const Rational& r, const Rational& s);
      friend bool operator==(const Rational& r, const Rational& s);
      friend bool operator<(const Rational& r, const Rational& s);
      friend bool operator<=(const Rational& r, const Rational& s);
      friend bool operator>(const Rational& r, const Rational& s);
      friend bool operator>=(const Rational& r, const Rational& s);

      friend bool operator!=(const Rational& r, const double& s);
      friend bool operator==(const Rational& r, const double& s);
      friend bool operator<(const Rational& r, const double& s);
      friend bool operator<=(const Rational& r, const double& s);
      friend bool operator>(const Rational& r, const double& s);
      friend bool operator>=(const Rational& r, const double& s);

      friend bool operator!=(const double& r, const Rational& s);
      friend bool operator==(const double& r, const Rational& s);
      friend bool operator<(const double& r, const Rational& s);
      friend bool operator<=(const double& r, const Rational& s);
      friend bool operator>(const double& r, const Rational& s);
      friend bool operator>=(const double& r, const Rational& s);

      friend Rational operator+(const double& d, const Rational& r);
      friend Rational operator-(const double& d, const Rational& r);
      friend Rational operator*(const double& d, const Rational& r);
      friend Rational operator/(const double& d, const Rational& r);

      friend Rational abs(const Rational& r);
      friend int sign(const Rational& r);
      friend Rational operator-(const Rational& q);
   };

   /// convert rational number to string
   std::string rationalToString(const Rational& r, const bool asfloat = true);

   /// read Rational from string
   bool readStringRational(const char* s, Rational& value);

   /// print Rational
   std::ostream& operator<<(std::ostream& os, const Rational& r);

   //@}


   //**@name Relational operators */
   //@{

   /// equality operator
   bool operator==(const Rational& r, const Rational& s);

   /// inequality operator
   bool operator!=(const Rational& r, const Rational& s);

   /// less than operator
   bool operator<(const Rational& r, const Rational& s);

   /// less than or equal to operator
   bool operator<=(const Rational& r, const Rational& s);

   /// greater than operator
   bool operator>(const Rational& r, const Rational& s);

   /// greater than or equal to operator
   bool operator>=(const Rational& r, const Rational& s);



   /// equality operator for Rational and double
   bool operator==(const Rational& r, const double& s);

   /// inequality operator for Rational and double
   bool operator!=(const Rational& r, const double& s);

   /// less than operator for Rational and double
   bool operator<(const Rational& r, const double& s);

   /// less than or equal to operator for Rational and double
   bool operator<=(const Rational& r, const double& s);

   /// greater than operator for Rational and double
   bool operator>(const Rational& r, const double& s);

   /// greater than or equal to operator for Rational and double
   bool operator>=(const Rational& r, const double& s);



   /// equality operator for double and Rational
   bool operator==(const double& r, const Rational& s);

   /// inequality operator for double and Rational
   bool operator!=(const double& r, const Rational& s);

   /// less than operator for double and Rational
   bool operator<(const double& r, const Rational& s);

   /// less than or equal to operator for double and Rational
   bool operator<=(const double& r, const Rational& s);

   /// greater than operator for double and Rational
   bool operator>(const double& r, const Rational& s);

   /// greater than or equal to operator for double and Rational
   bool operator>=(const double& r, const Rational& s);

   //@}


   //**@name Non-member arithmetic operators and functions */
   //@{

   /// addition operator for double and Rational
   Rational operator+(const double& d, const Rational& r);

   /// addition operator for double and Rational
   Rational operator+(const double& d, const Rational& r);

   /// addition operator for double and Rational
   Rational operator+(const double& d, const Rational& r);

   /// addition operator for double and Rational
   Rational operator+(const double& d, const Rational& r);

   /// absolute function
   Rational abs(const Rational& r);

   /// Sign function; returns 1 if r > 0, 0 if r = 0, and -1 if r < 0.
   int sign(const Rational& r);

   /// Negation.
   Rational operator-(const Rational& r);

   //@}

} // namespace soplex

#endif // _RATIONAL_H_

//-----------------------------------------------------------------------------
//Emacs Local Variables:
//Emacs mode:c++
//Emacs c-basic-offset:3
//Emacs tab-width:8
//Emacs indent-tabs-mode:nil
//Emacs End:
//-----------------------------------------------------------------------------
