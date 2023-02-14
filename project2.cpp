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
	tableClass()
	{
		
	}
	tableClass(int rows, int cols)
	{
		noRows = rows;
		noCols = cols;
		DTarray[cols];
		myTable[noRows][noCols];
	}
	
	// Overload the [] operator to access a row in myTable
	string* operator[](int i); 

	//File reading Method
	void readCSV(string filename)
	{
		ifstream csvReader(filename); //initialize ifstream object
		string line; //create buffer string to read from file
		char delimiter = ','; //declare delimiter to be used in later operations
		int rowCounter = 0; //int to count row position through loop
		int delimIndex = 0; //int to keep track of indices to use in substr function
		while(getline(csvReader, line)) //check if file has another line through each loop
		{
			for(int i = 0; i < noCols; i ++) //parse through each item in the line
			{
				delimIndex = line.find(delimiter);
				myTable[rowCounter][i] = line.substr(0, delimIndex);
			}
		}
		
		cout<<line;
	}


	//Output Method
	void display();

	//Sort the table
	void sortTable();

	//Search record
	string* searchRecord(string str); // str will be from the first column

	//Search value from table
	void searchValue(string str);
	
	//Getters
	int getNumberRows() // returns the number of rows
	{
		return noRows;
	}
	int getNumberCols() // returns the number of columns
	{
		return noCols;
	}
	void outputDTarray()
	{
		for(int i = 0; i < noCols; i++)
		{
			cout<<DTarray[i]<<" ";
		}
	}
	void setDTarray(string *array)//modify the DTarray member of tableClass
	{
		DTarray = array;
	}
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
	
	ifstream file;
	file.open("input1.txt"); //open text file using fstream
	if(file.is_open())
	{
		cin.rdbuf(file.rdbuf()); //redirect cin into the txt file if the file is open
	}

	cin >> numRows >> numCols >> fileName; // read in data from txt file

	tableClass* d = new tableClass(numRows, numCols); //constuct tableClass object

	//d->readCSV(fileName);
    // TODO: read the file input name and call readCSV()
    
    // TODO: read the data types and store in DTarray of d
	string DTarray[numCols];
	string tempStr;
	for(int i = 0; i < numCols; i++)
	{
		cin >> tempStr;
		DTarray[i] = tempStr;
	}
	d->setDTarray(DTarray);

    // TODO: start reading the options till the end of the file

	file.close();
	return 0;
}