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

  test.cpp --

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "systemc.h"

template<typename LV_T, typename BV_T>
void mytest(const LV_T& a, const BV_T& b) {
    cout << "---------------------------------------------------" << endl;
    cout << "mytest, lv a=" << a << endl;
    cout << "attempt convert to int: " << endl;
    int v = a.to_int();
    if (a.is_01() )  {
        cout << "   int value: " << v << endl;
    } else {
        cout << "   int value undefined (has X's or Z's)" << endl;
    }

    for (int i=0; i<4; i++) {
            cout << "a[" << i << "]=" << a[i]
                 << " : is_01=" << a[i].is_01() << endl;
        if (a[i].is_01()) {
            cout << "b[" << i << "]=" << b[i] << endl;
            // Check consistency:
            sc_assert(a[i].to_bool()==b[i]);
        } else {
            // Translation from X or Z to Boolean is undefined
        }
    }
}


int
sc_main( int, char*[] )
{
    sc_lv<4>    a = "01ZX";
    sc_uint<4>  b = a;

    mytest(a, b);

    a = "0101";
    b = a;

    mytest(a,b);

    a = "1010";
    b = a;

    mytest(a,b);

    return 0;
}
