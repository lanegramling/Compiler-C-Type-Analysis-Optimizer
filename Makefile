BISON = bison

EXE = P5

CSTD = -std=c99
CXXSTD = -std=c++14

CFLAGS = -O0 -g $(CSTD)
CXXFLAGS = -O0 -g $(CXXSTD)

$(EXE): lilc_parser.o lilc_lexer.o lilc_compiler.o $(EXE).o unparse.o symbol_table.o name_analysis.o type_analysis.o
	$(CXX) $(CXXFLAGS) -o $(EXE) $(EXE).o lilc_compiler.o lilc_parser.o lilc_lexer.o unparse.o symbol_table.o name_analysis.o type_analysis.o

$(EXE).o: $(EXE).cpp
	$(CXX) $(CXXFLAGS) -c $<

symbol_table.o: symbol_table.cpp
	$(CXX) $(CXXFLAGS) -c $<

name_analysis.o: name_analysis.cpp
	$(CXX) $(CXXFLAGS) -c $<

type_analysis.o: type_analysis.cpp
	$(CXX) $(CXXFLAGS) -c $<

lilc_compiler.o: lilc_compiler.cpp lilc_parser.o lilc_lexer.o
	$(CXX) $(CXXFLAGS) -c $<

lilc_parser.o: lilc_parser.cc
	$(CXX) $(CXXFLAGS) -o lilc_parser.o -c $<

lilc_parser.cc: lilc.yy
	$(BISON) --defines=grammar.hh -v $<

lilc_lexer.o: lilc.l
	flex --outfile=lilc_lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c lilc_lexer.yy.cc -o lilc_lexer.o

ast.o: ast.cpp
	$(CXX) $(CXXFLAGS) -c $<

unparse.o: unparse.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf *.output *.o *.cc *.hh P[1-6]
