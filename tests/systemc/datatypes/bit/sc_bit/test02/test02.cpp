#include "systemc.h"
#include "isaac.h"

QTIsaac<8> rng;         // Platform independent random number generator.

#define DUMP( WHAT ) \
{ \
    cout << hex << WHAT << " " << #WHAT << " ( " << dec << WHAT.length() << " ) " << endl; \
}

#define COMPARE_BV( LEFT, RIGHT ) \
    if ( ( LEFT != RIGHT ) ) { \
	cout << endl << "ERROR DETECTED @ " << __FILE__ << ":" << __LINE__ << ":" << endl; \
	DUMP(left_sc_unsigned); \
	DUMP(right_sc_unsigned); \
	DUMP(left_sc_bv_base); \
	DUMP(right_sc_bv_base); \
	cout << endl; \
	DUMP(LEFT); \
	DUMP(RIGHT); \
	cout << endl; \
    }

#define COMPARE_LV( LEFT, RIGHT ) \
    if ( ( LEFT != RIGHT ) ) { \
	cout << endl << "ERROR DETECTED @ " << __FILE__ << ":" << __LINE__ << ":" << endl; \
	DUMP(left_sc_unsigned); \
	DUMP(right_sc_unsigned); \
	DUMP(left_sc_lv_base); \
	DUMP(right_sc_lv_base); \
	cout << endl; \
	DUMP(LEFT); \
	DUMP(RIGHT); \
	cout << endl; \
    }

template<typename T>
inline void load_rand( int bits_n, T& target )
{
    int target_n = DIV_CEIL(bits_n);

    target = rng.rand();
    for ( int target_i = 1; target_i < target_n; ++target_i ) {
        target = (target << 32) + rng.rand();
    }
}

void test_and( const sc_unsigned& left_sc_unsigned, const sc_unsigned& right_sc_unsigned,
              const sc_lv_base& left_sc_lv_base, const sc_lv_base& right_sc_lv_base )
{
    sc_unsigned left_unsigned_or_right_unsigned( left_sc_unsigned & right_sc_unsigned );
    sc_unsigned left_unsigned_or_right_lv( left_sc_unsigned & right_sc_lv_base );
    sc_unsigned left_lv_or_right_unsigned ( left_sc_lv_base & right_sc_unsigned );
    sc_unsigned left_lv_or_right_lv( left_sc_lv_base & right_sc_lv_base );
    
    COMPARE_LV( left_unsigned_or_right_unsigned, left_unsigned_or_right_lv )
    COMPARE_LV( left_unsigned_or_right_unsigned, left_lv_or_right_unsigned )
    COMPARE_LV( left_unsigned_or_right_unsigned, left_lv_or_right_lv )
}

void test_and( const sc_unsigned& left_sc_unsigned, const sc_unsigned& right_sc_unsigned,
              const sc_bv_base& left_sc_bv_base, const sc_bv_base& right_sc_bv_base )
{
    sc_unsigned left_unsigned_or_right_unsigned( left_sc_unsigned & right_sc_unsigned );
    sc_unsigned left_unsigned_or_right_bv( left_sc_unsigned & right_sc_bv_base );
    sc_unsigned left_bv_or_right_unsigned ( left_sc_bv_base & right_sc_unsigned );
    sc_unsigned left_bv_or_right_bv( left_sc_bv_base & right_sc_bv_base );
    
    COMPARE_BV( left_unsigned_or_right_unsigned, left_unsigned_or_right_bv )
    COMPARE_BV( left_unsigned_or_right_unsigned, left_bv_or_right_unsigned )
    COMPARE_BV( left_unsigned_or_right_unsigned, left_bv_or_right_bv )
}

void test_or( const sc_unsigned& left_sc_unsigned, const sc_unsigned& right_sc_unsigned,
              const sc_lv_base& left_sc_lv_base, const sc_lv_base& right_sc_lv_base )
{
    sc_unsigned left_unsigned_or_right_unsigned( left_sc_unsigned | right_sc_unsigned );
    sc_unsigned left_unsigned_or_right_lv( left_sc_unsigned | right_sc_lv_base );
    sc_unsigned left_lv_or_right_unsigned ( left_sc_lv_base | right_sc_unsigned );
    sc_unsigned left_lv_or_right_lv( left_sc_lv_base | right_sc_lv_base );
    

    COMPARE_LV( left_unsigned_or_right_unsigned, left_unsigned_or_right_lv )
    COMPARE_LV( left_unsigned_or_right_unsigned, left_lv_or_right_unsigned )
    COMPARE_LV( left_unsigned_or_right_unsigned, left_lv_or_right_lv )
}

void test_or( const sc_unsigned& left_sc_unsigned, const sc_unsigned& right_sc_unsigned,
              const sc_bv_base& left_sc_bv_base, const sc_bv_base& right_sc_bv_base )
{
    sc_unsigned left_unsigned_or_right_unsigned( left_sc_unsigned | right_sc_unsigned );
    sc_unsigned left_unsigned_or_right_bv( left_sc_unsigned | right_sc_bv_base );
    sc_unsigned left_bv_or_right_unsigned ( left_sc_bv_base | right_sc_unsigned );
    sc_unsigned left_bv_or_right_bv( left_sc_bv_base | right_sc_bv_base );
    

    COMPARE_BV( left_unsigned_or_right_unsigned, left_unsigned_or_right_bv )
    COMPARE_BV( left_unsigned_or_right_unsigned, left_bv_or_right_unsigned )
    COMPARE_BV( left_unsigned_or_right_unsigned, left_bv_or_right_bv )
}

void test_xor( const sc_unsigned& left_sc_unsigned, const sc_unsigned& right_sc_unsigned,
              const sc_lv_base& left_sc_lv_base, const sc_lv_base& right_sc_lv_base )
{
    sc_unsigned left_unsigned_or_right_unsigned( left_sc_unsigned ^ right_sc_unsigned );
    sc_unsigned left_unsigned_or_right_lv( left_sc_unsigned ^ right_sc_lv_base );
    sc_unsigned left_lv_or_right_unsigned ( left_sc_lv_base ^ right_sc_unsigned );
    sc_unsigned left_lv_or_right_lv( left_sc_lv_base ^ right_sc_lv_base );
    
    COMPARE_LV( left_unsigned_or_right_unsigned, left_unsigned_or_right_lv )
    COMPARE_LV( left_unsigned_or_right_unsigned, left_lv_or_right_unsigned )
    COMPARE_LV( left_unsigned_or_right_unsigned, left_lv_or_right_lv )
}

void test_xor( const sc_unsigned& left_sc_unsigned, const sc_unsigned& right_sc_unsigned,
              const sc_bv_base& left_sc_bv_base, const sc_bv_base& right_sc_bv_base )
{
    sc_unsigned left_unsigned_or_right_unsigned( left_sc_unsigned ^ right_sc_unsigned );
    sc_unsigned left_unsigned_or_right_bv( left_sc_unsigned ^ right_sc_bv_base );
    sc_unsigned left_bv_or_right_unsigned ( left_sc_bv_base ^ right_sc_unsigned );
    sc_unsigned left_bv_or_right_bv( left_sc_bv_base ^ right_sc_bv_base );
    
    COMPARE_BV( left_unsigned_or_right_unsigned, left_unsigned_or_right_bv )
    COMPARE_BV( left_unsigned_or_right_unsigned, left_bv_or_right_unsigned )
    COMPARE_BV( left_unsigned_or_right_unsigned, left_bv_or_right_bv )
}

void test1()
{
    for ( int left_i = 1; left_i < 128; ++left_i ) {
	for ( int right_i = left_i; right_i < 128; ++right_i ) {
	    sc_unsigned left_sc_unsigned(left_i);
	    sc_unsigned right_sc_unsigned(right_i);
	    sc_bv_base  left_sc_bv_base(left_i);
	    sc_bv_base  right_sc_bv_base(right_i);
	    sc_lv_base  left_sc_lv_base(left_i);
	    sc_lv_base  right_sc_lv_base(right_i);

            load_rand( left_i, left_sc_unsigned );
            load_rand( right_i, right_sc_unsigned );

            left_sc_lv_base = left_sc_unsigned;
            right_sc_lv_base = right_sc_unsigned;
	    test_and( left_sc_unsigned, right_sc_unsigned, left_sc_lv_base, right_sc_lv_base );
	    test_or( left_sc_unsigned, right_sc_unsigned, left_sc_lv_base, right_sc_lv_base );
	    test_xor( left_sc_unsigned, right_sc_unsigned, left_sc_lv_base, right_sc_lv_base );

            left_sc_bv_base = left_sc_unsigned;
            right_sc_bv_base = right_sc_unsigned;
	    test_and( left_sc_unsigned, right_sc_unsigned, left_sc_bv_base, right_sc_bv_base );
	    test_or( left_sc_unsigned, right_sc_unsigned, left_sc_bv_base, right_sc_bv_base );
	    test_xor( left_sc_unsigned, right_sc_unsigned, left_sc_bv_base, right_sc_bv_base );

        }
    }
}

int sc_main(int argc, char* argv[])
{
    test1();

    cout << "Bit logic operators test completed" << endl;
    return 0;
}
