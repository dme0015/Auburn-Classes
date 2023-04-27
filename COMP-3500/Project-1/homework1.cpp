#include <iostream>
#include <fstream>
#include <string>
// infile.close() command to the end of the program.
int main()
{
   std::ifstream myfile;
   myfile.open("inputFile.txt"); // opening the .txt file

   std::string mystring; // string variable that holds the contents

   if (myfile.is_open())
   {
      char mychar;
      while (myfile) // to read in file's contents in their entirety we will stick to a while loop
      {
         mychar = myfile.get(); // get() member function of fstream class that reads in one character at a time. Does not ignore white space
         std::cout << mychar;   // outputs characters
      }
   }
   else
   {
      std::cout << "Couldn't open file\n";
   }
   return 0;
}