#include "ast.hpp"
#include "symbol_table.hpp"

namespace LILC{

bool ASTNode::typeAnalysis(){
	throw std::runtime_error("Internal Error: \n"
		"We should never see this, as it\n"
		"is supposed to be overridden in any\n"
		"subclass at which it is encountered");
}

bool ProgramNode::typeAnalysis(){
	//TODO: recurse down the AST, making sure to
	// uncover any type errors as detailed in the 
	// project 5 spec
	std::cerr << "[DELETE ME]: program node typeAnalysis\n"
	" should probably check for some children typing before\n"
	" declaring victory here.\n";
	
	return false;
}

/*
* Creates a comma-separated string listing the types of formals.
* This function mostly serves as a helper for 
* FnDeclNode::getTypeString() in building a function 
* type signature for unparsing. 
*/
std::string FormalsListNode::getTypeString(){
	std::string res = "";
	bool first = true;
	for (FormalDeclNode * decl : *myFormals){
		if (first){ first = false; }
		else { res += ","; }
		res += decl->getTypeString();
	}
	return res;
}

/*
* Create a string representing the type signature of a
* function.  This function is used for building a function 
* type signature for unparsing. 
*/
std::string FnDeclNode::getTypeString(){
	return myFormals->getTypeString() 
		+ "->" 
		+ myRetType->getTypeString();
}

/*
* The type of a declaration is that of the
* type it declares
*/
std::string FormalDeclNode::getTypeString(){
	return myType->getTypeString();
}

} // End namespace LILC 

