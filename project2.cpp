// Spring 2023
// Data Structures
// Project 2


#include <iostream>
#include <string>
#include <fstream> // for reading fileInput
using namespace std;

string trimString(string str)
{
	for(int i = 0; i < str.length(); i++)
	{
		if(str.at(i) == ' ' || str.at(i) == '\n' || str.at(i) == '\t' || str.at(i) == '\r' || str.at(i) == '\f' || str.at(i) == '\v')
		{
			str.erase(i);
		}
	}
	return str;
}

class tableException : exception //custom exception class
{
	public:
		string outOfBounds(int index) //exception for index out of bounds
		{
			return "Column Number " + to_string(index) + " out of bounds";
		}
		string invalidType() //exception for if a non numeric argument is used for the findMin function
		{
			return "Non-numerical data type used as argument.";
		}
		string nameNotPresent() //exception for if name is not within the table
		{
			return "Record not found";
		}
};

class tableClass {
protected:
	string** myTable; // 2D string array to store all values (strings and numbers)
	string* DTarray; // 1D array to store the data types of each column
	int noRows, noCols; // number of rows and columns

public:
	//Constructors
	tableClass() //empty default constructor
	{
		
	}
	tableClass(int rows, int cols) //main constructor which initializes rows and column sizes
	{
		noRows = rows;
		noCols = cols;
		DTarray = new string[noCols]; //initalizing DTarray with length of cols
		myTable = new string*[rows]; // set myTable equal to a 1d array of length rows
		for(int i = 0; i < rows; i++)//assign each element(pointer) of myTable to a string array, representing rows
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
			for(int i = 0; i < noCols-1; i ++) 
			{
				getline(csvReader,myTable[rowCounter][i],delimiter); //parse through each item in the line using a delimiter
			}
			getline(csvReader,myTable[rowCounter][noCols-1]); //parse the last item in a line which does not have a comma at the end
			myTable[rowCounter][noCols-1] = trimString(myTable[rowCounter][noCols-1]);
			
		}
	}


	//Output Method
	void display()
	{
		for(int i = 0; i < noCols; i++) //loop through each element of DTarray to output
		{
			cout << DTarray[i] << " ";
		}
		cout << '\n';
		for(int i = 0; i < noRows; i++) //nested loop to print every element of 2d array
		{
			for(int j = 0; j < noCols; j++)
			{
				cout << myTable[i][j] << '\t';
			}
			cout << '\n';
		}
	}

	//Sort the table
	void sortTable() //function utilizing insertion sort to sort table based on first column data
	{
		string* tempRow; //temp variable to hold shifting data during sort process
		for(int i = 1; i < noRows; i++) //loop through each row in table
		{
			//shift all elements to add smaller elements to front
			for(int j = i; j > 0 && myTable[j-1][0].compare(myTable[j][0]) > 0; j--)//shift elements while previous element is greater than next element
			{
				tempRow = myTable[j-1]; //temp var to store row for swapping
				myTable[j-1] = myTable[j]; //swap left row with right row
				myTable[j] = tempRow; //swap right row with left row
			}
		}
	}

	//Search record
	string* searchRecord(string str) // str will be from the first column
	{
		string* rowData = new string[noCols]; //1d string array to hold row data
		string tempVal;
		for(int i = 0; i < noRows; i++) //nested loop through all rows in table
		{
			if(myTable[i][0].compare(str) == 0) //check that first column data is the same as the target str
			{
				for(int j = 0; j < noCols; j++) //loop to copy all data from a row into rowData
				{
					tempVal = myTable[i][j];
					rowData[j] = tempVal;
				}
				return rowData;
			}
		}
			return NULL; //exception for if no such str exists
		
	}
	//Search value from table
	void searchValue(string str)
	{
		bool found = false; //boolean var to keep track of whether str has been found
		cout << "Searching for " << str << '\n';
		for(int i = 0; i < noRows; i++) //nested for loop to check every element of table
		{
			for(int j = 0; j < noCols; j++)
			{
				if(myTable[i][j].compare(str) == 0) //check if strings are the same
				{
					cout << " found in (" << i << "," << j << ")" << '\n';
					found = true;
				}
			}
		}
		if(!found) cout << "Value not found" << '\n'; //if string is not in the table
	}
	
	//Getters
	int getNumberRows() // returns the number of rows
	{
		return noRows;
	}
	int getNumberCols() // returns the number of columns
	{
		return noCols;
	}
	void setDTarray(string* array)//modify the DTarray member of tableClass
	{
		for(int i = 0; i < noCols; i++) //copy each element from argument into DTarray
		{
			DTarray[i] = array[i];
		}
	}
	tableClass* getColumns(int colLeft, int colRight) // returns a tableClass with a set of columns from colLeft to colRight indices
	{
		tableClass* newTable = new tableClass(noRows, (colRight - colLeft)); //create a new tableClass with size equal to difference between boundaries
		string tempArray[colRight-colLeft];  //temp array to be used as argument for setDTarray()
		for(int i = 0; i < (colRight-colLeft); i++)
		{
			tempArray[i] = DTarray[i+colLeft]; //copy values
		}
		newTable->setDTarray(tempArray); //call function to setDTarray
		for(int i = 0; i < noRows; i++) // outer loop for rows
		{
			for(int j = 0; j < (colRight - colLeft); j++) //inner loop for columns
			{
				newTable->myTable[i][j] = myTable[i][j+colLeft]; //set new table values equal to current table values within boundaries
			}
		}
		return newTable;
	}
	tableClass* getRows(int rowTop, int rowBottom) // returns a tableClass with a set of rows from rowTop to rowBottom indices
	{
		tableClass* newTable = new tableClass((rowBottom - rowTop), noCols); //create a new tableClass with size equal to difference between boundaries
		for(int i = 0; i < noCols; i++) // outer loop for columns
		{
			for(int j = 0; j < (rowBottom - rowTop); j++) //inner loop for rows
			{
				newTable->myTable[j][i] = myTable[j+rowTop][i]; //set new table values equal to current table values within boundaries
			}
		}
		newTable->setDTarray(DTarray);
		return newTable;
	}
	tableClass* getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom) // returns a tableClass with the data between the cols and rows given
	{
		tableClass* newTable = new tableClass((rowBottom-rowTop), (colRight - colLeft)); //create a new tableClass with size equal to difference between boundaries
		string tempArray[colRight-colLeft];
		for(int i = 0; i < (colRight-colLeft); i++)//copy DTarray elements from within specified boundaries
		{
			tempArray[i] = DTarray[i+colLeft]; //copying elements
		}
		newTable->setDTarray(tempArray);
		for(int i = 0; i < (rowBottom - rowTop); i++) // outer loop for rows
		{
			for(int j = 0; j < (colRight - colLeft); j++) //inner loop for columns
			{
				newTable->myTable[i][j] = myTable[i+rowTop][j+colLeft]; //set new table values equal to current table values within boundaries
			}
		}
		return newTable;
	}

	//Find info of a given column
	double findMin(int colNumber)// returns the min of the given column
	{
		double min = stod(myTable[0][colNumber]);
		for(int i = 1; i < noRows; i++)//loop through all rows in table
		{
			if(stod(myTable[i][colNumber]) < min)
			{
				min = stod(myTable[i][colNumber]);
			}
		}
		return min;
	} 

	//Destructor
	~tableClass()
	{
		delete[] myTable;
	}
};

int main()
{
	//declaring variables
	string fileName, name, V, I, C1, C2, R1, R2, S1, S2, S3, S4;
	tableClass* c;
	tableClass* r;
	tableClass* s;
	int numRows, numCols;
	string* record;
	char option;
	
	ifstream file; //ifstream object to read data from input file
	file.open("input1.txt"); //open text file using fstream
	if(file.is_open())
	{
		cin.rdbuf(file.rdbuf()); //redirect cin into the txt file if the file is open
	}

	cin >> numRows >> numCols >> fileName; // read in data from txt file
	cout<<"NumRows: "<<numRows<<'\n'<<"NumCols: "<<numCols<<'\n'; //output numRows and numCols
	cout<<"FileName: "<<fileName<<'\n'; //output filename

	tableClass* d = new tableClass(numRows, numCols); //constuct tableClass object

    //read the data types and store in DTarray of d
	string DTarray[numCols];
	string tempStr;
	for(int i = 0; i < numCols; i++)//read in column data types into DTarray
	{
		cin >> tempStr;
		DTarray[i] = tempStr;
	}
	d->setDTarray(DTarray); //initialize class data
	d->readCSV(fileName); //read data into table
	d->sortTable(); //sort table elements
	while(cin >> option) //check that there are more things to be read in
	{
		switch(option)
		{
			case 'F': //return the row of the value corresponding to the first column
				cin >> name; //read in data
				record = d->searchRecord(name); //call class function to search table for data
				try
				{
					if(record == NULL)throw tableException(); //throw exception if name is not in the table
					cout << "Record found:" << '\n';
					for(int i = 0; i < numCols; i++) //for loop to output all data in row
					{
						cout << '\t' << record[i];
					}
					cout << '\n';
				}
				catch(tableException e) 
				{
					cout << e.nameNotPresent() << '\n'; //output in case that data was not found
				}
				delete[] record; //deleting dynamic record array to prevent memory leak
				break;

			case 'V': //find value in table and return its row and column number
				cin >> V;
				d->searchValue(V); //seachValue function
				break;

			case 'D': //display data in tableClass object
				d->display();
				break;

			case 'I': //find the min value of a given column
				cin >> I;
				try
				{
					if(stoi(I) < 3 || stoi(I) >= 6)throw tableException(); //if the column number is out of bounds or non numerical, throw exception
					cout<<"Min of "<<stoi(I)<<" is "<< d->findMin(stoi(I)) << endl;
				}				
				catch(tableException e)
				{
					if(stoi(I) < 3)cout << e.invalidType() << '\n'; //exception for non-numeric column
					if(stoi(I) >= 6)cout << e.outOfBounds(stoi(I)) << '\n'; //exception for out of bounds
				}
				break;

			case 'C': //return a tableClass object that is a subset of the columns between 2 given boundaries
				cin >> C1 >> C2;
				c = d->getColumns(stoi(C1), stoi(C2)); //set c address equal to tableClass object generated by getColumns()
				c->display(); //display the data of c
				delete(c); //delete to free memory
				break;

			case 'R': //return a tableClass object that is a subset of the rows between 2 given boundaries
				cin >> R1 >> R2;
				r = d->getRows(stoi(R1), stoi(R2)); //set r address equal to tableClass object generated by getRows()
				r->display(); //display the data of r
				delete(r); //delete to free memory
				break;

			case 'S': //return a tableClass object that is a subset of the rows and columns between 4 given boundaries (2 for rows, 2 for cols)
				cin >> S1 >> S2 >> S3 >> S4;
				s = d->getRowsCols(stoi(S1),stoi(S2),stoi(S3),stoi(S4)); //set s address equal to tableClass object generated by getRowsColumns()
				s->display(); //display the data of s
				delete(s); //delete to free memory
				break;

			default: //default case
				cout << "There was an error reading input." << endl;
		}
	}
	delete(d); //delete tableClass object 2
	file.close(); //close the ifstream object
	return 0;
}