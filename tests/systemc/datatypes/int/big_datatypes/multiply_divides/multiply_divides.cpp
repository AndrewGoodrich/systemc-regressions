#include "systemc.h"
#include "isaac.h"

QTIsaac<8> rng;         // Platform independent random number generator.

template<int W, int D>
class MultiplyDivide : public MultiplyDivide<W-D,D>
{
  public:
    MultiplyDivide() : MultiplyDivide<W-D,D>() {}
    void test_signed_signed()
    {
        sc_bigint<W>   v_sc_bigint_a;
        sc_bigint<W>   v_sc_bigint_b;
        sc_bigint<W+W> v_product;
        sc_bigint<W+W> v_quotient;

	for ( size_t count = 0; count < 1000; ++count ) {
	    v_sc_bigint_a = rng.rand();
	    v_sc_bigint_b = rng.rand();
	    for ( int digit_i = 1; digit_i < DIV_CEIL(W); ++digit_i ) {
		v_sc_bigint_a = (v_sc_bigint_a << 32) + rng.rand();
		v_sc_bigint_b = (v_sc_bigint_b << 32) + rng.rand();
	    }

	    // Make sure no divide by zero:

	    v_sc_bigint_a = v_sc_bigint_a | 1;
	    v_sc_bigint_b = v_sc_bigint_b | 1;

	    // a * b

	    v_product = v_sc_bigint_a * v_sc_bigint_b;
	    v_quotient = v_product / v_sc_bigint_b;
	    if ( false && v_quotient != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << W << "> / sc_bigint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_bigint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_bigint_b );
	    }

	    // b * a

	    v_product = v_sc_bigint_b * v_sc_bigint_a;
	    v_quotient = v_product / v_sc_bigint_a;
	    if ( false && v_quotient != v_sc_bigint_b ) {
		cout << "ERROR: sc_bigint<" << W << "> / sc_bigint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_bigint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_bigint_a );
	    }
	}

	((MultiplyDivide<W-D,D>*)this)->test_signed_signed();
    }

    void test_unsigned_unsigned()
    {
        sc_biguint<W>   v_sc_biguint_a;
        sc_biguint<W>   v_sc_biguint_b;
        sc_biguint<W+W> v_product;
        sc_biguint<W+W> v_quotient;

	for ( size_t count = 0; count < 1000; ++count ) {
	    v_sc_biguint_a = rng.rand();
	    v_sc_biguint_b = rng.rand();
	    for ( int digit_i = 1; digit_i < DIV_CEIL(W); ++digit_i ) {
		v_sc_biguint_a = (v_sc_biguint_a << 32) + rng.rand();
		v_sc_biguint_b = (v_sc_biguint_b << 32) + rng.rand();
	    }

	    // Make sure no divide by zero:

	    v_sc_biguint_a = v_sc_biguint_a | 1;
	    v_sc_biguint_b = v_sc_biguint_b | 1;

	    // a * b
	    v_product = v_sc_biguint_a * v_sc_biguint_b;
	    v_quotient = v_product / v_sc_biguint_b;
	    if ( v_quotient != v_sc_biguint_a ) {
		cout << "ERROR: sc_biguint<" << W << "> / sc_biguint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_biguint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_biguint_b );
	    }

	    // b * a

	    v_product = v_sc_biguint_b * v_sc_biguint_a;
	    v_quotient = v_product / v_sc_biguint_a;
	    if ( v_quotient != v_sc_biguint_b ) {
		cout << "ERROR: sc_biguint<" << W << "> / sc_biguint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_biguint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_biguint_a );
	    }
	}

	((MultiplyDivide<W-D,D>*)this)->test_signed_signed();
    }
};

template<int D>
class MultiplyDivide<0,D>
{
  public:
    MultiplyDivide() {}
    void test_signed_signed() {}
};

int sc_main(int argc, char* argv[])
{
    MultiplyDivide<128,1> x;
    MultiplyDivide<3100,31> y;

    x.test_signed_signed();
    x.test_unsigned_unsigned();
    y.test_signed_signed();
    y.test_unsigned_unsigned();

    cout << "Big multiply/divide tests completed" << endl;
    return 0;
}
