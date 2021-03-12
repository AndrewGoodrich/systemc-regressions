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

template<int W, int D=1>
class Selection : public Selection<W-D,D>
{
  public:
    Selection( unsigned int fill ) : Selection<W-D,D>(fill)
    {
        sc_bigint<W> bigint_source;
        sc_signed    signed_source(W);

        load( W, bigint_source, fill );
        load( W, signed_source, fill );
	
	for ( int low = 0; low < W; ++low ) {
	    for ( int high = low; high < W; ++high ) {
	        int width = (high-low) + 1;
		sc_biguint<W> mask = -1; 
		sc_biguint<W> pre_mask = mask << width;
		mask = ~(mask << width);

		// test sc_biguint<W> selection:

                if ( 1 )
		{
		    sc_unsigned actual = bigint_source(high,low); 
		    sc_unsigned shifted_source = (bigint_source >> low);

		    // sc_unsigned expected = shifted_source & mask;
		    sc_biguint<W>  expected = shifted_source & mask;
		    if (0) {
		        std::cout << std::endl << "sc_bigint<" << W << ">(" << high << "," 
			          << low << "):" << endl;
		        std::cout << "shift & mask = expected" << std::endl;
		        std::cout << std::hex << shifted_source << " & " << mask << " = " 
                                  << expected << std::dec << std::endl;
                    }
		    if ( actual != expected ) {
			cout << "ERROR: actual != expected in " << __FILE__ << " at line " 
			     << __LINE__ << endl;
			cout << "  range    (" << high << "," << low << "):" << endl;
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
			cout << "ERROR: actual != expected in " << __FILE__ << " at line " 
			     << __LINE__ << endl;
			cout << "  range    (" << high << "," << low << "):" << endl;
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

template<int W, int D=1>
class SelectionWrite : public SelectionWrite<W-D,D>
{
  public:
    SelectionWrite( unsigned int fill ) : SelectionWrite<W-D,D>(fill)
    {
        sc_bigint<W> bigint_actual;
        sc_bigint<W> bigint_expected;
        sc_bigint<W> bigint_source;
        sc_signed    signed_actual(W);
        sc_signed    signed_expected(W);
        sc_signed    signed_source(W);

	load( W, bigint_source, fill );
        load( W, signed_source, fill );
	
	for ( int low = 0; low < W; ++low ) {
	    for ( int high = low; high < W; ++high ) {
	        int width = (high-low) + 1;
		sc_biguint<W> mask = -1; 
		mask = ~(mask << width);

		// test sc_biguint<W> selection:

                if ( 1 )
		{
		    bigint_actual = 0;
		    bigint_actual(high,low) = bigint_source;
		    bigint_expected = bigint_source & mask;
		    bigint_expected = bigint_expected << low;
		    if ( bigint_actual != bigint_expected ) {
			cout << "ERROR: actual != expected in " << __FILE__ << " at line " 
			     << __LINE__ << endl;
			cout << "  range    (" << high << "," << low << "):" << endl;
			cout << "  width    " << width << endl;
			dump( "  expected ", bigint_expected );
			dump( "  actual   " , bigint_actual );
			dump( "  mask     ", mask );
			dump( "  source   ", bigint_source );
			assert(0);
		    }
		}

		// test sc_unsigned selection:

		{
		    signed_actual = 0;
		    signed_actual(high,low) = signed_source;
		    signed_expected = signed_source & mask;
		    signed_expected = signed_expected << low;
		    if ( bigint_actual != bigint_expected ) {
			cout << "ERROR: actual != expected in " << __FILE__ << " at line " 
			     << __LINE__ << endl;
			cout << "  range    (" << high << "," << low << "):" << endl;
			cout << "  width    " << width << endl;
			dump( "  expected ", signed_expected );
			dump( "  actual   " , signed_actual );
			dump( "  mask     ", mask );
			dump( "  source   ", signed_source );
			assert(0);
		    }
		}

	    }
        }
    }
};

template<int D>
class SelectionWrite<0,D>
{
  public:
    SelectionWrite(unsigned int fill ) {}
};

int sc_main( int argc, char* argv[] )
{
    if ( true )
    {
	cout << "Selection(0x" << std::hex << ~0u << std::dec << ")" << std::endl;
	Selection<128> x(~0u);
	Selection<1550,31> y(~0u);

	cout << "SelectionWrite(0x" << std::hex << ~0u << std::dec << ")" << std::endl;
	SelectionWrite<128> x_write(~0u);
	SelectionWrite<1550,31> y_write(~0u);
    }
    if ( true )
    {
	cout << "Selection(0x" << std::hex << 0x55555555u << std::dec << ")" << std::endl;
	Selection<128> x(0x55555555u);

	cout << "SelectionWrite(0x" << std::hex << 0x55555555u << std::dec << ")" << std::endl;
	SelectionWrite<128> x_write1(0x55555555u);
    }
    if ( true )
    {
	cout << "Selection(0x" << std::hex << 0xaaaaaaaau << std::dec << ")" << std::endl;
	Selection<128> x(0xaaaaaaaau);

	cout << "Selection(0x" << std::hex << 0xaaaaaaaau << std::dec << ")" << std::endl;
	SelectionWrite<128> x_write(0xaaaaaaaau);
    }
    if ( true )
    {
	cout << "Selection(0x" << std::hex << 0x99999999u << std::dec << ")" << std::endl;
	Selection<128> x(0x99999999u);

	cout << "SelectionWrite(0x" << std::hex << 0x99999999u << std::dec << ")" << std::endl;
	SelectionWrite<128> x_write(0x99999999u);
    }
    if ( true )
    {
	cout << "Selection(0x" << std::hex << 0x66666666u << std::dec << ")" << std::endl;
	Selection<128> x(0x66666666u);

	cout << "SelectionWrite(0x" << std::hex << 0x66666666u << std::dec << ")" << std::endl;
	SelectionWrite<128> x_write(0x66666666u);
    }
    cout << "Big value signed selection completed" << endl;

    return 0;
}
#endif
