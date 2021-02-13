/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  test03.cpp --

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

// test of assigning sc_lv_base to the integer types

#include "systemc.h"

template<typename T1, typename T2>
void check_bits(const T1& bv1, const T2& bv2, const sc_lv<4>& lv)
{
    cout << "checking bits  " << flush;
    for (int i=0; i<4; i++) {
        if (lv[i].is_01()) {
            if (i<bv1.length()) {
                sc_assert(bv1[i]==lv[i].to_bool());
                cout << "." << flush;
            }
            if (i<bv2.length()) {
                sc_assert(bv2[i]==lv[i].to_bool());
                cout << "," << flush;
            }
        }
    }
    cout << " good!" << endl;
}

void
test_smaller( const sc_lv<4>& lv_one, const sc_lv<4>& lv_two )
{
    cout << "*** smaller ***" << endl;
    {
        sc_int<8> a( lv_one );
        sc_int<8> b( lv_two );
        sc_int<8> c;
        sc_int<8> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
    cout << endl;
    {
        sc_uint<8> a( lv_one );
        sc_uint<8> b( lv_two );
        sc_uint<8> c;
        sc_uint<8> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
    }
    cout << endl;
    {
        sc_bigint<8> a( lv_one );
        sc_bigint<8> b( lv_two );
        sc_bigint<8> c;
        sc_bigint<8> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
    cout << endl;
    {
        sc_biguint<8> a( lv_one );
        sc_biguint<8> b( lv_two );
        sc_biguint<8> c;
        sc_biguint<8> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
}

void
test_equal( const sc_lv<4>& lv_one, const sc_lv<4>& lv_two )
{
    cout << "*** equal ***" << endl;
    {
        sc_int<4> a( lv_one );
        sc_int<4> b( lv_two );
        sc_int<4> c;
        sc_int<4> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
    cout << endl;
    {
        sc_uint<4> a( lv_one );
        sc_uint<4> b( lv_two );
        sc_uint<4> c;
        sc_uint<4> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
    cout << endl;
    {
        sc_bigint<4> a( lv_one );
        sc_bigint<4> b( lv_two );
        sc_bigint<4> c;
        sc_bigint<4> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
    cout << endl;
    {
        sc_biguint<4> a( lv_one );
        sc_biguint<4> b( lv_two );
        sc_biguint<4> c;
        sc_biguint<4> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
}

void
test_larger( const sc_lv<4>& lv_one, const sc_lv<4>& lv_two )
{
    cout << "*** larger ***" << endl;
    {
        sc_int<2> a( lv_one );
        sc_int<2> b( lv_two );
        sc_int<2> c;
        sc_int<2> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
    cout << endl;
    {
        sc_uint<2> a( lv_one );
        sc_uint<2> b( lv_two );
        sc_uint<2> c;
        sc_uint<2> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
    cout << endl;
    {
        sc_bigint<2> a( lv_one );
        sc_bigint<2> b( lv_two );
        sc_bigint<2> c;
        sc_bigint<2> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
    cout << endl;
    {
        sc_biguint<2> a( lv_one );
        sc_biguint<2> b( lv_two );
        sc_biguint<2> c;
        sc_biguint<2> d;
        c = lv_one;
        d = lv_two;
        if (lv_one.is_01()) {
            cout << a << endl;
            cout << c << endl;
        }
        if (lv_two.is_01()) {
            cout << b << endl;
            cout << d << endl;
        }
        check_bits(a,c,lv_one);
        check_bits(b,d,lv_two);
    }
}

int
sc_main( int, char*[] )
{
    sc_lv<4> lv_one( "01ZX" );
    sc_lv<4> lv_two( "1010" );

    test_smaller( lv_one, lv_two );
    test_equal  ( lv_one, lv_two );
    test_larger ( lv_one, lv_two );

    return 0;
}
