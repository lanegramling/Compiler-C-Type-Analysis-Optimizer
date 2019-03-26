#include <iostream>
#include <cstdlib>
#include <cstring>

#include "lilc_compiler.hpp"
#include "ast.hpp"

using namespace LILC;

int
main( const int argc, const char **argv )
{
   if (argc != 3){
	std::cout << "Usage: P5 <infile> <outfile>" << std::endl;
	return 1;
   }

   LILC::LilC_Compiler compiler;
   // compiler.nameAnalysis( argv[1], argv[2] );
   compiler.typeAnalysis( argv[1], argv[2] ); //typeAnalysis extends nameAnalysis in terms of execution
   return 0;
}
