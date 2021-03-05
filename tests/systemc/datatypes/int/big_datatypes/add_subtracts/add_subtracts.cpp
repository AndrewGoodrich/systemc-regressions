#include "systemc.h"
#include "isaac.h"

#define COUNT_N 2000

QTIsaac<8> rng;         // Platform independent random number generator.

template<typename T>
inline void load( int bits_n, T& target )
{
    int target_n = DIV_CEIL(bits_n);

    target = rng.rand();
    for ( int target_i = 1; target_i < target_n; ++target_i ) {
        target = (target << 32) + rng.rand();
    }
}

void test_signed( int max_width, int delta_width )
{
    for ( int left_width = max_width; left_width > 1; left_width -= delta_width ) {
	for ( int right_width = max_width; right_width > 1; right_width -= delta_width ) {
	    sc_signed left(left_width);
	    sc_signed right(right_width);

	    for ( int count = 0; count < COUNT_N; ++count ) {
		load(left_width, left);
		load(right_width, right);

		sc_signed sum = left+right;
		sc_signed difference = sum - left;
		if ( difference != right ) {
		    cout << "ERROR: sc_signed(" << left_width << ") - sc_signed(" 
			 << right_width << "):" << endl;
		    cout << "  left       " << left << endl;
		    cout << "  right      " << right << endl;
		    cout << "  sum        " << sum << endl;
		    cout << "  difference " << difference << endl;
		    assert( difference == right );
		}
	    }

	}
    }
}

void test_mixed( int max_width, int delta_width )
{
    for ( int left_width = max_width; left_width > 1; left_width -= delta_width ) {
	for ( int right_width = max_width; right_width > 1; right_width -= delta_width ) {
	    {
		sc_signed   left(left_width);
		sc_unsigned right(right_width);

		for ( int count = 0; count < COUNT_N; ++count ) {
		    load(left_width, left);
		    load(right_width, right);

		    sc_signed sum = left+right;
		    sc_signed difference = sum - left;
		    if ( difference != right ) {
			cout << "ERROR: sc_signed(" << left_width << ") - sc_unsigned(" 
			     << right_width << "):" << endl;
			cout << "  left       " << left << endl;
			cout << "  right      " << right << endl;
			cout << "  sum        " << sum << endl;
			cout << "  difference " << difference << endl;
			assert( difference == right );
		    }
		}
	    }

	    {
		sc_unsigned left(left_width);
		sc_signed right(right_width);

		for ( int count = 0; count < COUNT_N; ++count ) {
		    load(left_width, left);
		    load(right_width, right);

		    sc_signed sum = left+right;
		    sc_signed difference = sum - left;
		    if ( difference != right ) {
			cout << "ERROR: sc_unsigned(" << left_width << ") - sc_signed(" 
			     << right_width << "):" << endl;
			cout << "  left       " << left << endl;
			cout << "  right      " << right << endl;
			cout << "  sum        " << sum << endl;
			cout << "  difference " << difference << endl;
			assert( difference == right );
		    }
		}
	    }

	}
    }
}

void test_unsigned( int max_width, int delta_width )
{
    for ( int left_width = max_width; left_width > 1; left_width -= delta_width ) {
	for ( int right_width = max_width; right_width > 1; right_width -= delta_width ) {
	    sc_unsigned left(left_width);
	    sc_unsigned right(right_width);

	    for ( int count = 0; count < COUNT_N; ++count ) {
		load(left_width, left);
		load(right_width, right);

		sc_signed sum = left+right;
		sc_signed difference = sum - left;
		if ( difference != right ) {
		    cout << "ERROR: sc_unsigned(" << left_width << ") - sc_unsigned(" 
			 << right_width << "):" << endl;
		    cout << "  left       " << left << endl;
		    cout << "  right      " << right << endl;
		    cout << "  sum        " << sum << endl;
		    cout << "  difference " << difference << endl;
		    assert( difference == right );
		}
	    }

	}
    }
}

template<int W, int D>
class AddSubtract : public AddSubtract<W-D,D>
{
  public:
    AddSubtract() : AddSubtract<W-D,D>() {}
    void test_signed()
    {
        sc_bigint<W>     v_sc_bigint_a;
        sc_bigint<W>     v_sc_bigint_b;
        sc_bigint<W+1>   v_sum;
        sc_bigint<W+1+1> v_difference;

	for ( size_t count = 0; count < COUNT_N; ++count ) {
	    load( W, v_sc_bigint_a );
	    load( W, v_sc_bigint_b );

	    // a + b

	    v_sum = v_sc_bigint_a + v_sc_bigint_b;
	    v_difference = v_sum - v_sc_bigint_b;
	    if ( v_difference != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << W << "> - sc_bigint<" << W << ">:" << endl;
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
		cout << "ERROR: sc_bigint<" << W << "> - sc_bigint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_bigint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_bigint_b );
	    }
	}

	((AddSubtract<W-D,D>*)this)->test_signed();
    }

    void test_mixed()
    {
        sc_bigint<W>       v_sc_bigint_a;
        sc_biguint<W>      v_sc_biguint_b;
        sc_bigint<W+1+1>   v_sum;
        sc_bigint<W+1+1+1> v_difference;

	for ( size_t count = 0; count < COUNT_N; ++count ) {
	    load(W, v_sc_bigint_a);
	    load(W+1, v_sc_biguint_b);

	    // a + b

	    v_sum = v_sc_bigint_a + v_sc_biguint_b;
	    v_difference = v_sum - v_sc_biguint_b;
	    if ( v_difference != v_sc_bigint_a ) {
		cout << "ERROR: sc_bigint<" << W << "> - sc_biguint<" << W << ">:" << endl;
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
		cout << "ERROR: sc_biguint<" << W << "> - sc_bigint<" << W << ">:" << endl;
		cout << "  a        " << v_sc_bigint_a << endl;
		cout << "  b        " << v_sc_biguint_b << endl;
		cout << " product " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_biguint_b );
	    }
	}

	((AddSubtract<W-D,D>*)this)->test_signed();
    }

    void test_unsigned()
    {
        sc_biguint<W>      v_sc_biguint_a;
        sc_biguint<W>      v_sc_biguint_b;
        sc_bigint<W+2+1>   v_sum;
        sc_bigint<W+2+1+1> v_difference;

	for ( size_t count = 0; count < COUNT_N; ++count ) {
	    load(W+1, v_sc_biguint_a);
	    load(W+1, v_sc_biguint_b);

	    // a + b

	    v_sum = v_sc_biguint_a + v_sc_biguint_b;
	    v_difference = v_sum - v_sc_biguint_b;
	    if ( v_difference != v_sc_biguint_a ) {
		cout << "ERROR: sc_biguint<" << W << "> - sc_biguint<" << W << ">:" << endl;
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
		cout << "ERROR: sc_biguint<" << W << "> - sc_biguint<" << W << ">:" << endl;
		cout << "  a         " << v_sc_biguint_a << endl;
		cout << "  b         " << v_sc_biguint_b << endl;
		cout << " sum        " << v_sum << endl;
		cout << " difference " << v_difference << endl;
		assert( v_difference == v_sc_biguint_b );
	    }
	}

	((AddSubtract<W-D,D>*)this)->test_signed();
    }
};

template<int D>
class AddSubtract<0,D>
{
  public:
    AddSubtract() {}
    void test_signed() {}
};

int sc_main(int argc, char* argv[])
{
    AddSubtract<128,1>      x;
    AddSubtract<3100,31>    y;

    x.test_signed();
    x.test_mixed();
    x.test_unsigned();
    y.test_signed();
    y.test_mixed();
    y.test_unsigned();

    test_signed(128,1);
    test_mixed(128,1);
    test_unsigned(128,1);

    cout << "Big Addition/Subtraction tests completed" << endl;
    return 0;
}
