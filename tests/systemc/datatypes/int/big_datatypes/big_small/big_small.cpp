#include "systemc.h"
#include "isaac.h"

QTIsaac<8> rng;         // Platform independent random number generator.

template<typename T>
void load( int bits_n, T& target )
{
    int target_n = DIV_CEIL(bits_n);

    target = rng.rand();
    for ( int target_i = 1; target_i < target_n; ++target_i ) {
        target = (target << 32) + rng.rand();
    }
}

template<int W>
void test_add_subtract_signed_int( int max_width, int delta_width )
{
    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_signed left(width);
	sc_int<W> right;
	for ( int count = 0; count < 1000; ++count ) {
	    load(width, left);
	    uint64 source = rng.rand();
	    right = (source << 32) | rng.rand();
	    sc_signed sum = left+right;
	    sc_signed difference = sum - left;
	    if ( difference != right ) {
		cout << "ERROR: sc_int<" << W << "> - sc_signed(" << width << "):" << endl;
		cout << "  left       " << left << endl;
		cout << "  right      " << right << endl;
		cout << "  sum        " << sum << endl;
		cout << "  difference " << difference << endl;
		assert( difference == right );
	    }
	}
    }

    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_int<W> left;
	sc_signed right(width);
	for ( int count = 0; count < 1000; ++count ) {
	    uint64 source = rng.rand();
	    left = (source << 32) | rng.rand();
	    load(width, right);
	    sc_signed sum = right+left;
	    sc_signed difference = sum - left;
	    if ( difference != right ) {
		cout << "ERROR: sc_signed(" << width << ") - sc_int<" << W << ">:" << endl;
		cout << "  left       " << left << endl;
		cout << "  right      " << right << endl;
		cout << "  sum        " << sum << endl;
		cout << "  difference " << difference << endl;
		assert( difference == right );
	    }
	}
    }
}

template<int W>
void test_add_subtract_signed_uint( int max_width, int delta_width )
{
    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_signed  left(width);
	sc_uint<W> right;
	for ( int count = 0; count < 1000; ++count ) {
	    load(width, left);
	    uint64 source = rng.rand();
	    right = (source << 32) | rng.rand();
	    sc_signed sum = left+right;
	    sc_signed difference = sum - left;
	    if ( difference != right ) {
		cout << "ERROR: sc_uint<" << W << "> - sc_signed(" << width << "):" << endl;
		cout << "  left       " << left << endl;
		cout << "  right      " << right << endl;
		cout << "  sum        " << sum << endl;
		cout << "  difference " << difference << endl;
		assert( difference == right );
	    }
	}
    }

    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_uint<W> left;
	sc_signed  right(width);
	for ( int count = 0; count < 1000; ++count ) {
	    uint64 source = rng.rand();
	    left = (source << 32) | rng.rand();
	    load(width, right);
	    sc_signed sum = right+left;
	    sc_signed difference = sum - left;
	    if ( difference != right ) {
		cout << "ERROR: sc_signed(" << width << ") - sc_uint<" << W << ">:" << endl;
		cout << "  left       " << left << endl;
		cout << "  right      " << right << endl;
		cout << "  sum        " << sum << endl;
		cout << "  difference " << difference << endl;
		assert( difference == right );
	    }
	}
    }
}


template<int W>
void test_add_subtract_unsigned_int( int max_width, int delta_width )
{
    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_unsigned left(width);
	sc_int<W>   right;
	for ( int count = 0; count < 1000; ++count ) {
	    load(width+1, left);
	    uint64 source = rng.rand();
	    right = (source << 32) | rng.rand();
	    sc_signed sum = left+right;
	    sc_signed difference = sum - left;
	    if ( difference != right ) {
		cout << "ERROR: sc_int<" << W << "> - sc_signed(" << width << "):" << endl;
		cout << "  left       " << left << endl;
		cout << "  right      " << right << endl;
		cout << "  sum        " << sum << endl;
		cout << "  difference " << difference << endl;
		assert( difference == right );
	    }
	}
    }

    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_int<W>   left;
	sc_unsigned right(width);
	for ( int count = 0; count < 1000; ++count ) {
	    uint64 source = rng.rand();
	    left = (source << 32) | rng.rand();
	    load(width+1, right);
	    sc_signed sum = right+left;
	    sc_signed difference = sum - left;
	    if ( difference != right ) {
		cout << "ERROR: sc_signed(" << width << ") - sc_int<" << W << ">:" << endl;
		cout << "  left       " << left << endl;
		cout << "  right      " << right << endl;
		cout << "  sum        " << sum << endl;
		cout << "  difference " << difference << endl;
		assert( difference == right );
	    }
	}
    }
}

template<int W>
void test_add_subtract_unsigned_uint( int max_width, int delta_width )
{
    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_unsigned  left(width);
	sc_uint<W>   right;
	for ( int count = 0; count < 1000; ++count ) {
	    load(width+1, left);
	    uint64 source = rng.rand();
	    right = (source << 32) | rng.rand();
	    sc_unsigned sum = left+right;
	    sc_signed difference = sum - left;
	    if ( difference != right ) {
		cout << "ERROR: sc_uint<" << W << "> - sc_unsigned(" << width << "):" << endl;
		cout << "  left       " << left << endl;
		cout << "  right      " << right << endl;
		cout << "  sum        " << sum << endl;
		cout << "  difference " << difference << endl;
		assert( difference == right );
	    }
	}
    }

    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_uint<W>  left;
	sc_unsigned right(width);
	for ( int count = 0; count < 1000; ++count ) {
	    uint64 source = rng.rand();
	    left = (source << 32) | rng.rand();
	    load(width+1, right);
	    sc_unsigned sum = right+left;
	    sc_signed difference = sum - left;
	    if ( difference != right ) {
		cout << "ERROR: sc_unsigned(" << width << ") - sc_uint<" << W << ">:" << endl;
		cout << "  left       " << left << endl;
		cout << "  right      " << right << endl;
		cout << "  sum        " << sum << endl;
		cout << "  difference " << difference << endl;
		assert( difference == right );
	    }
	}
    }
}

template<int W>
void test_multiply_divide_signed_int( int max_width, int delta_width )
{
    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_signed left(width);
	sc_int<W> right;
	for ( int count = 0; count < 1000; ++count ) {
	    load(width, left);
	    left |= 1;
	    uint64 source = rng.rand();
	    right = (source << 32) | rng.rand();
	    sc_signed product = left * right;
	    sc_signed quotient = product / left;
	    if ( quotient != right ) {
		cout << "ERROR: sc_int<" << W << "> / sc_signed(" << width << "):" << endl;
		cout << "  left     " << left << endl;
		cout << "  right    " << right << endl;
		cout << "  product  " << product << endl;
		cout << "  quotient " << quotient << endl;
		assert( quotient == right );
	    }
	}
    }

    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_int<W> left;
	sc_signed right(width);
	for ( int count = 0; count < 1000; ++count ) {
	    uint64 source = rng.rand();
	    left = (source << 32) | rng.rand();
	    left |= 1;
	    load(width, right);
	    sc_signed product = right * left;
	    sc_signed quotient = product / left;
	    if ( quotient != right ) {
		cout << "ERROR: sc_signed(" << width << ") / sc_int<" << W << ">:" << endl;
		cout << "  left     " << left << endl;
		cout << "  right    " << right << endl;
		cout << "  product  " << product << endl;
		cout << "  quotient " << quotient << endl;
		assert( quotient == right );
	    }
	}
    }
}

template<int W>
void test_multiply_divide_signed_uint( int max_width, int delta_width )
{
    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_signed  left(width);
	sc_uint<W> right;
	for ( int count = 0; count < 1000; ++count ) {
	    load(width, left);
	    left |= 1;
	    uint64 source = rng.rand();
	    right = (source << 32) | rng.rand();
	    sc_signed product = left * right;
	    sc_signed quotient = product / left;
	    if ( quotient != right ) {
		cout << "ERROR: sc_uint<" << W << "> / sc_signed(" << width << "):" << endl;
		cout << "  left     " << left << endl;
		cout << "  right    " << right << endl;
		cout << "  product  " << product << endl;
		cout << "  quotient " << quotient << endl;
		assert( quotient == right );
	    }
	}
    }

    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_uint<W> left;
	sc_signed  right(width);
	for ( int count = 0; count < 1000; ++count ) {
	    uint64 source = rng.rand();
	    left = (source << 32) | rng.rand();
	    left |= 1;
	    load(width, right);
	    sc_signed product = right * left;
	    sc_signed quotient = product / left;
	    if ( quotient != right ) {
		cout << "ERROR: sc_signed(" << width << ") / sc_uint<" << W << ">:" << endl;
		cout << "  left     " << left << endl;
		cout << "  right    " << right << endl;
		cout << "  product  " << product << endl;
		cout << "  quotient " << quotient << endl;
		assert( quotient == right );
	    }
	}
    }
}


template<int W>
void test_multiply_divide_unsigned_int( int max_width, int delta_width )
{
    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_unsigned left(width);
	sc_int<W>   right;
	for ( int count = 0; count < 1000; ++count ) {
	    load(width+1, left);
	    left |= 1;
	    uint64 source = rng.rand();
	    right = (source << 32) | rng.rand();
	    sc_signed product = left * right;
	    sc_signed quotient = product / left;
	    if ( quotient != right ) {
		cout << "ERROR: sc_int<" << W << "> / sc_signed(" << width << "):" << endl;
		cout << "  left     " << left << endl;
		cout << "  right    " << right << endl;
		cout << "  product  " << product << endl;
		cout << "  quotient " << quotient << endl;
		assert( quotient == right );
	    }
	}
    }

    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_int<W>   left;
	sc_unsigned right(width);
	for ( int count = 0; count < 1000; ++count ) {
	    uint64 source = rng.rand();
	    left = (source << 32) | rng.rand();
	    left |= 1;
	    load(width+1, right);
	    sc_signed product = right * left;
	    sc_signed quotient = product / left;
	    if ( quotient != right ) {
		cout << "ERROR: sc_signed(" << width << ") / sc_int<" << W << ">:" << endl;
		cout << "  left     " << left << endl;
		cout << "  right    " << right << endl;
		cout << "  product  " << product << endl;
		cout << "  quotient " << quotient << endl;
		assert( quotient == right );
	    }
	}
    }
}

template<int W>
void test_multiply_divide_unsigned_uint( int max_width, int delta_width )
{
    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_unsigned  left(width);
	sc_uint<W>   right;
	for ( int count = 0; count < 1000; ++count ) {
	    load(width+1, left);
	    left |= 1;
	    uint64 source = rng.rand();
	    right = (source << 32) | rng.rand();
	    sc_unsigned product = left * right;
	    sc_signed quotient = product / left;
	    if ( quotient != right ) {
		cout << "ERROR: sc_uint<" << W << "> / sc_unsigned(" << width << "):" << endl;
		cout << "  left     " << left << endl;
		cout << "  right    " << right << endl;
		cout << "  product  " << product << endl;
		cout << "  quotient " << quotient << endl;
		assert( quotient == right );
	    }
	}
    }

    for ( int width = max_width; width > 1; width -= delta_width ) {
	sc_uint<W>  left;
	sc_unsigned right(width);
	for ( int count = 0; count < 1000; ++count ) {
	    uint64 source = rng.rand();
	    left = (source << 32) | rng.rand();
	    left |= 1;
	    load(width+1, right);
	    sc_unsigned product = right * left;
	    sc_signed quotient = product / left;
	    if ( quotient != right ) {
		cout << "ERROR: sc_unsigned(" << width << ") / sc_uint<" << W << ">:" << endl;
		cout << "  left     " << left << endl;
		cout << "  right    " << right << endl;
		cout << "  product  " << product << endl;
		cout << "  quotient " << quotient << endl;
		assert( quotient == right );
	    }
	}
    }
}
template<int W>
class BigSmall : public BigSmall<W-1>
{
  public:
    BigSmall() : BigSmall<W-1>() {}
    void test( int max_width, int delta_width )
    {
        test_add_subtract_signed_int<W>( max_width, delta_width );
        test_add_subtract_signed_uint<W>( max_width, delta_width );
        test_add_subtract_unsigned_int<W>( max_width, delta_width );
        test_add_subtract_unsigned_uint<W>( max_width, delta_width );

        test_multiply_divide_signed_int<W>( max_width, delta_width );
        test_multiply_divide_signed_uint<W>( max_width, delta_width );
        test_multiply_divide_unsigned_int<W>( max_width, delta_width );
        test_multiply_divide_unsigned_uint<W>( max_width, delta_width );

        ( (BigSmall<W-1>*)this)->test( max_width, delta_width );
    }
};

template<>
class BigSmall<1> 
{
  public:
   void test( int max_width, int delta_width ) {}
};

int sc_main(int argc, char* argv[])
{
    BigSmall<64> x;

    x.test( 128, 1 );

    cout << "Program completed" << endl;
    return 0;
}
