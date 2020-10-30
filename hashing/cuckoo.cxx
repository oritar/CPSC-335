// Assignment 3: Cuckoo Hashing algorithm
// Doina Bein
// An open addressing method called Cuckoo Hashing
// INPUT: an input file containing strings of maximum 255 characters, 
// one string per line
// OUTPUT: a detailed list of where the strings are inserted.     

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// cuckoo tables' size                                                        
const int tablesize = 17;
// combine the two 1-dimensional table into one 2-dimensional table           
string  t[tablesize][2];

// define the prime number used in calculating the hash values
const int prime = 39;

// compute the hash functions
size_t f(string, size_t);

// place a string in one of the hash tables
bool place_in_hash_tables (string);

// print final hash tables
void print_hash_tables();

int main() {
  // the strings to be stored in the hash tables
  string s;
  size_t i, len;
  bool placed;

  // clear the tables
  for(i=0; i< tablesize; i++) {
      t[i][0] = "";
      t[i][1] = "";
  }

  char filename[255] = "";

   // display the header
  cout << endl << "CPSC 335.01 - Programming Assignment #3: ";
  cout << "Cuckoo Hashing algorithm" << endl;
    
  // read the strings from a file
  cout << "Input the file name (no spaces)!" << endl;
  cin >> filename;

  // open the file for reading
  ifstream infile(filename);
  /* read line by line from the file */
  while ( getline(infile,s) ) {
    // place null character at the end of the line instead of <return>
    len = s.size();
    s[len-1]='\0';
    // insert the string in the cuckoo table
    placed = place_in_hash_tables(s);
    // check whether the placement was successful
    if (!placed) {
      cout << "Placement has failed" << endl;
      return -1;
    }
  }
  infile.close();

  print_hash_tables();

  return 0;
}


bool place_in_hash_tables (string s) {
  
  bool placed;
  size_t pos;
  int index;
  string temp_s, temp;
  
  temp_s = s;

  // use a counter to detect loops; if counter >= 2*tablesize, then loop
  int counter = 0;
  
  // start with table T1
  index = 0;
  
  placed = false;

  pos = f(temp_s, index);

  while((!placed ) && (counter < 2*tablesize)) {
    if (t[pos][index] == "") {
      cout << "String <" << temp_s << "> will be placed at";
      cout  << " t[" << pos <<"][" << index << "]" << endl;
      t[pos][index] = temp_s;
      placed = true;
      return placed;
    }
    else {
      cout << "String <" << temp_s << "> will be placed at" << " t[" << pos;
      cout <<"][" << index << "]" << " replacing <" << t[pos][index] << ">";
      cout << endl;

      temp = t[pos][index];
      t[pos][index] = temp_s;
      temp_s = temp;

      index = (index + 1) % 2;
      pos = f(temp, index);

      counter++;
    }
  }
  return placed;
};


// oompute the hash functions
// TO DO: complete the ELSE brach
size_t f(string s, size_t index) {
  size_t po, len;
  int i, val, temp;
  po = 1;

  len = s.size();

  if (index == 0) {
    val = s[0];
    val = val % tablesize;
    if (val < 0) val += tablesize;

    if (len == 1) 
      return val;
    
    for (i = 1; i < len; i++) {
      temp = s[i];
      po *= prime;

      po = po % tablesize;
      if (po < 0) po += tablesize;
      
      val += temp * po;
      val = val % tablesize;

      if (val < 0) val += tablesize;
    }
    return val;
}
  else {
    // TO DO: YOU NEED TO IMPLEMENT THE STEPS TO CALCULATE THE SECOND 
    // HASH FUNCTION in <val>
    val = s[len-1];
    val = val % tablesize;

    if (val < 0) val += tablesize;

    if(len == 1) return val;

    for (i = 1; i < len; ++i) { 
      temp = s[len-i-1]; //the last character in the string
      po *= prime;

      po = po % tablesize;

      if (po < 0) po += tablesize;

      val += temp*po;
      val = val % tablesize;

      if (val < 0 ) val += tablesize;
    }

    return val;
  }
}

void print_hash_tables(){
  const char sp = ' ';
  const char ln = '-';
  const int totW = 104;
  const int emWidth = 4;
  const int width = 45;
  size_t index = 0; // begin at table 1

  cout << endl << endl;
  cout << left << setw(totW) << setfill(ln) << " |" << "| "  << endl;
  cout << left << " | " << setw(emWidth) << " " << setfill(sp) << " | " << setw(width) << "Table T1 " << setfill(sp) << " | " << setw(width) << setfill(sp) << "Table T2" << " | " << endl;
  cout << left << setw(totW) << setfill(ln) << " |" << "| "  << endl;

  for(int i = 0; i < tablesize; i++ ){
    if(i < 10){
      cout << left << " | " << setfill(sp) << "[" << i << "] " << " | " << setw(width) << t[i][index] << setfill(sp) << " | "  << setw(width) << setfill(sp) << t[i][(index + 1 % 2)] << " | " << endl;
      cout << left << setw(totW) << setfill(ln) << " |" << "| "  << endl;
    }
    else {
      cout << left << " | " << setfill(sp) << "[" << i << "]" << " | " << setw(width) << t[i][index] << setfill(sp) << " | "  << setw(width) << setfill(sp) << t[i][(index + 1 % 2)] << " | " << endl;
      cout << left << setw(totW) << setfill(ln) << " |" << "| "  << endl;
    }
  }
}
