//
// scverify.h
//
// This header file provides macros to simplify the creation of C++
// testbench files that are SCVerify-ready.
//
// A sample testbench file looks like this:
//
// #include "scverify.h"
// #include "my_func.h"
//
// CCS_MAIN(int argc, char *argv)
// {
//   for (int iteration=0; iteration<5; iteration++) {
//      int arg1 = iteration;     // 1st arg to my_func
//      int arg2 = iteration+1;   // 2nd arg to my_func
//      int arg3;                 // result
//      CCS_DESIGN(my_func)(arg1,arg2,&arg3);
//      cout << arg3 << endl;
//   }
//   CCS_RETURN(0);  // return success
// }

#ifndef SCVERIFY_H_INC
#define SCVERIFY_H_INC

#undef CCS_DESIGN
#undef CCS_MAIN
#undef CCS_RETURN

#ifdef CCS_SCVERIFY
#include <mc_testbench.h>
#define CCS_DESIGN(a) testbench::exec_##a
#define CCS_MAIN(a,b) void testbench::main()
#define CCS_RETURN(a)
#else
#define CCS_DESIGN(a) a
#define CCS_MAIN(a,b) int main(a,b)
#define CCS_RETURN(a) return(a)
#endif


#endif

