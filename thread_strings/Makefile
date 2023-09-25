# CXX Make variable for compiler
CXX=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -Wall -g3 -c
LDFLAGS=-pthread
INCLUDE=-I./

# object files
OBJS = trie.o main.o args_handling.o input_handling.o chars_map.o progress_bar.o count_vocab_strings.o read_lines.o read_vocab.o parent_thread.o threading.o 
HEADERS = trie.hpp args_handling.hpp input_handling.hpp chars_map.hpp progress_bar.hpp count_vocab_strings.hpp read_lines.hpp read_vocab.hpp parent_thread.hpp threading.hpp
# Program name
PROGRAM = countvocabstrings

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
$(PROGRAM) : $(OBJS) $(HEADERS)
	$(CXX) -o $(PROGRAM) $^ $(LDFLAGS)

trie.o : trie.hpp trie.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) trie.cpp
	
args_handling.o : args_handling.hpp args_handling.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) args_handling.cpp
	
input_handling.o : input_handling.hpp input_handling.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) input_handling.cpp
	
chars_map.o : chars_map.hpp chars_map.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) chars_map.cpp

progress_bar.o : progress_bar.hpp progress_bar.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) progress_bar.cpp

count_vocab_strings.o : count_vocab_strings.hpp count_vocab_strings.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) count_vocab_strings.cpp
	
read_lines.o : read_lines.hpp read_lines.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) read_lines.cpp
	
read_vocab.o : read_vocab.hpp read_vocab.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) read_vocab.cpp

parent_thread.o : parent_thread.hpp parent_thread.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) parent_thread.cpp

threading.o : threading.hpp threading.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) threading.cpp

main.o : trie.cpp input_handling.cpp chars_map.cpp args_handling.cpp main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) main.cpp
	
clean :
	rm -f *.o $(PROGRAM)
