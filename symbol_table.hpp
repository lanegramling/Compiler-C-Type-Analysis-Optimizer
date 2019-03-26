#ifndef LILC_SYMBOL_TABLE_HPP
#define LILC_SYMBOL_TABLE_HPP
#include <unordered_map>
#include <list>

namespace LILC{

//A single entry for one name in the symbol table
class SymbolTableEntry{
	//TODO: Add type, kind, etc. instance variables
	//TODO: add getters/setters for type, kind, etc.
public:
	void setType(std::string type) {
		myType = type;
	}
	std::string getType() { return myType; }
	void setStructDecls(std::list<std::string> decls) {
		structDecls = decls;
	}
	std::list<std::string> getStructDecls() { return structDecls; }
	void setStructTypes(std::list<std::string> decls) {
		structTypes = decls;
	}
	std::list<std::string> getStructTypes() { return structTypes; }
	void setStructId(std::string id) {
		structId = id;
	}
	std::string getStructId() { return structId; }
	bool structListContains(std::string accessId) {
		for (std::string s : structDecls) {
			if (s == accessId) return true;
		}
		return false;
	}
	std::string getTypeOfStructAccess(std::string accessId) {
		int count = 0;
		for (std::string s : structDecls) {
			if (s == accessId) break;
			count++;
		}
		int temp = 0;
		for (std::string s : structTypes) {
			if (temp == count)
				return s;
			temp++;
		}
		return "MESSED UP";
	}
private:
	std::string myType;
	std::list<std::string> structDecls;
	std::list<std::string> structTypes;
	std::string structId;
};

//A single 
class ScopeTable{
	public:
		ScopeTable();
		//TODO: add functions for looking up symbols
		// and/or returning information to indicate
		// that the symbol does not exist within 
		// the current scope
		bool findByName(std::string name);
		std::string getTypeOf(std::string id);
		std::string getStructName(std::string id);
		std::string getAccessType(std::string structId, std::string accessId);
		bool addItem(std::string id, std::string type);
		bool addStruct(std::string id, std::list<std::string> list, std::list<std::string> list2);
		bool addStructUsage(std::string id, std::string type, std::string structId);
		bool structListContains(std::string structId, std::string accessId);
		void printAll(); // Debug method
	private:
		std::unordered_map<std::string, SymbolTableEntry *>* map;
};

class SymbolTable{
	public:
		SymbolTable();
		void addScope();
		void dropScope();
		bool addItem(std::string id, std::string type);
		bool addStruct(std::string id, std::list<std::string> list, std::list<std::string> list2);
		bool addStructUsage(std::string id, std::string type, std::string structId);
		bool findByName(std::string name);
		std::string getTypeOf(std::string id);
		std::string getStructName(std::string id);
		std::string getAccessType(std::string structId, std::string accessId);
		bool structListContains(std::string structId, std::string accessId);
		void reportError(std::string message);
		void printAll(); // Debug method
		void addLine(int lines);
		void addChar(int chars);
		void multiplyDeclaredId(char f);
		void undeclaredId(char f);
		void dotAccess(char f);
		void invalidStructField(char f);
		void nonFunctionVoid(char f);
		void invalidStructName(char f);
	private:
		std::list<ScopeTable *> * scopeTables;
		ScopeTable * getTableContaining(std::string id);
};

}
#endif
