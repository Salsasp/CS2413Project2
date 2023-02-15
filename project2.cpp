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
		DTarray[cols]; //initalizing DTarray with length of cols
		myTable = new string*[rows]; // set myTable equal to a 1d array of length rows
		for(int i = 0; i < rows; i++) //not sure how this works but I'll figure it out later TODO
		{
			myTable[i] = new string[cols];
		}
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
		for(rowCounter; rowCounter < noRows; rowCounter++) //loop through all lines in CSV file
		{
			for(int i = 0; i < noCols-1; i ++) //parse through each item in the line past the first item
			{
				getline(csvReader,myTable[rowCounter][i],delimiter);
			}
			getline(csvReader,myTable[rowCounter][noCols-1]);
		}
	}


	//Output Method
	void display()
	{
		for(int i = 0; i < noRows; i++)
		{
			for(int j = 0; j < noCols; j++)
			{
				cout << myTable[i][j] << " ";
			}
			cout << '\n';
		}
	}

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

    // TODO: read the data types and store in DTarray of d
	string DTarray[numCols];
	string tempStr;
	for(int i = 0; i < numCols; i++)
	{
		cin >> tempStr;
		DTarray[i] = tempStr;
	}
	d->setDTarray(DTarray);

	d->readCSV(fileName);
	d->display();

    // TODO: start reading the options till the end of the file

	file.close();
	return 0;
}