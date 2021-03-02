#include "systemc.h"

#define ASSIGN(to, from, value) \
{ \
    from = value; \
    to = from; \
    if ( to != from ) { \
        cout << "Error at width " << W << endl; \
        cout << "    " << #to << " = " << hex << to << dec << endl; \
        cout << "    " << #from << " = " << hex << from << dec << endl; \
	sc_assert( to == from ); \
    } \
}

template<int W>
class BigAssignments : public BigAssignments<W-1>
{
  public:
    BigAssignments() : BigAssignments<W-1>() {}
    void test( const sc_signed& value )
    {
        sc_bigint<W>  v_sc_bigint;
        sc_biguint<W> v_sc_biguint;
	sc_signed     v_sc_signed(W);
	sc_unsigned   v_sc_unsigned(W);

        ASSIGN(v_sc_bigint, v_sc_signed, value);

        ASSIGN(v_sc_signed, v_sc_bigint, value);

        ASSIGN(v_sc_biguint, v_sc_unsigned, value);

        ASSIGN(v_sc_unsigned, v_sc_biguint, value);
        
	((BigAssignments<W-1>*)this)->test(value);
    }
    void test( const sc_unsigned& value )
    {
        sc_bigint<W>  v_sc_bigint;
        sc_biguint<W> v_sc_biguint;
	sc_signed     v_sc_signed(W);
	sc_unsigned   v_sc_unsigned(W);

        ASSIGN(v_sc_bigint, v_sc_signed, value);

        ASSIGN(v_sc_signed, v_sc_bigint, value);

        ASSIGN(v_sc_biguint, v_sc_unsigned, value);

        ASSIGN(v_sc_unsigned, v_sc_biguint, value);
        
	((BigAssignments<W-1>*)this)->test(value);
    }
};

template<>
class BigAssignments<1>
{
  public:
    BigAssignments() {}
    void test( const sc_unsigned& value ) { }
};

template<int W>
class LittleAssignments : public LittleAssignments<W-1>
{
  public:
    LittleAssignments() : LittleAssignments<W-1>() {}
    void test( uint64 value )
    {
        sc_bigint<W>  v_sc_bigint;
        sc_biguint<W> v_sc_biguint;
        sc_int<W>     v_sc_int;
        sc_uint<W>    v_sc_uint;
	sc_signed     v_sc_signed(W);
	sc_unsigned   v_sc_unsigned(W);

        ASSIGN(v_sc_bigint, v_sc_int, value);
        ASSIGN(v_sc_bigint, v_sc_signed, value);

        ASSIGN(v_sc_int, v_sc_bigint, value);
        ASSIGN(v_sc_int, v_sc_signed, value);

        ASSIGN(v_sc_signed, v_sc_bigint, value);
        ASSIGN(v_sc_signed, v_sc_int, value);

        ASSIGN(v_sc_biguint, v_sc_uint, value);
        ASSIGN(v_sc_biguint, v_sc_unsigned, value);

        ASSIGN(v_sc_uint, v_sc_biguint, value);
        ASSIGN(v_sc_uint, v_sc_unsigned, value);

        ASSIGN(v_sc_unsigned, v_sc_biguint, value);
        ASSIGN(v_sc_unsigned, v_sc_uint, value);
        
	((LittleAssignments<W-1>*)this)->test(value);
    }
};

template<>
class LittleAssignments<1>
{
  public:
    LittleAssignments() {}
    void test( uint64 value ) { }
};

template<typename T>
void load(T& target, int width, unsigned int value )
{
    target = value; 
    for ( int load_i = 32; load_i < width; load_i+=32 ) {
       target = (target << 32) | value;
    }
}

int sc_main(int argc, char* argv[])
{
    BigAssignments<128>   big;
    LittleAssignments<64> little;

    uint64 target = 0x965afull;
    for ( int shift = 0; shift < 64; ++shift ) {
        target = target << shift;
	little.test( target );
    }

    for ( int width = 2; width < 129; ++width ) {
        sc_signed   v_signed(width);
        sc_unsigned v_unsigned(width);
	load(v_signed, width, 0xaaaaaaaau);
	load(v_unsigned, width, 0xaaaaaaaau);
	big.test(v_signed);
	big.test(v_unsigned);
    }



    cout << "Assignment tests passed" << endl;
    return 0;
}
