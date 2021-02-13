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

  datatypes.cpp --

  Original Author: Rocco Jonack, Synopsys, Inc., 1999-07-30

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/


#include "datatypes.h"


template<typename T_IN, typename SHIFT_T, typename T_OUT>
void do_shift(const T_IN& tmp, SHIFT_T shift, T_OUT& tmpr)
{
   if (shift>=0) {
     tmpr = tmp << shift;
   } else {
     tmpr = tmp >> -shift;
   }
}

void datatypes::entry()
{
  sc_bigint<8>    tmp1;
  sc_bigint<8>    tmp1r;
  sc_biguint<8>   tmp2;
  sc_biguint<8>   tmp2r;
  long            tmp3;
  long            tmp3r;
  int             tmp4;
  int             tmp4r;
  short           tmp5;
  short           tmp5r;
  char            tmp6;
  char            tmp6r;

// define 1 dimensional array
   unsigned int  tmp7[2];
// define sc_bool_vector
  sc_bv<4>	tmp10;
  tmp10[3] = 0;  tmp10[2] = 1;  tmp10[1] = 0;  tmp10[0] = 1;

// define 2 dimentional array
   sc_bv<1> tmp11[2];

// reset_loop
  if (reset.read() == true) {
    out_valid.write(false);
    out_ack.write(false);
    wait();
  } else wait();

//
// main loop
//

// initialization of sc_array

   tmp7[0] = 3;
   tmp7[1] = 12;
   tmp11[0][0] = "1";
   tmp11[1][0] = "0";


 while(1) {
    while(in_valid.read()==false) wait();

    //reading the inputs
    tmp1 = in_value1.read();
    tmp2 = in_value2.read();
    tmp3 = in_value3.read();
    tmp4 = in_value4.read();
    tmp5 = in_value5.read();
    tmp6 = in_value6.read();

    out_ack.write(true);

    //execute mixed data type shift operations
    sc_bigint<8>  shift1 = (tmp7[0] % 8);
    sc_biguint<8> shift2 = 2;
    long          shift3 = 1;
    int           shift4 = (tmp7[1] % 16);
    short         shift5 = ((unsigned int)(tmp1.to_int()) % 32);
    char          shift6 = 1;

    do_shift(tmp1,shift1,tmp1r);
    do_shift(tmp2,shift2,tmp2r);
    do_shift(tmp3,shift3,tmp3r);
    do_shift(tmp4,shift4,tmp4r);
    do_shift(tmp3,shift5,tmp5r);
    do_shift(tmp6,shift6,tmp6r);

    //write outputs
    out_value1.write(tmp1r);
    out_value2.write(tmp2r);
    out_value3.write(tmp3r);
    out_value4.write(tmp4r);
    out_value5.write(tmp5r);
    out_value6.write(tmp6r);

    out_valid.write(true);
    wait();
    out_ack.write(false);
    out_valid.write(false);

    shift1 = (tmp7[0] % 8);
    shift2 = (unsigned int)(tmp4 % 8);
    shift3 = (short)(tmp5 % 32);
    shift4 = 2;
    shift5 = ((unsigned int)(tmp5) % 16);
    shift6 = (tmp2.to_uint() % 32);

    //execute mixed data type shift operations
    do_shift(tmp1,shift1,tmp1r);
    do_shift(tmp2,shift2,tmp2r);
    do_shift(tmp3,shift3,tmp3r);
    do_shift(tmp4,shift4,tmp4r);
    do_shift(tmp3,shift5,tmp5r);
    do_shift(tmp6,shift6,tmp6r);

    //write outputs
    out_value1.write(tmp1r);
    out_value2.write(tmp2r);
    out_value3.write(tmp3r);
    out_value4.write(tmp4r);
    out_value5.write(tmp5r);
    out_value6.write(tmp6r);

    out_valid.write(true);
    wait();
    out_ack.write(false);
    out_valid.write(false);

 }

} // End

