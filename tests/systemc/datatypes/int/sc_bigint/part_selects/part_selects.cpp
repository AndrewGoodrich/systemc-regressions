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

template<int W>
class Selection : public Selection<W-1>
{
  public:
    Selection( unsigned int fill ) : Selection<W-1>(fill)
    {
        sc_biguint<W> source;
	source = fill;
	if ( W > 32 ) { source = (source << 32) | fill; }
	if ( W > 64 ) { source = (source << 32) | fill; }
	if ( W > 96 ) { source = (source << 32) | fill; }
	
	for ( int low = 0; low < W; ++low ) {
	    for ( int high = low; high < W; ++high ) {
	        int width = (high-low) + 1;
		sc_bigint<W> mask = -1;
		if (0) std::cout << std::endl << "sc_biguint<" << W << ">(" << high << "," << low << "):" << endl;
		mask = ~(mask << width);
		sc_unsigned actual = source(high,low);
		sc_unsigned shift = (source >> low);
		sc_unsigned expected = (source >> low) & mask;
		if (0) std::cout << "shift & mask = expected" << std::endl;
		if (0) std::cout << std::hex << shift << " & " << mask << " = " << expected << std::dec << std::endl;
		if ( actual != expected ) {
		    cout << "ERROR sc_biguint<" << W << ">(" << high << "," << low << "):" << endl;
		    cout << "  expected " << hex << expected << dec << " " << expected.get_hod() << endl;
		    cout << "  actual   " << hex << actual << dec << " " << actual.get_hod() << endl;
		    cout << "  mask     " << hex << mask << dec << " " << mask.get_hod() << endl;
		    cout << "  shift    " << hex << shift << endl;
		    cout << "  source   " << hex << source << endl;
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
