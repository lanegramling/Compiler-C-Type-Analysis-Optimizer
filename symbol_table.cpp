#include "symbol_table.hpp"
#include <iostream>
#include <utility>
namespace LILC{

ScopeTable::ScopeTable(){
	map = new std::unordered_map<std::string, SymbolTableEntry *>();
}

void ScopeTable::printAll() {
	for (std::pair<std::string, SymbolTableEntry *> e : *map) {
		std::cout << "Name: " << e.first << ", Type: " << e.second->getType() << "\n";
	}
}

bool ScopeTable::findByName(std::string name) {
	return (map->count(name) > 0);
}

std::string ScopeTable::getTypeOf(std::string id) {
	std::unordered_map<std::string,SymbolTableEntry *>::const_iterator got = map->find (id);
	return got->second->getType();
}

std::string ScopeTable::getStructName(std::string id) {
	std::unordered_map<std::string,SymbolTableEntry *>::const_iterator got = map->find (id);
	return got->second->getStructId();
}

std::string ScopeTable::getAccessType(std::string structId, std::string accessId) {
	std::unordered_map<std::string,SymbolTableEntry *>::const_iterator got = map->find (structId);
	return got->second->getTypeOfStructAccess(accessId);
}

bool ScopeTable::addItem(std::string id, std::string type) {
	if (map->count(id) == 0) {
		SymbolTableEntry * temp = new SymbolTableEntry();
		temp->setType(type);
		map->insert({{id, temp}});
		temp = nullptr;
		return true;
	} else {
		// maybe put an error...
		return false;
	}
}

bool ScopeTable::addStruct(std::string id, std::list<std::string> list, std::list<std::string> list2) {
	if (map->count(id) == 0) {
		SymbolTableEntry * temp = new SymbolTableEntry();
		temp->setType("struct");
		temp->setStructDecls(list);
		temp->setStructTypes(list2);
		map->insert({{id, temp}});
		temp = nullptr;
		return true;
	} else {
		return false;
	}
}

bool ScopeTable::addStructUsage(std::string id, std::string type, std::string structId) {
	if (map->count(id) == 0) {
		SymbolTableEntry * temp = new SymbolTableEntry();
		temp->setType(type);
		temp->setStructId(structId);
		map->insert({{id, temp}});
		temp = nullptr;
		return true;
	} else {
		return false;
	}
}

bool ScopeTable::structListContains(std::string structId, std::string accessId) {
	std::unordered_map<std::string,SymbolTableEntry *>::const_iterator got = map->find (structId);
	return got->second->structListContains(accessId);
}

SymbolTable::SymbolTable(){
	scopeTables = new std::list<ScopeTable *>();
};

void SymbolTable::addScope() {
	scopeTables->push_back(new ScopeTable());
}

void SymbolTable::dropScope() {
	scopeTables->pop_back();
}

bool SymbolTable::addItem(std::string id, std::string type) {
	return scopeTables->back()->addItem(id, type);
}

bool SymbolTable::addStruct(std::string id, std::list<std::string> list, std::list<std::string> list2) {
	return scopeTables->back()->addStruct(id, list, list2);
}

bool SymbolTable::addStructUsage(std::string id, std::string type, std::string structId) {
	return scopeTables->back()->addStructUsage(id, type, structId);
}

bool SymbolTable::findByName(std::string name) {
	for (ScopeTable* table: *scopeTables) {
		if (table->findByName(name)) return true;
	}
	return false;
}

std::string SymbolTable::getTypeOf(std::string id) {
	return getTableContaining(id)->getTypeOf(id);
}

std::string SymbolTable::getStructName(std::string id) {
	return getTableContaining(id)->getStructName(id);
}

std::string SymbolTable::getAccessType(std::string structId, std::string accessId) {
	return getTableContaining(structId)->getAccessType(structId, accessId);
}

bool SymbolTable::structListContains(std::string structId, std::string accessId) {
	return getTableContaining(structId)->structListContains(structId, accessId);
}

ScopeTable * SymbolTable::getTableContaining(std::string id) {
	for (ScopeTable* table: *scopeTables) {
		if (table->findByName(id)) return table;
	}
	return nullptr; // Hopefully never happens
}

void SymbolTable::reportError(std::string message) {
	std::cerr << message << "\n";
}

void SymbolTable::printAll() {
	int i = 0;
	for (ScopeTable* table : *scopeTables) {
		std::cout << "Scope " << i << ":\n";
		table->printAll();
	}
}

void SymbolTable::multiplyDeclaredId(char f) {
	std::cerr << "Multiply declared identifier: " << f << "\n";
}

void SymbolTable::undeclaredId(char f) {
	std::cerr << "Undeclared identifier: " << f << "\n";
}

void SymbolTable::dotAccess(char f) {
	std::cerr << "Dot-access of non-struct type: " << f << "\n";
}

void SymbolTable::invalidStructField(char f) {
	std::cerr << "Invalid struct field name: " << f << "\n";
}

void SymbolTable::nonFunctionVoid(char f) {
	std::cerr << "Non-function declared void: " << f << "\n";
}

void SymbolTable::invalidStructName(char f) {
	std::cerr << "Invalid name of struct type: " << f << "\n";
}

}
