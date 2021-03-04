#include "systemc.h"
#include "isaac.h"

QTIsaac<8> rng;         // Platform independent random number generator.

template<typename T>
inline void load( int bits_n,  T& target )
{
    int target_n = DIV_CEIL(bits_n);

    target = rng.rand();
    for ( int target_i = 1; target_i < target_n; ++target_i ) {
        target = (target << 32) + rng.rand();
    }
}

template<int WA, int WB, int D>
class BigDecrement : public BigDecrement<WA,WB-D,D>
{
  public:
    BigDecrement() : BigDecrement<WA,WB-D,D>() {}

    void test_add_subtract_signed()
    {
        sc_bigint<WA>                      v_sc_bigint_a;
        sc_bigint<WB>                      v_sc_bigint_b;
        sc_bigint<WA < WB ? WB+1:WA+1>     v_sum;
        sc_bigint<WA < WB ? WB+1+1:WA+1+1> v_difference;

	for ( size_t count = 0; count < 1000; ++count ) {
	    load( WA, v_sc_bigint_a );
	    load( WB, v_sc_bigint_b );

	    // a + b

	    v_sum = v_sc_bigint_a + v_sc_bigint_b;
	    v_difference = v_sum - v_sc_bigint_b;
	    if ( v_difference != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << WA << "> - sc_bigint<" << WB << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_bigint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_bigint_a );
	    }

	    // b + a

	    v_sum = v_sc_bigint_b + v_sc_bigint_a;
	    v_difference = v_sum - v_sc_bigint_a;
	    if ( v_difference != v_sc_bigint_b ) {
		cout << "ERROR: sc_bigint<" << WB << "> - sc_bigint<" << WA << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_bigint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_bigint_b );
	    }
	}

	((BigDecrement<WA,WB-D,D>*)this)->test_add_subtract_signed();
    }

    void test_add_subtract_mixed()
    {
        sc_bigint<WA>                            v_sc_bigint_a;
        sc_biguint<WB>                           v_sc_biguint_b;
	sc_bigint<WA < WB ? WB+1+1 : WA+1+1>     v_sum;
	sc_bigint<WA < WB ? WB+1+1+1 : WA+1+1+1> v_difference;

	for ( size_t count = 0; count < 1000; ++count ) {
	    load(WA, v_sc_bigint_a);
	    load(WB+1, v_sc_biguint_b);

	    // a + b

	    v_sum = v_sc_bigint_a + v_sc_biguint_b;
	    v_difference = v_sum - v_sc_biguint_b;
	    if ( v_difference != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << WA << "> - sc_biguint<" << WB << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_bigint_a );
	    }

	    // b + a

	    v_sum = v_sc_biguint_b + v_sc_bigint_a;
	    v_difference = v_sum - v_sc_bigint_a;
	    if ( v_difference != v_sc_biguint_b ) {
		cout << "ERROR: sc_biguint<" << WB << "> - sc_bigint<" << WA << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_biguint_b );
	    }
	}

	((BigDecrement<WA,WB-D,D>*)this)->test_add_subtract_mixed();
    }

    void test_add_subtract_unsigned()
    {
        sc_biguint<WA>                           v_sc_biguint_a;
        sc_biguint<WB>                           v_sc_biguint_b;
        sc_bigint<WA < WB ? WB+2+1 : WA+2+1>     v_sum;
        sc_bigint<WA < WB ? WB+2+1+1 : WA+2+1+1> v_difference;

	for ( size_t count = 0; count < 1000; ++count ) {
	    load(WA+1, v_sc_biguint_a);
	    load(WB+1, v_sc_biguint_b);

	    // a + b

	    v_sum = v_sc_biguint_a + v_sc_biguint_b;
	    v_difference = v_sum - v_sc_biguint_b;
	    if ( v_difference != v_sc_biguint_a ) {
		cout << "ERROR: sc_biguint<" << WA << "> - sc_biguint<" << WB << ">:" << endl;
		cout << "  a         " << v_sc_biguint_a << endl;
		cout << "  b         " << v_sc_biguint_b << endl;
		cout << " sum        " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_biguint_a );
	    }

	    // b + a

	    v_sum = v_sc_biguint_b + v_sc_biguint_a;
	    v_difference = v_sum - v_sc_biguint_a;
	    if ( v_difference != v_sc_biguint_b ) {
		cout << "ERROR: sc_biguint<" << WB << "> - sc_biguint<" << WA << ">:" << endl;
		cout << "  a         " << v_sc_biguint_a << endl;
		cout << "  b         " << v_sc_biguint_b << endl;
		cout << " sum        " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_biguint_b );
	    }
	}

	((BigDecrement<WA,WB-D,D>*)this)->test_add_subtract_unsigned();
    }
    void test_multiply_divide_signed()
    {
        sc_bigint<WA>   v_sc_bigint_a;
        sc_bigint<WB>   v_sc_bigint_b;
        sc_bigint<WA+WB> v_product;
        sc_bigint<WA+WB> v_quotient;

	for ( size_t count = 0; count < 1000; ++count ) {
	    load(WA, v_sc_bigint_a);
	    load(WB, v_sc_bigint_b);

	    // Make sure no divide by zero:

	    v_sc_bigint_a = v_sc_bigint_a | 1;
	    v_sc_bigint_b = v_sc_bigint_b | 1;

	    // a * b

	    v_product = v_sc_bigint_a * v_sc_bigint_b;
	    v_quotient = v_product / v_sc_bigint_b;
	    if ( v_quotient != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << WA << "> / sc_bigint<" << WB << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_bigint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_bigint_a );
	    }

	    // b * a

	    v_product = v_sc_bigint_b * v_sc_bigint_a;
	    v_quotient = v_product / v_sc_bigint_a;
	    if ( v_quotient != v_sc_bigint_b ) {
		cout << "ERROR: sc_bigint<" << WB << "> / sc_bigint<" << WA << ">:" << endl;
		cout << "  a       " << v_sc_bigint_a << endl;
		cout << "  b       " << v_sc_bigint_b << endl;
		cout << " product  " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_bigint_b );
	    }
	}

	((BigDecrement<WA,WB-D,D>*)this)->test_multiply_divide_signed();
    }

    void test_multiply_divide_unsigned()
    {
        sc_biguint<WA>   v_sc_biguint_a;
        sc_biguint<WB>   v_sc_biguint_b;
        sc_biguint<WA+WB> v_product;
        sc_biguint<WA+WB> v_quotient;

	for ( size_t count = 0; count < 1000; ++count ) {
	    load(WA+1, v_sc_biguint_a);
	    load(WB+1, v_sc_biguint_b);

	    // Make sure no divide by zero:

	    v_sc_biguint_a = v_sc_biguint_a | 1;
	    v_sc_biguint_b = v_sc_biguint_b | 1;

	    // a * b
	    v_product = v_sc_biguint_a * v_sc_biguint_b;
	    v_quotient = v_product / v_sc_biguint_b;
	    if ( v_quotient != v_sc_biguint_a ) {
		cout << "ERROR: sc_biguint<" << WA << "> / sc_biguint<" << WB << ">:" << endl;
		cout << "  a        " << v_sc_biguint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_biguint_a );
	    }

	    // b * a

	    v_product = v_sc_biguint_b * v_sc_biguint_a;
	    v_quotient = v_product / v_sc_biguint_a;
	    if ( v_quotient != v_sc_biguint_b ) {
		cout << "ERROR: sc_biguint<" << WA << "> / sc_biguint<" << WB << ">:" << endl;
		cout << "  a        " << v_sc_biguint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_biguint_b );
	    }
	}

	((BigDecrement<WA,WB-D,D>*)this)->test_multiply_divide_unsigned();
    }

    void test_multiply_divide_mixed()
    {
        sc_bigint<WA>      v_sc_bigint_a;
        sc_biguint<WB>     v_sc_biguint_b;
        sc_bigint<WA+WB+1> v_product;
        sc_bigint<WA+WB>   v_quotient;

	for ( size_t count = 0; count < 1000; ++count ) {
	    load(WA, v_sc_bigint_a);
	    load(WB+1, v_sc_biguint_b);

	    // Make sure no divide by zero:

	    v_sc_bigint_a = v_sc_bigint_a | 1;
	    v_sc_biguint_b = v_sc_biguint_b | 1;

	    // a * b

	    v_product = v_sc_bigint_a * v_sc_biguint_b;
	    v_quotient = v_product / v_sc_biguint_b;
	    if ( v_quotient != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << WA << "> / sc_biguint<" << WB << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a 
		                      << hex << " (" << v_sc_bigint_a << ")" << dec << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient 
		                     << hex << " (" << v_quotient << ")" << dec << endl;
		assert( v_quotient == v_sc_bigint_a );
	    }

	    // b * a

	    v_product = v_sc_biguint_b * v_sc_bigint_a;
	    v_quotient = v_product / v_sc_bigint_a;
	    if ( v_quotient != v_sc_biguint_b ) {
		cout << "ERROR: sc_biguint<" << WB << "> / sc_bigint<" << WA << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_product << endl;
		cout << " quotient " << v_quotient << endl;
		assert( v_quotient == v_sc_biguint_b );
	    }
	}

	((BigDecrement<WA,WB-D,D>*)this)->test_multiply_divide_mixed();
    }
};

template<int WA, int D>
class BigDecrement<WA, 0, D> 
{
  public:
    BigDecrement() {}
    void test_add_subtract_signed() {}
    void test_add_subtract_mixed() {}
    void test_add_subtract_unsigned() {}
    void test_multiply_divide_signed() {}
    void test_multiply_divide_mixed() {}
    void test_multiply_divide_unsigned() {}
};

template<int W, int D_ME, int D_DECREMENT>
class BigTop : public BigTop<W-D_ME,D_ME,D_DECREMENT>
{
  public:
    BigTop() : BigTop<W-D_ME,D_ME,D_DECREMENT>() {}
    void test()
    {
	test_add_subtract_signed();
        test_add_subtract_mixed();
        test_add_subtract_unsigned();
	test_multiply_divide_signed();
        test_multiply_divide_mixed();
        test_multiply_divide_unsigned();
    }
    void test_add_subtract_signed()
    {
	m_decrement.test_add_subtract_signed();
	((BigTop<W-D_ME,D_ME,D_DECREMENT>*)this)->test_add_subtract_signed();
    }
    void test_add_subtract_mixed()
    {
	m_decrement.test_add_subtract_mixed();
	((BigTop<W-D_ME,D_ME,D_DECREMENT>*)this)->test_add_subtract_unsigned();
    }
    void test_add_subtract_unsigned()
    {
	m_decrement.test_add_subtract_unsigned();
	((BigTop<W-D_ME,D_ME,D_DECREMENT>*)this)->test_add_subtract_unsigned();
    }
    void test_multiply_divide_signed()
    {
	m_decrement.test_multiply_divide_signed();
	((BigTop<W-D_ME,D_ME,D_DECREMENT>*)this)->test_multiply_divide_signed();
    }
    void test_multiply_divide_mixed()
    {
	m_decrement.test_multiply_divide_mixed();
	((BigTop<W-D_ME,D_ME,D_DECREMENT>*)this)->test_multiply_divide_unsigned();
    }
    void test_multiply_divide_unsigned()
    {
	m_decrement.test_multiply_divide_unsigned();
	((BigTop<W-D_ME,D_ME,D_DECREMENT>*)this)->test_multiply_divide_unsigned();
    }
  protected:
    BigDecrement<W,W,D_DECREMENT> m_decrement;
};

template<int D_ME, int D_DECREMENT>
class BigTop<0,D_ME,D_DECREMENT>
{
  public:
    BigTop() {}
    void test() {}
    void test_add_subtract_signed() {}
    void test_add_subtract_mixed() {}
    void test_add_subtract_unsigned() {}
    void test_multiply_divide_signed() {}
    void test_multiply_divide_mixed() {}
    void test_multiply_divide_unsigned() {}
};

int sc_main(int argc, char* argv[])
{
    BigTop<10,10,1> top;
    // BigTop<310,31,31> top;
    // BigDecrement<128,128,1> top;

    top.test();

    cout << "Program completed" << endl;
    return 0;
}
