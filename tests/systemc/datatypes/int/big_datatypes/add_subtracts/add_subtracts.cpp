#include "systemc.h"
#include "isaac.h"

QTIsaac<8> rng;         // Platform independent random number generator.

template<int W, int D>
class AddSubtract : public AddSubtract<W-D,D>
{
  public:
    AddSubtract() : AddSubtract<W-D,D>() {}
    void test_signed_signed()
    {
        sc_bigint<W>     v_sc_bigint_a;
        sc_bigint<W>     v_sc_bigint_b;
        sc_bigint<W+1>   v_sum;
        sc_bigint<W+1+1> v_difference;

	for ( size_t count = 0; count < 1000; ++count ) {
	    v_sc_bigint_a = rng.rand();
	    v_sc_bigint_b = rng.rand();
	    for ( int digit_i = 1; digit_i < DIV_CEIL(W); ++digit_i ) {
		v_sc_bigint_a = (v_sc_bigint_a << 32) + rng.rand();
		v_sc_bigint_b = (v_sc_bigint_b << 32) + rng.rand();
	    }

	    // a + b

	    v_sum = v_sc_bigint_a + v_sc_bigint_b;
	    v_difference = v_sum - v_sc_bigint_b;
	    if ( false && v_difference != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << W << "> - sc_bigint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_bigint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_bigint_b );
	    }

	    // b + a

	    v_sum = v_sc_bigint_b + v_sc_bigint_a;
	    v_difference = v_sum - v_sc_bigint_a;
	    if ( false && v_difference != v_sc_bigint_b ) {
		cout << "ERROR: sc_bigint<" << W << "> - sc_bigint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_bigint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_bigint_a );
	    }
	}

	((AddSubtract<W-D,D>*)this)->test_signed_signed();
    }

    void test_signed_unsigned()
    {
        sc_bigint<W>       v_sc_bigint_a;
        sc_biguint<W>      v_sc_biguint_b;
        sc_bigint<W+1+1>   v_sum;
        sc_bigint<W+1+1+1> v_difference;

	for ( size_t count = 0; count < 1000; ++count ) {
	    v_sc_bigint_a = rng.rand();
	    v_sc_biguint_b = rng.rand();
	    for ( int digit_i = 1; digit_i < DIV_CEIL(W); ++digit_i ) {
		v_sc_bigint_a = (v_sc_bigint_a << 32) + rng.rand();
		v_sc_biguint_b = (v_sc_biguint_b << 32) + rng.rand();
	    }

	    // a + b

	    v_sum = v_sc_bigint_a + v_sc_biguint_b;
	    v_difference = v_sum - v_sc_biguint_b;
	    if ( false && v_difference != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << W << "> - sc_biguint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_biguint_b );
	    }

	    // b + a

	    v_sum = v_sc_biguint_b + v_sc_bigint_a;
	    v_difference = v_sum - v_sc_bigint_a;
	    if ( false && v_difference != v_sc_biguint_b ) {
		cout << "ERROR: sc_biguint<" << W << "> - sc_bigint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_bigint_a );
	    }
	}

	((AddSubtract<W-D,D>*)this)->test_signed_signed();
    }

    void test_unsigned_unsigned()
    {
        sc_biguint<W>      v_sc_biguint_a;
        sc_biguint<W>      v_sc_biguint_b;
        sc_bigint<W+2+1>   v_sum;
        sc_bigint<W+2+1+1> v_difference;

	for ( size_t count = 0; count < 1000; ++count ) {
	    v_sc_biguint_a = rng.rand();
	    v_sc_biguint_b = rng.rand();
	    for ( int digit_i = 1; digit_i < DIV_CEIL(W); ++digit_i ) {
		v_sc_biguint_a = (v_sc_biguint_a << 32) + rng.rand();
		v_sc_biguint_b = (v_sc_biguint_b << 32) + rng.rand();
	    }

	    // a + b

	    v_sum = v_sc_biguint_a + v_sc_biguint_b;
	    v_difference = v_sum - v_sc_biguint_b;
	    if ( v_difference != v_sc_biguint_a ) {
		cout << "ERROR: sc_biguint<" << W << "> - sc_biguint<" << W << ">:" << endl;
		cout << "  a         " << v_sc_biguint_a << endl;
		cout << "  b         " << v_sc_biguint_b << endl;
		cout << " sum        " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_biguint_b );
	    }

	    // b + a

	    v_sum = v_sc_biguint_b + v_sc_biguint_a;
	    v_difference = v_sum - v_sc_biguint_a;
	    if ( v_difference != v_sc_biguint_b ) {
		cout << "ERROR: sc_biguint<" << W << "> - sc_biguint<" << W << ">:" << endl;
		cout << "  a         " << v_sc_biguint_a << endl;
		cout << "  b         " << v_sc_biguint_b << endl;
		cout << " sum        " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_biguint_a );
	    }
	}

	((AddSubtract<W-D,D>*)this)->test_signed_signed();
    }
};

template<int D>
class AddSubtract<0,D>
{
  public:
    AddSubtract() {}
    void test_signed_signed() {}
};

int sc_main(int argc, char* argv[])
{
    AddSubtract<128,1> x;
    AddSubtract<3100,31> y;

    x.test_signed_signed();
    x.test_signed_unsigned();
    x.test_unsigned_unsigned();
    y.test_signed_signed();
    y.test_signed_unsigned();
    y.test_unsigned_unsigned();

    cout << "Big Addition/Subtraction tests completed" << endl;
    return 0;
}
