// Spring 2023
// Data Structures
// Project 2


#include <iostream>
#include <string>
#include <fstream> // for reading fileInput

using namespace std;

class tableClass {
protected:
	string** myTable; // 2D string array to store all values (strings and numbers)
	string* DTarray; // 1D array to store the data types of each column
	int noRows, noCols; // number of rows and columns

public:
	//Constructors
	tableClass();
	tableClass(int rows, int cols);
	
	// Overload the [] operator to access a row in myTable
	string* operator[](int i); 

	//File reading Method
	void readCSV(string filename);

	//Output Method
	void display();

	//Sort the table
	void sortTable();

	//Search record
	string* searchRecord(string str); // str will be from the first column

	//Search value from table
	void searchValue(string str);
	
	//Getters
	int getNumberRows(); // returns the number of rows
	int getNumberCols(); // returns the number of columns
	tableClass* getColumns(int colLeft, int colRight); // returns a tableClass with a set of columns from colLeft to colRight indices
	tableClass* getRows(int rowTop, int rowBottom); // returns a tableClass with a set of rows from rowTop to rowBottom indices
	tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom); // returns a tableClass with the data between the cols and rows given

	//Find info of a given column
	double findMin(int colNumber); // returns the min of the given column

	//Destructor
	~tableClass();
};



int main()
{
	int numRows, numCols;
	string fileName;
	char option;

	cin >> numRows >> numCols >> fileName;
	cout << "NumRows: " << numRows << endl;
	cout << "NumCols: " << numCols << endl;
	cout << "FileName: " << fileName << endl;

	tableClass* d = new tableClass(numRows, numCols);

    // TODO: read the file input name and call readCSV()
    
    // TODO: read the data types and store in DTarray of d

    // TODO: start reading the options till the end of the file

	return 0;
}