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

#define DEBUGF false

template<int W>
class Selection : public Selection<W-1>
{
  public:
    Selection( unsigned int fill ) : Selection<W-1>(fill)
    {
        sc_bigint<W> source;
	source = fill;
	if ( W > 32 ) { source = (source << 32) | fill; }
	if ( W > 64 ) { source = (source << 32) | fill; }
	if ( W > 96 ) { source = (source << 32) | fill; }
	
	for ( int low = 0; low < W; ++low ) {
	    for ( int high = low; high < W; ++high ) {
	        int width = (high-low) + 1;
		sc_biguint<W> mask = -1;
		if (DEBUGF) std::cout << std::endl << "sc_bigint<" << W << ">(" << high << "," << low << "):" << endl;
		mask = ~(mask << width);
		sc_unsigned actual = source(high,low);
		sc_unsigned shift = (sc_unsigned(source) >> low);
		sc_unsigned expected = shift & mask;
		if (DEBUGF) std::cout << "shift & mask = expected" << std::endl;
		if (DEBUGF) std::cout << std::hex << shift << " & " << mask << " = " << expected << std::dec << std::endl;
		if ( actual != expected ) {
		    cout << "ERROR sc_bigint<" << W << ">(" << high << "," << low << "):" << endl;
		    cout << "  expected " << hex << expected << dec << endl;
		    cout << "  actual   " << hex << actual << dec <<  endl;
		    cout << "  mask     " << hex << mask << dec << endl;
		    cout << "  shift    " << hex << shift << endl;
		    cout << "  source   " << hex << source << dec << endl;
		    assert(0);
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
