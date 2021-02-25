#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
using std::cout;
using std::endl;
using std::hex;
using std::dec;
#include "systemc.h"

#if !defined(SC_VECTOR_UTILS_H)
  
int sc_main( int argc, char* argv[] )
{
    cout << endl << "The vector utiliies package is not implemented in this systemc library" 
         << endl << endl;
    return 0;
}

#else

using namespace sc_dt;

void dump( size_t n, sc_dt::sc_digit* digits )
{
    for ( int digit_i = n-1; digit_i >= 0; --digit_i )
    {
        cout << hex << std::setfill('0') << std::setw(8) << digits[digit_i] << " ";
    }
    cout << endl;
}

void load( size_t n, sc_dt::sc_digit* from, sc_dt::sc_digit* to )
{
    for ( size_t digit_i = 0; digit_i < n; ++digit_i ) { to[digit_i] = from[digit_i]; }
}

int sc_main( int argc, char* argv[] )
{
    sc_digit from_digits1[] = { 1, 0, 0, 0 };
    sc_digit to_digits[20];
    sc_digit from_digits2[] = { 0, 0, 0, 0x80000000 };

    dump(4, from_digits1);
    dump(4, from_digits2);

    std::cout << "---------- shift left ----------" << std::endl;
    for ( size_t i = 0; i < 4*32; ++i ) {
        load(4, from_digits1, to_digits);
        vector_shift_left( 4, to_digits, i );
        dump(4, to_digits);
    }

    std::cout << std::endl << "---------- shift right unsigned ----------" << std::endl;
    for ( size_t i = 0; i < 4*32; ++i ) {
        load(4, from_digits2, to_digits);
        vector_shift_right( 4, to_digits, i, 0 );
        dump(4, to_digits);
    }


    std::cout << std::endl << "---------- shift right signed ----------" << std::endl;
    for ( size_t i = 0; i < 4*32; ++i ) {
        load(4, from_digits2, to_digits);
        vector_shift_right( 4, to_digits, i, -1 );
        dump(4, to_digits);
    }


    cout << "Program completed" << endl;
    return 0;
}
#endif // #if !defined(SC_VECTOR_UTILS_H)
