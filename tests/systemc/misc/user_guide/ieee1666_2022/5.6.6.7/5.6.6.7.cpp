// NEEDS EXECUTION CODE
//
// At present this test will validate the compilation syntax, but needs an execution 
// component.
//
// @@@@ ISSUES @@@@

#include <systemc.h>

SC_MODULE(M) {
    SC_CTOR(M) {
        SC_THREAD(run);
    }

    void run()
    {
        try {
	    // .  .  .
	} catch( const sc_core::sc_unwind_exception& ex ) {
	    // perform clean up
	    if ( ex.is_reset() ) {
	        // .  .  .
	    }
	    else {
	        // .  .  .
	    }
	    throw ex;
	}
    }
};

int sc_main( int argc, char* argv[] ) { 

    M m("m");

    std::cout << "program completed" << std::endl;
    return 0;
}