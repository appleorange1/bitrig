// The -*- C++ -*- float_complex class.
// Copyright (C) 1994 Free Software Foundation

// This file is part of the GNU ANSI C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// As a special exception, if you link this library with files
// compiled with a GNU compiler to produce an executable, this does not cause
// the resulting executable to be covered by the GNU General Public License.
// This exception does not however invalidate any other reasons why
// the executable file might be covered by the GNU General Public License.

// Written by Jason Merrill based upon the specification in the 27 May 1994
// C++ working paper, ANSI document X3J16/94-0098.

#ifndef __FCOMPLEX__
#define __FCOMPLEX__

#ifdef __GNUG__
#pragma interface "fcomplex"
#endif

extern "C++" {
class complex<float>
{
public:
  complex (float r = 0, float i = 0): re (r), im (i) { }
  explicit complex (const complex<double>& r);
  explicit complex (const complex<long double>& r);

  complex& operator+= (const complex&);
  complex& operator-= (const complex&);
  complex& operator*= (const complex&);
  complex& operator/= (const complex&);

  float real () const { return re; }
  float imag () const { return im; }
private:
  float re, im;

  // These functions are specified as friends for purposes of name injection;
  // they do not actually reference private members.
  friend float real (const complex& x) { return x.real (); }
  friend float imag (const complex& x) { return x.imag (); }
  friend complex operator + (const complex&, const complex&) __attribute__ ((const));
  friend complex operator + (const complex&, float) __attribute__ ((const));
  friend complex operator + (float, const complex&) __attribute__ ((const));
  friend complex operator - (const complex&, const complex&) __attribute__ ((const));
  friend complex operator - (const complex&, float) __attribute__ ((const));
  friend complex operator - (float, const complex&) __attribute__ ((const));
  friend complex operator * (const complex&, const complex&) __attribute__ ((const));
  friend complex operator * (const complex&, float) __attribute__ ((const));
  friend complex operator * (float, const complex&) __attribute__ ((const));
  friend complex operator / (const complex&, const complex&) __attribute__ ((const));
  friend complex operator / (const complex&, float) __attribute__ ((const));
  friend complex operator / (float, const complex&) __attribute__ ((const));
  friend bool operator == (const complex&, const complex&) __attribute__ ((const));
  friend bool operator == (const complex&, float) __attribute__ ((const));
  friend bool operator == (float, const complex&) __attribute__ ((const));
  friend bool operator != (const complex&, const complex&) __attribute__ ((const));
  friend bool operator != (const complex&, float) __attribute__ ((const));
  friend bool operator != (float, const complex&) __attribute__ ((const));
  friend complex polar (float, float) __attribute__ ((const));
  friend complex pow (const complex&, const complex&) __attribute__ ((const));
  friend complex pow (const complex&, float) __attribute__ ((const));
  friend complex pow (const complex&, int) __attribute__ ((const));
  friend complex pow (float, const complex&) __attribute__ ((const));
  friend istream& operator>> (istream&, complex&);
  friend ostream& operator<< (ostream&, const complex&);
};
} // extern "C++"

#endif
