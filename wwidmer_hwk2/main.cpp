//============================================================================
// Name        : main.cpp
// Author      : William Widmer
// Created     : March 2014
// Build       : g++ main.cpp
//               or simply with attached makefile: make and run with ./eavl.out
// Version     : 1.0
// Description : Main file for Assignment two, Spring 2014 CSCI 335 Professor Weiss
// Reads a file of commands then executes those commands on an EAVLTREE containing words (strings)              
// Takes command line argument for path to file. Parses the file and tokenizes every line. Executes 
// given instructions on a line by line basis and outputs to a stream. (cout or cerr, where applicable)
//============================================================================


#include "eavltree.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdarg>
#include <sstream>

using namespace std;

vector<string> simple_tokenizer(string line);
void driver(string line);
bool eavl_driver(string error_line,string cmd, ...);
AvlTree<string> t; 

/**
 * Main function. Requires an argument (path to a file).
 * Will only accept first argument as a path to a file others ignored.
 */
int main(int argc, char* argv[] ){
  if(argc < 2){
    cerr << "ERROR: No arguments found! Please try again with a file name. Exiting.." << endl;
    return 0;
  } else {
    if(argc > 2){
      cerr << "ERROR: Too many arguments found! First argument: " << argv[1] << " being used..." << endl;
    }
    driver(argv[1]);
    exit(EXIT_FAILURE);
    return 0;
  }
}

/**
 * Driver function to open the input file. 
 * Reads each line using the simple_tokenizer
 * Interprets each line using the eavl_driver
 * An error occurs if unable to open the file, which then exits.
 */
void  driver(string input){
  ifstream file;
  string line;
  string error_line;
  file.open(input.c_str());
  if(file.is_open()){
       
    while(getline(file,line)){
      vector<string> tokens = simple_tokenizer(line);
      error_line = "(" + line + ") is not a valid line!";
    
      if(tokens.size() < 3){
	if( tokens.size() == 1){
	  eavl_driver(error_line, tokens[0]);
	} else if (tokens.size() > 1){
	  eavl_driver(error_line, tokens[0],tokens[1].c_str());      }    
      }
    }  file.close();
  } else 
    cerr << "ERROR: Unable to open file" << endl;
}

/**
 * eavl_driver
 * Takes in a variable amount of arguments, being, the command to run to the avltree and the word to insert, find, or remove.
 */
bool eavl_driver(string error_line, string cmd, ...){
  va_list args;
  int freq;
  va_start(args, cmd);
  
  if(cmd == "insert"){
    char* c = va_arg(args,char *);
    cout << c << "\t" << t.insert(c) << endl;
    va_end(args);
    return true;
  }else if(cmd == "remove"){
    char* c = va_arg(args,char *);
    freq = -1;
    freq = t.remove(c);
    if(freq > -1){
      cout << c << "\t" << freq << endl;
    } else
      cout << c << "\t" << "not found" <<endl;    
    va_end(args);
    return true;
  }else if(cmd == "find"){
    char* c = va_arg(args,char *);
    freq = 0;
    int visit = t.find(c,freq);			      
    cout << c << "\t" << freq << "\t" << visit << endl;
    va_end(args);
    return true;
  }else if(cmd == "display"){
    t.display(cout);
    va_end(args);
    return true;
  }else if(cmd == "report"){
    t.report();
    va_end(args);
    return true;
  }else if(cmd =="quit"){
    t.make_empty();
    va_end(args);
    exit(EXIT_FAILURE);
  }else{
    cerr << error_line << endl;
    va_end(args);
    return false;
  }
}

/**
 * Returns a vector of all strings found in a line of input.
 * Simple tokenizer to break down each line of input - streamstream accounts for whitespace.
 */

vector<string> simple_tokenizer(string line){
  vector<string> tokens;
  string buffer;
  stringstream ss(line);

  while ( ss >> buffer){
    tokens.push_back(buffer);
  }
  return tokens;
}

  
