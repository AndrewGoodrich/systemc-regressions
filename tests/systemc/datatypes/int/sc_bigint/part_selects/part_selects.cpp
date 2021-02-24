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

void dump( const std::string& prefix, const sc_unsigned& value )
{
    cout << prefix << hex << value << dec
#if defined(SC_VECTOR_UTILS_H)
         << " hod " << value.get_hod() << " bits "
         << value.get_actual_width()
#endif
         << endl;
}

template<int W>
class Selection : public Selection<W-1>
{
  public:
    Selection( unsigned int fill ) : Selection<W-1>(fill)
    {
        sc_bigint<W> bigint_source;
        sc_signed   signed_source(W);
	bigint_source = fill;
	signed_source = fill;
	if ( W > 32 ) { 
	    bigint_source = (bigint_source << 32) | fill; 
	    signed_source = (signed_source << 32) | fill; 
	}
	if ( W > 64 ) { 
	    bigint_source = (bigint_source << 32) | fill; 
	    signed_source = (signed_source << 32) | fill; 
	}
	if ( W > 96 ) { 
	    bigint_source = (bigint_source << 32) | fill; 
	    signed_source = (signed_source << 32) | fill; 
	}
	
	for ( int low = 0; low < W; ++low ) {
	    for ( int high = low; high < W; ++high ) {
	        int width = (high-low) + 1;
		sc_biguint<W> mask = -1;
		mask = ~(mask << width);

		// test sc_biguint<W> selection:

		{
		    sc_unsigned actual = bigint_source(high,low);
		    sc_unsigned shifted_source = (bigint_source >> low);
		    sc_unsigned expected = shifted_source & mask;
		    if (0) {
		        std::cout << std::endl << "sc_biguint<" << W << ">(" << high << "," 
			          << low << "):" << endl;
		        std::cout << "shift & mask = expected" << std::endl;
		        std::cout << std::hex << shifted_source << " & " << mask << " = " 
			          << expected << std::dec << std::endl;
                    }
		    if ( actual != expected ) {
			cout << "ERROR sc_bigint<" << W << ">(" << high << "," << low << "):" 
			     << endl;
                        dump( "  expected ", expected );
                        dump( "  actual   " ,actual );
                        dump( "  mask     ", mask );
			dump( "  shift    " , shifted_source );
			cout << "  bigint_source   " << hex << bigint_source << dec << endl;
		    }
		}

		// test sc_signed selection:

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
			cout << "ERROR sc_signed(" << W << ")(" << high << "," << low << "):" 
			     << endl;
                        dump( "  expected ", expected );
                        dump( "  actual   " ,actual );
                        dump( "  mask     ", mask );
			dump( "  shift    ", shifted_source );
			cout << "  signed_source   " << hex << signed_source << dec << endl;
		    } 
		}

	    }
        }
    }
};

template<>
class Selection<1>
{
  public:
    Selection(unsigned int fill ) {}
};

int sc_main( int argc, char* argv[] )
{
    cout << "Selection(0x" << std::hex << ~0u << std::dec << ")" << std::endl;
    Selection<128>(~0u);
    cout << "Selection(0x" << std::hex << 0x55555555u << std::dec << ")" << std::endl;
    Selection<128>(0x55555555u);
    cout << "Selection(0x" << std::hex << 0xaaaaaaaau << std::dec << ")" << std::endl;
    Selection<128>(0xaaaaaaaau);
    cout << "Selection(0x" << std::hex << 0x99999999u << std::dec << ")" << std::endl;
    Selection<128>(0x99999999u);
    cout << "Selection(0x" << std::hex << 0x66666666u << std::dec << ")" << std::endl;
    Selection<128>(0x66666666u);
    cout << "Program completed" << endl;

    return 0;
}
