#include "systemc.h"
#include "isaac.h"

QTIsaac<8> rng;         // Platform independent random number generator.


template<int W>
class Add : public Add<W-1>
{
  public:
    Add() : Add<W-1>() {}
    void test( uint64 a, uint64 b )
    {
	int64          v_int_result;
	uint64         v_uint_result;


        sc_bigint<64>  v_sc_bigint_result;
        sc_bigint<64>  v_sc_bigint_source_a;
        sc_biguint<64> v_sc_biguint_result;
        sc_biguint<64> v_sc_biguint_source_a;

	sc_signed      v_sc_signed_a(W);
	sc_signed      v_sc_signed_b(W);

	sc_unsigned    v_sc_unsigned_a(W);
	sc_unsigned    v_sc_unsigned_b(W);

        sc_bigint<W>   v_sc_bigint_a;
        sc_bigint<W>   v_sc_bigint_b;

        sc_biguint<W>  v_sc_biguint_a;
        sc_biguint<W>  v_sc_biguint_b;

        sc_int<W>  v_sc_int_a;
        sc_int<W>  v_sc_int_b;

        sc_uint<W>  v_sc_uint_a;
        sc_uint<W>  v_sc_uint_b;


        v_sc_bigint_source_a = a;
        v_sc_biguint_source_a = a;

        v_sc_int_a = a;
        v_sc_int_b = b;

        v_sc_uint_a = a;
        v_sc_uint_b = b;

        v_sc_bigint_a = a;
        v_sc_bigint_b = b;

        v_sc_biguint_a = a;
        v_sc_biguint_b = b;

        v_sc_signed_a = a;
        v_sc_signed_b = b;

        v_sc_unsigned_a = a;
        v_sc_unsigned_b = b;

	v_sc_bigint_result = v_sc_bigint_a * v_sc_bigint_b;
	v_sc_biguint_result = a + b;

	v_int_result = v_sc_int_a + v_sc_int_b;
	v_uint_result = v_sc_uint_a + v_sc_uint_b;

	v_sc_bigint_result = v_sc_bigint_a + v_sc_bigint_b;
	if ( v_sc_bigint_result != v_int_result ) {
	    cout << "ERROR: sc_bigint<" << W << "> + sc_bigint<" << W << ">:" << endl;
	    cout << "  a        " << a << endl;
	    cout << "  b        " << b << endl;
	    cout << " C++       " << v_int_result << endl;
	    cout << " sc_bigint " << v_sc_bigint_result << endl;
	    assert( v_sc_bigint_result == v_int_result );
	}

	v_sc_bigint_result = v_sc_signed_a + v_sc_signed_b;
	if ( v_sc_bigint_result != v_int_result ) {
	    cout << "ERROR: sc_signed(" << W << ") + sc_signed(" << W << "):" << endl;
	    cout << "  a        " << a << endl;
	    cout << "  b        " << b << endl;
	    cout << " C++       " << v_int_result << endl;
	    cout << " sc_bigint " << v_sc_bigint_result << endl;
	    assert( v_sc_bigint_result == v_int_result );
	}

	v_sc_biguint_result = v_sc_biguint_a + v_sc_biguint_b;
	if ( v_sc_biguint_result != v_uint_result ) {
	    cout << "ERROR: sc_biguint<" << W << "> + sc_biguint<" << W << ">:" << endl;
	    cout << "  a         " << a << endl;
	    cout << "  b         " << b << endl;
	    cout << " C++        " << v_uint_result << endl;
	    cout << " sc_biguint " << v_sc_biguint_result << endl;
	    assert( v_sc_biguint_result == v_uint_result );
	}

	v_sc_biguint_result = v_sc_unsigned_a + v_sc_unsigned_b;
	if ( v_sc_biguint_result != v_uint_result ) {
	    cout << "ERROR: sc_unsigned(" << W << ") + sc_unsigned(" << W << "):" << endl;
	    cout << "  a         " << a << endl;
	    cout << "  b         " << b << endl;
	    cout << " C++        " << v_uint_result << endl;
	    cout << " sc_biguint " << v_sc_biguint_result << endl;
	    assert( v_sc_biguint_result == v_uint_result );
	}

	v_sc_biguint_result = v_sc_bigint_source_a(W-1,0) + v_sc_biguint_b;
	if ( v_sc_bigint_result != v_int_result ) {
	    cout << "ERROR: sc_bigint<" << W << ">(" << W-1 << ",0) + sc_biguint<" << W 
		 << ">:" << endl;
	    cout << "  a         " << a << endl;
	    cout << "  b         " << b << endl;
	    cout << " C++        " << v_uint_result << endl;
	    cout << " sc_biguint " << v_sc_biguint_result << endl;
	    assert( v_sc_biguint_result == v_uint_result );
	}
	    
	v_sc_biguint_result = v_sc_biguint_source_a(W-1,0) + v_sc_biguint_b;
	if ( v_sc_bigint_result != v_int_result ) {
	    cout << "ERROR: sc_biguint<" << W << ">(" << W-1 << ",0) + sc_biguint<" << W 
		 << ">:" << endl;
	    cout << "  a         " << a << endl;
	    cout << "  b         " << b << endl;
	    cout << " C++        " << v_uint_result << endl;
	    cout << " sc_biguint " << v_sc_biguint_result << endl;
	    assert( v_sc_biguint_result == v_uint_result );
	}
	    

	((Add<W-1>*)this)->test(a, b);
    }
};

template<>
class Add<0>
{
  public:
    Add() {}
    void test( uint64 a, uint64 b ) {}
};

int sc_main(int argc, char* argv[])
{
    Add<64> x;

    for ( int i = 0; i < 10000; ++i ) {
	uint64 a = rng.rand();
	a = (a << 32) | rng.rand();
	uint64 b = rng.rand();
	b = (b << 32) | rng.rand();
	x.test( a, b );
    }

    cout << "Small add tests completed" << endl;
    return 0;
}
