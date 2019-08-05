# Text Files

```c++
#include<assert.h>
#include<string>
// File Library
#include<fstream>
#include<iostream>
// Different file streams
using std::fstream; // for both input and output
using std::ifstream; // for input only
using std::ofstream; // for output only

using std::ios;


int main(int argc, char 

	const *argv[])
 {	
	/* Modes for opening
		ios::in - open file for reading
		ios::out - open file for writing
		ios::trunc - open file and delete information in it
		ios::app - open file for writing, only write in the end of it
		ios::binary - work with bytes instead of characters
	*/

 	/* Constructor
 		The constructor takes 2 arguments, name of file and mode of opening (see above)
 		The default modes of opening are:
 			1. ios::in|ios::out for fstream
 			2. ios::in 			for ifstream
 			3. ios::out 		for ofstream
 	*/
 	fstream f1("f1.txt", ios::in|ios::out); // equivalent to fstream f1("f1.txt");
 	
 	/*  Default constructor
 		Creates a stream and doesn't associate it with a file
 		You can later assocaite the stream with a file using the open method. It works just like the constructor.
	*/

	fstream f2; // Declare fstream2;
	// ...
	f2.open("f2.txt"); // When you have access to the file, open it.

	// Don't forget to close your streams once you no longer need them
	f1.close();
	f2.close();

	/*  NB!
		RAII - Resource Acquisation Is Initialization
		Use your class' constructor to acquire resources (e.g. dynamic memory, files, etc ...)
		Use the destructor to free the resource (e.g. delete dynamic memory, close files, etc ...)
	*/

	// Reading from file

	// >> operator, reads until white space

	/* EXAMPLEFILE.txt
	hello 322 ab1234
	one word
	linewith.points.init
	newlineA
	*/

	ifstream fin("EXAMPLEFILE.txt");
	std::string word;
	int number;

	fin >> word >> number;
	std::cout << word << " " << number << std::endl;

	/* output
		hello322
	*/

	// get(char a) - gets one symbol from the stream and assigns it to a
	// get(char* a, streamsize n) - gets n-1 symbols from the stream (or until it reads '\n' and assings them and a '\0' to a
	// get(char* a, streamsize n, char delim) - same as above but also stops at delim
	// get() - read one symbol and return it's ascii code
	char symbol;

	fin.get(); // read and ignore the white space
	fin.get(symbol); // read 1 character and assing it to symbol
	std::cout<<symbol;
	symbol = fin.get(); // get the ascii code of 1 character and assign the character it represents to symbol
	std::cout << symbol << std::endl;

	/* Output
		ab
	*/

	char symbols[5];
	fin.get(symbols, 5);
	std::cout << symbols << std::endl;
	// Output: 1234
	// Last character in symbols is '\0'

	fin.get(); // ignore the new lineq
	char line[50];
	fin.getline(line, 50); // read until you've read 50 symbols or reached a new line
	std::cout << line << std::endl; // output: one word
	
	fin.getline(line, 20, '.'); // read until 50 symbols or new line or '.''
	std::cout << line << std::endl; // output: linewith

	// getline removes the delimiter from the stream
	std::cout<<(char)fin.peek()<<std::endl; // output: p // (notice how the . was skipped)

	fin.get(line, 20, '.');
	std::cout << line << std::endl; // output: points
	// get does not remove the delimiter from the stream
	std::cout<<(char)fin.get()<<std::endl; // output: . // the . wasn't skipped

	// read(char *a, streamsize n) extracts n characters from the steams and copies them without checking what they are
	fin.read(line, 12);
	line[12] = '\0'; // read doesn't put a '\0' at the end
	std::cout<<line<<std::endl;
	/* output
		init
		newline
	*/
	// \n was also copied
	
	// peek() returns the ascii code of the nex symbol without consuming it
	// putback(char a) puts one character at the front of the stream

	std::cout<<(char)fin.peek(); // output: A
	std::cout<<(char)fin.get(); // output: A // A again because it wasn't consumed last time
	fin.putback('A');
	std::cout<<(char)fin.get(); // output: A // A again because we returned it
	fin.putback('B');
	std::cout<<(char)fin.get(); // output: B // We can put back characters different from the last consumed one
	// depending on the type of stream this may fail or be ignored

	/* Positioning in file
		There are 2 pointers associated with an open stream
			put pointer (p) -> Writing operations will begin from this point
			get pointer (g) -> Reading operations will begin from this point
		tellg()
		tellp() -> return the position of the given pointer
		seekg(streampos pos)
		seekp(steampos pos) // move the given pointer to position pos
		seekg()
		seekp(streamoff offset, ios_base::seekdir way)
		seekg(streamoff offset, ios_base::seekdir way) -> move given pointer "offset" positions starting from "way"
		
		ios_base::seekdir enums
			ios::beg - beginning of the stream
			ios::cur - current position
			ios::end - end of the file
	*/

	// Getting total number of characters in the file
	fin.seekg(0, ios::end); // move to end
	std::cout<<std::endl<<fin.tellg(); // tell current position
	// output: 55

	// reading whole file
	fin.seekg(0);
	std::cout<<std::endl;
	while(fin.get(symbol)) {
	    std::cout<<symbol;
	} // outputs the file

	// or

	/*while(!fin.eof()) {
	    // reading operation here
	}*/

	fin.close();
	

	// Writing to file
	
	ofstream fout("example2.txt");
	fout << "1 line\n2 lines\n";
	// write(const char* s, streamsize n); // write n cahracters from s to the stream
	fout.write("3 lines\n4lines", 14);

	/* example2.txt
		1 line
		2 lines3 lines
		4lines
	*/
	fout.close();

 	return 0;
 }  
```