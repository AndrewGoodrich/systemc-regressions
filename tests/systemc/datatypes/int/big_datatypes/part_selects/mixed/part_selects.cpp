#include <stdio.h>
#include <cstdlib>
#include <iostream>
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
    cout << endl 
         << "Skipping his test because it runs too long with non-2's-complement systemc library"
         << endl << endl;
    return 0;
}

#else

#include "isaac.h"

#define COUNT_N 100

QTIsaac<8> rng;         // Platform independent random number generator.

template<typename T>
void dump( const char* prefix, const T& value ) 
{
    cout << prefix << hex << value << dec 
#if defined(SC_VECTOR_UTILS_H)
         << " hod " << value.get_hod() << " bits "
	 << value.get_actual_width()
#endif                       
	 << endl;
}

template<typename T>
inline void load( int bits_n,  T& target, unsigned int fill )
{
    int target_n = DIV_CEIL(bits_n);

    target = fill;
    for ( int target_i = 1; target_i < target_n; ++target_i ) {
        target = (target << 32) + fill;
    }
}

void test_big( int width, unsigned int fill )
{
    sc_signed    signed_source(width);   // unsigned source to part select from.
    sc_unsigned  unsigned_source(width); // signed source to part select from.

    // Initialize sources:

    load(width, signed_source, fill);
    load(width, unsigned_source, fill);

    // Test sc_unsigned destination:

    for ( int right = 0; right < width; ++right ) {
	for ( int left = right; left < width; ++left ) {
            sc_unsigned actual_from_signed_l_r = signed_source(left,right);
            sc_unsigned actual_from_unsigned_l_r = unsigned_source(left,right);
	    if ( actual_from_signed_l_r != actual_from_unsigned_l_r ) {
		cout << "ERROR unsigned=XXsigned(" << width << ")(" << left << "," << right 
		     << "):" << endl;
		cout << "  width    " << width << endl;
		dump( "  actual from signed   ", actual_from_signed_l_r );
		dump( "  actual from unsigned ", actual_from_unsigned_l_r );
		dump( "  signed source        ", unsigned_source );
		dump( "  unsigned source      ", signed_source );
		assert(0);
	    }

            sc_unsigned actual_from_signed_r_l = signed_source(right,left);
            sc_unsigned actual_from_unsigned_r_l = unsigned_source(right,left);
	    if ( actual_from_signed_r_l != actual_from_unsigned_r_l  ) {
		cout << "ERROR unsigned=XXsigned(" << width << ")(" << right << "," << left 
		     << "):" << endl;
		cout << "  width    " << width << endl;
		dump( "  actual from signed   " , actual_from_signed_r_l );
		dump( "  actual from unsigned " , actual_from_unsigned_r_l );
		dump( "  signed source        ", unsigned_source );
		    assert(0);
	    }
	}
    }

    // Test sc_signed destination:

    for ( int right = 0; right < width; ++right ) {
	for ( int left = right; left < width; ++left ) {
            sc_signed actual_from_signed_l_r( signed_source(left,right) );
            sc_signed actual_from_unsigned_l_r( unsigned_source(left,right) );
	    if ( actual_from_signed_l_r != actual_from_unsigned_l_r ) {
                        cout << "ERROR signed=XXsigned(" << width << ")(" << left << "," << right 
                             << "):" << endl;
                        cout << "  width    " << width << endl;
                        dump( "  actual from signed   " , actual_from_signed_l_r );
                        dump( "  actual from unsigned " , actual_from_unsigned_l_r );
                        dump( "  signed source        ", unsigned_source );
                        dump( "  unsigned source      ", signed_source );
                        assert(0);
	    }

            sc_signed actual_from_signed_r_l( signed_source(right,left) );
            sc_signed actual_from_unsigned_r_l( unsigned_source(right,left) );
	    if ( actual_from_signed_r_l != actual_from_unsigned_r_l ) {
                        cout << "ERROR signed=XXsigned(" << width << ")(" << right << "," << left 
                             << "):" << endl;
                        cout << "  width    " << width << endl;
                        dump( "  actual from signed   " , actual_from_signed_r_l );
                        dump( "  actual from unsigned " , actual_from_unsigned_r_l );
                        dump( "  signed source        ", unsigned_source );
                        assert(0);
	    }
	}
    }
}

void test_small( int width, unsigned int fill )
{
    sc_int_base  int_source(width);      // sc_int source to part select from.
    sc_uint_base uint_source(width);     // sc_uint source to part select from.

    // Initialize sources:

    load(width, int_source, fill);
    load(width, uint_source, fill);

    // Test sc_unsigned destination:

    for ( int right = 0; right < width; ++right ) {
	for ( int left = right; left < width; ++left ) {
            sc_unsigned actual_from_int_l_r( int_source(left,right) );
            sc_unsigned actual_from_uint_l_r( uint_source(left,right) );
	    if ( actual_from_int_l_r != actual_from_uint_l_r ) {
		cout << "ERROR unsigned=XXint(" << width << ")(" << left << "," << right 
		     << "):" << endl;
		cout << "  width    " << width << endl;
		dump( "  actual from int      ", actual_from_int_l_r );
		dump( "  actual from uint     ", actual_from_uint_l_r );
		assert(0);
	    }
	}
    }

    // Test sc_signed destination:

    for ( int right = 0; right < width; ++right ) {
	for ( int left = right; left < width; ++left ) {
            sc_signed actual_from_int_l_r( int_source(left,right) );
            sc_signed actual_from_uint_l_r( uint_source(left,right) );
	    if ( actual_from_int_l_r != actual_from_uint_l_r ) {
		cout << "ERROR signed=XXint(" << width << ")(" << left << "," << right 
		     << "):" << endl;
		cout << "  width    " << width << endl;
		dump( "  actual from int      ", actual_from_int_l_r );
		dump( "  actual from uint     ", actual_from_uint_l_r );
		assert(0);
	    }
	}
    }
}

int sc_main( int argc, char* argv[] )
{
    for ( int width = 1; width < 129; ++width )  {
	if ( width < 65 ) {
	    test_small( width, 0xffffffffu );
	    test_small( width, 0xaaaaaaaau );
	    test_small( width, 0x99999999u );
	    test_small( width, 0x66666666u );
	    test_small( width, 0x55555555u );
	}
        test_big( width, 0xffffffffu );
        test_big( width, 0xaaaaaaaau );
        test_big( width, 0x99999999u );
        test_big( width, 0x66666666u );
        test_big( width, 0x55555555u );

	if ( width < 65 ) {
	    for ( size_t test_i = 0; test_i < COUNT_N; ++test_i ) {
		test_small( width, rng.rand() );
	    }
	}
	for ( size_t test_i = 0; test_i < COUNT_N; ++test_i ) {
	    test_big( width, rng.rand() );
	}

    }

    cout << "Big value mixed part selection completed" << endl;
    return 0;
}
#endif
