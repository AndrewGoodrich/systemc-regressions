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

// #define OVERFLOW_CHECK(target) assert(save_actual == actual );
#define OVERFLOW_CHECK(target) 

template<int W, int D=1>
class Selection : public Selection<W-D,D>
{
  public:
    Selection( unsigned int fill ) : Selection<W-D,D>(fill)
    {
        sc_bigint<W> bigint_source;
        sc_signed    signed_source(W);

	size_t width = (W+31)/32;
	for ( size_t data_i = 0; data_i < width; ++data_i ) {
	    bigint_source = (bigint_source << 32) | fill; 
	    signed_source = (signed_source << 32) | fill; 
	}
	
	for ( int low = 0; low < W; ++low ) {
	    for ( int high = low; high < W; ++high ) {
	        int width = (high-low) + 1;
		sc_biguint<W> mask = -1; 
		sc_biguint<W> pre_mask = mask << width;
		mask = ~(mask << width);
		// sc_biguint<W> save_mask = mask;
		// OVERFLOW_CHECK( mask[0] )

		// test sc_biguint<W> selection:

                if ( 1 )
		{
		    sc_unsigned actual = bigint_source(high,low); 
		    sc_unsigned save_actual = actual;
		    OVERFLOW_CHECK( actual[0] )
		    OVERFLOW_CHECK( mask[0] )
		    sc_unsigned shifted_source = (bigint_source >> low);
		    OVERFLOW_CHECK( actual[0] )
		    OVERFLOW_CHECK( mask[0] )

		    // sc_unsigned expected = shifted_source & mask;
		    sc_biguint<W>  expected = shifted_source & mask;
		    OVERFLOW_CHECK( actual[0] )
		    OVERFLOW_CHECK( mask[0] )
		    if (0) {
		        std::cout << std::endl << "sc_bigint<" << W << ">(" << high << "," 
			          << low << "):" << endl;
		        std::cout << "shift & mask = expected" << std::endl;
		        std::cout << std::hex << shifted_source << " & " << mask << " = " 
                                  << expected << std::dec << std::endl;
                    }
		    if ( actual != expected ) {
			cout << "ERROR sc_biguint<" << W << ">(" << high << "," << low << "):" 
			     << endl;
			cout << "  width    " << width << endl;
			dump( "  expected ", expected );
			dump( "  actual   " ,actual );
			dump( "  pre_mask ", pre_mask );
			dump( "  mask     ", mask );
			dump( "  shift    ", shifted_source );
			dump( "  source   ", signed_source );
			dump( "  saveact  ", save_actual );
			assert(0);
		    }
		}

		// test sc_unsigned selection:

		{
		    sc_unsigned actual = signed_source(high,low);
		    sc_unsigned shifted_source = (signed_source >> low);
		    sc_unsigned expected = shifted_source & mask;
		    if (0) {
		        std::cout << std::endl << "sc_signed(" << W << ")(" << high << "," 
			          << low << "):" << endl;
		        std::cout << "shift & mask = expected" << std::endl;
		        std::cout << std::hex << shifted_source << " & " << mask << " = " 
                                  << expected << std::dec << std::endl;
                    }
		    if ( actual != expected ) {
			cout << "ERROR sc_unsigned(" << W << ")(" << high << "," << low << "):" 
			     << endl;
			cout << "  width    " << width << endl;
			dump( "  expected ", expected );
			dump( "  actual   " ,actual );
			dump( "  pre_mask ", pre_mask );
			dump( "  mask     ", mask );
			dump( "  shift    ", shifted_source );
			dump( "  source   ", signed_source );
                        assert(0);
		    } 
		}

	    }
        }
    }
};

template<int D>
class Selection<0,D>
{
  public:
    Selection(unsigned int fill ) {}
};

int sc_main( int argc, char* argv[] )
{
    if ( true )
    {
	cout << "Selection(0x" << std::hex << ~0u << std::dec << ")" << std::endl;
	Selection<128> x(~0u);
	Selection<2000,200> y1(~0u);
    }
    if ( true )
    {
	cout << "Selection(0x" << std::hex << 0x55555555u << std::dec << ")" << std::endl;
	Selection<128> x1(0x55555555u);
	Selection<2000,200> y(0x55555555u);
    }
    if ( true )
    {
	cout << "Selection(0x" << std::hex << 0xaaaaaaaau << std::dec << ")" << std::endl;
	Selection<128> x2(0xaaaaaaaau);
	Selection<1200,120> y2(0xaaaaaaaau);
    }
    if ( true )
    {
	cout << "Selection(0x" << std::hex << 0x99999999u << std::dec << ")" << std::endl;
	Selection<128> x1(0x99999999u);
	Selection<1200,120> y2(0x99999999u);
    }
    if ( true )
    {
	cout << "Selection(0x" << std::hex << 0x66666666u << std::dec << ")" << std::endl;
	Selection<128> x1(0x66666666u);
	Selection<1200,120> y2(0x66666666u);
    }
    cout << "Program completed" << endl;

    return 0;
}
