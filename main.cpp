/*
#ifdef _WIN32
#include <conio.h> //For Windows
#else
#include <curses.h> //For POSIX
#define _getch() getch()
#endif
*/ //Use this when compile to windows or POSIX
#define _getch() replgetch() //remove this line when compile to Windows or POSIX\
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

//common function
#include "commonf.h"

//readFile
#include "loadfile.h"

//export data and table
#include "exporthtml.h"
#include "table.h" //display and output text file
#include "LRAndPearsonHtml.h"

//maths function
#include "statistic.h"
#include "distinct.h"
#include "LRAndPearson.h"

//histogram function
#include "histogram.h"
#include "histohtml.h"

using namespace std;

//For Repl only
//remove this when compile to Windows or POSIX
char replgetch() {
	system("/bin/stty raw");
	system("/bin/stty -echo");
	cin.clear();
	char c = getc(stdin);
	system("/bin/stty echo");
	system("/bin/stty cooked");
	return c;
}

//open file
string openFile(vector<string>&, vector<vector<double>>&, vector<vector<double>>&);

//Menu function
char getChoice(char, char);
int selVector(vector<string>, string extra = "null");
char mainMenu();
char computeMenu();
void sortByColMenu(vector<string>, vector<vector<double>>&);
char outputOptions();

//compute function
void computeFunc(vector<string>, vector<vector<double>>);

//Statistics function and menu
void statMenu(vector<string>, vector<vector<double>>);

//Distinct function and menu
void distinctMenu(vector<string>, vector<vector<double>>);

//Generate Histogram
void histogramMenu(vector<string>, vector<vector<double>>);
void displayHisto(string, vector<string>, vector<int>, string, int);

//data above and below mean
void abvBlwMean(vector<string>, vector<double>, vector<vector<double>>);
void showMeanTable(string, double, vector<vector<double>>, vector<double>, vector<double> , vector<double>, vector<double>); 
void displayTwoTable(string, double, vector<vector<double>>, vector<double>, vector<double> , vector<double>, vector<double>); 

//Pearson correlation //LR
void pearsonAndLRMenu(vector<string>, vector<double>, vector<vector<double>>);
void PCLRPrompt(vector<string>,vector<vector<double>>, vector<string>&,vector<vector<double>>&);
vector<vector<string>> getPCLRData(vector<double>,vector<vector<double>>);
void displayPCLROutput(string,vector<string>,vector<string>, vector<vector<string>>,vector<vector<double>>,double,double,double);

//Display Data
void displayData(string, vector<string>, vector<string>, vector<vector<double>>);


// user input function (range)
char getChoice(char bott, char upp) {
	cout << "\nPlease input a selection from " << bott << " to " << upp << ": " << endl;
	char ch = _getch();

	while (ch < bott || ch > upp) {
		cout << "You had entered " << ch << ", try again" << endl;
		cout << "Please input a selection from " << bott << " to " << upp << ": " << endl;
		ch = _getch();
	}

	return ch;
}

int selVector(vector<string> vect, string extra) {
	int size = vect.size(); //get size of vector
	cout << "Select Option : " << endl << endl;

	for (int i = 0; i < size; i++) //print all element with index+1
		cout << i + 1 << ". " << vect[i] << endl;

	if (extra != "null") //extra option if exist, print and ++size
		cout << ++size << ". " << extra << endl << endl;

	char c = getChoice('1', size + 48); //get selection
	cout << c << endl; //print selection
	return c - 49; //get index from input
}

//Menu Function
char mainMenu() { //print main menu and get user input
	cout << "=========== MAIN MENU ===========  " << endl << endl;
	cout << "1. Load another file               " << endl;
	cout << "2. Display and Export data         " << endl;
	cout << "3. Computation                     " << endl;
	cout << "4. Sort data by column             " << endl;
	cout << "5. Generate Report                 " << endl;
	cout << "6. EXIT                            " << endl << endl;

	return getChoice('1', '6'); //get user input 
}

char computeMenu() {  //print compute menu and get user input
	cout << "============ COMPUTATION MENU ==============" << endl << endl;
	cout << "1. Compute Statistics                       " << endl;
	cout << "2. Show Distinct Number                     " << endl;
	cout << "3. Generate Histogram                       " << endl;
	cout << "4. Data Above and Below Mean                " << endl;
	cout << "5. Pearson Correlation and Linear Regression" << endl;
	cout << "6. Back                                     " << endl << endl;

	return getChoice('1', '6'); //get user input 
}

void sortByColMenu(vector<string> colName, vector<vector<double>>& data) {
	cout << "Choose a column : " << endl << endl;
	int i = selVector(colName, "Back"); //get user input from colName

	if (i == colName.size())
    return; //user pick back

	sortByCol(data, i); // sort the data with selected column

	cout << endl << "The data is sorted by " << colName[i] << endl;
	cout << "Which order would you like to sort the data in ?" << endl << endl;
	cout << "1. Ascending " << endl;
	cout << "2. Decending " << endl << endl;

	if (getChoice('1', '2') == '2') //reverse the vector if descending
		reverse(data.begin(), data.end());
  
  clrScr();
  displayData("Data Output", {}, colName, data);
}

char outputOptions(){ //print and get export option
  cout << "Would you like to :                " << endl << endl;
	cout << "1. Export to HTML                  " << endl;
	cout << "2. Export to text file             " << endl;
	cout << "3. Export to HTML and text file    " << endl;
	cout << "4. Continue                        " << endl << endl;

  return getChoice('1','4');
};

//compute function
void computeFunc(vector<string> title, vector<vector<double>> data) {
	vector<double> id = data[0]; //get ID as string vector
	data.erase(data.begin()); //remove ID from data
	title.erase(title.begin()); //remove ID from title

	char c = computeMenu(); //get input option
	clrScr();

	switch (c) { //call input option base on requirement
    case '1': statMenu(title, data); break;
    case '2': distinctMenu(title, data); break;
    case '3': histogramMenu(title, data); break;
    case '4': abvBlwMean(title, id, data); break;
    case '5': pearsonAndLRMenu(title, id, data); break;
    case '7': return;
	}
}

//Statistics function and menu
void statMenu(vector<string> title, vector<vector<double>> data) {
	vector<vector<double>> res, tmp; //temporary vector
	vector<string> selTitle, selFuncName;
	vector<function<double(vector<double>)>> func{ minVect, maxVect, median, mean, variance, sd };
	vector<string> funcName{ "Min", "Max", "Median", "Mean", "Variance", "Standard Deviation" };
	vector<function<double(vector<double>)>> selFunc;

	int i = selVector(title, "All"); //get title selection
	if (i == title.size()) {
		tmp = data; //compute all data
		selTitle = title;
	}else {
		tmp.push_back(data[i]); //compute specific data
		selTitle.push_back(title[i]);
	}

	int j = selVector(funcName, "All"); //get compute selection
	if (j == funcName.size()) {
		selFunc = func; //run all compute function
		selFuncName = funcName;
	}else {
		selFunc.push_back(func[j]); //compute specific function
		selFuncName.push_back(funcName[j]);
	}

	for (int i = 0; i < selFunc.size(); i++) { // run computation function
		res.emplace_back();
		for (int j = 0; j < tmp.size(); j++)
			res.back().push_back(selFunc[i](tmp[j]));
	}
  //display result
	displayData("Compute Statistics", selFuncName, selTitle, res);
}

void distinctMenu(vector<string> title, vector<vector<double>> data) {
	int i = selVector(title);
	vector<double> tmp{ data[i] };
	string selTitle = title[i];

	vector<double> res;
	vector<int> count;
	distinctNum(tmp, res, count);

	vector<double> doubleCount(count.begin(), count.end());

	displayData("Distinct Number: " + selTitle, {}, { "Number", "Count" }, transposeV({ res, doubleCount }));
}

int main() {
	//initialize variable
	vector<string> title;
	vector<vector<double>> data;
	vector<vector<double>> dataTp;

	cout << "Welcome to Bossku's system" << endl;
	string fileName = openFile(title, data, dataTp);

	while (1) {
		clrScr();
		cout << "You had loaded " << fileName << endl;
		char c = mainMenu();
		clrScr();

		switch (c) {
		case '1': openFile(title, data, dataTp); break;
		case '2': displayData("Data Output", {}, title, data); break;
		case '3': computeFunc(title, dataTp); break; //havent code
		case '4': sortByColMenu(title, data); break;
		case '5': cout << "Generate Report"; break;
		case '6': return 0;
		}
	}
	return 0;
}

//open file
string openFile(vector<string>& title, vector<vector<double>>& data, vector<vector<double>>& dataTp) {
	string fileName = loadFile(title, data);
	dataTp = transposeV(data);
	return fileName;
}

//Display data
void displayData(string title, vector<string> row, vector<string> col, vector<vector<double>> data) {
	PrintTableByVect(title, row, col, data); //display data
	cout << endl;

  exportHTML(title + ".html", title, row, col, data);
  exportTxt(title + ".txt", title, row, col, data);

  cout << "Data has been exported. Please press any key to continue" << endl;
  _getch();
}

// AboveBelow Mean Calculation function ============================
void abvBlwMean(vector<string> title, vector<double> id, vector<vector<double>> data) {
	cout << "Data Above and Below Mean " << endl;

	int choice = selVector(title); //get selected title
	double meanRes = mean(data[choice]); //get mean result for selected title
	vector<vector<double>> cmb{ id, data[choice] }; //combine id and selected title
	
  sortByRow(cmb, 1); //sort by the data of title

	int n = -1; //index to iterate
  while(cmb[1][++n] < meanRes); //find boundary

	vector<double> blwID(cmb[0].begin(), cmb[0].begin() + n);		// extract the ID above & below boundary to new vectors
	vector<double> blwData(cmb[1].begin(), cmb[1].begin() + n);	// same with data (marks)
	vector<double> abvID(cmb[0].begin() + n, cmb[0].end());
	vector<double> abvData(cmb[1].begin() + n, cmb[1].end());

	showMeanTable(title[choice], meanRes, cmb, blwID, blwData, abvID, abvData);
  displayTwoTable(title[choice], meanRes, cmb, blwID, blwData, abvID, abvData);
}
// ================================================================

void showMeanTable(string title, double meanRes, vector<vector<double>> cmb, vector<double> blwID, vector<double> blwData, vector<double> abvID, vector<double> abvData) {		// show 2 tables, above & below mean in prompt
	cout << endl << "The mean is " << meanRes << endl << endl;

	PrintTableByVect("Above", {}, { "ID", title }, transposeV({ abvID, abvData }));
	cout << endl;
	PrintTableByVect("Below", {}, { "ID", title }, transposeV({ blwID, blwData }));
	cout << endl;
}

void displayTwoTable(string title, double meanRes, vector<vector<double>> cmb, vector<double> blwID, vector<double> blwData, vector<double> abvID, vector<double> abvData){			// made just for mean, as it requires 2 tables
	// output the 2 tables in HTML (using the extra mode parameter)
	exportHTML(title + " Mean.html", title + " Above mean", {}, { "ID", title }, transposeV({ abvID, abvData }), "The mean is " + toStr(meanRes), "new");
	exportHTML(title + " Mean.html", title + " Below Mean", {}, { "ID", title }, transposeV({ blwID, blwData }), "", "last");

	ofstream dataOut;		// from here below, output in .txt
	dataOut.open(title + " Mean.txt"); 	//cout title
  dataOut << title << " mean" << endl;

  streambuf *psbuf, *backup;		// use buffer to output 2tables in .txt
  backup = cout.rdbuf();
  psbuf = dataOut.rdbuf();
  cout.rdbuf(psbuf);

  showMeanTable(title, meanRes, cmb, blwID, blwData, abvID, abvData);

  cout.rdbuf(backup);
	cout << "Data has been exported. Please press any key to continue" << endl;
  _getch();
}

void displayHisto(string title, vector<string> markRange, vector<int> freq, string starUnit, int n) {		// output histogram table

	histogramHTML(title + "\'s histogram.html", title, markRange, freq, starUnit, n);
	exportHistoTxt(title + "\'s histogram.txt", title, markRange, freq, starUnit, n); 
							
	cout << "Data has been exported. Please press any key to continue" << endl;
	_getch();
}

void histogramMenu(vector<string> title, vector<vector<double>> data) {	
	cout << "Generate Histogram" << endl;

	int choice = selVector(title);
	vector<string> markRange = { "0 - <10", "10 - <20", "20 - <30", "30 - <40", "40 - <50", "50 - <60", "60 - <70", "70 - <80", "80 - <90", "90 - 100" };
	vector<int> freq = calcMarksRange({ data[choice] });
	int n = unitDistribution(freq);					// flexible unit
	string starUnit = unitSize(n);       	  // flexible unit in string

	plotHistogram(title[choice], markRange, freq, starUnit, n);			// prompt
	cout << endl;

	displayHisto(title[choice], markRange, freq, starUnit, n);			//HTML and txt
}



void pearsonAndLRMenu(vector<string> title, vector<double> id, vector<vector<double>> data) {
  //Input Prompt
	vector<string> selTitle;
	vector<vector<double>> selData;
  PCLRPrompt(title,data, selTitle,selData);
  //Declare arguments
  vector<double> dataX = selData[0];
  vector<double> dataY = selData[1];
	double r = pearsonCorr(dataY, dataX);
  double m = slope(r,dataY, dataX);
  double b = y_Intercept(m,dataY, dataX);
  string mainTitle = selTitle[0] + "(X)" + " vs " + selTitle[1] + "(Y)";
	vector <string> rowName(id.size() + 1, "");
	rowName.back() = "Total";
  vector <string> colName = { "ID","X","Y","XY","X**2","Y**2" };
	vector<vector<string>> strVect = getPCLRData(id,selData);
  //Display Table
  displayPCLROutput(mainTitle,rowName,colName,strVect,selData,r,m,b);
	
	exportPCLRHtml(mainTitle+ "\'s PearsonCorr&LinearRegre.html",mainTitle,rowName, colName, strVect,dataY, dataX, r, m, b);
	exportPCLRTxt(mainTitle+ "\'s PearsonCorr&LinearRegre.txt",mainTitle,rowName, colName, strVect,dataY, dataX, r, m, b);

	cout << "Data has been exported. Please press any key to continue" << endl;
  _getch();
}

vector<vector<string>> getPCLRData(vector<double> id,vector<vector<double>> selData){
  // Append data into 2d vector and then transpose it to be able to display properly
  vector<double> dataX = selData[0];
  vector<double> dataY = selData[1];
  vector<double> realProductXY = productXY(dataX,dataY);
  vector<double> sqVectX = sqVect(dataX);
  vector<double> sqVectY = sqVect(dataY);
  
  vector<vector<double>> finalData = transposeV({ id,dataX,dataY,realProductXY,sqVectX,sqVectY});
  // Append the data at last row 
	finalData.push_back({ sum(dataX),sum(dataY),sum(realProductXY),sum(sqVectX),sum(sqVectY) });

	vector<vector<string>> strVect = convertDVectToSVect(finalData);
  //Insert blank space
	strVect.back().insert(strVect.back().begin(), "");
  
  strVect.back().resize(6);

  return strVect;
}

void displayPCLROutput(string mainTitle, vector<string>rowName,vector<string>colName, vector<vector<string>>strVect,vector<vector<double>>selData,double r,double m,double b){
  cout << endl;
	PrintTableByVect(mainTitle, rowName,colName, strVect);
  printComputationOfPC(selData[1], selData[0], r);
  printComputationOfLR(selData[1], selData[0], r, m, b);
  cout<< endl;
}

//PearsonLR Menu Input Prompt
void PCLRPrompt(vector<string> title,vector<vector<double>> data, vector<string> &selTitle,vector<vector<double>> &selData){
  string prompt = "XY";
  cout << "Pearson Correlation and Linear Regression" << endl;
	for (int i = 0; i < 2; i++) { //get user input
		//Ask user to determine whether which one Y Or X
		cout << endl << "Please pick for " << prompt[i] << " axis\n" << endl;

		int n = selVector(title);
		selTitle.push_back(title[n]);
		selData.push_back(data[n]);

		//remove select data
		title.erase(title.begin() + n);
		data.erase(data.begin() + n);
	}
  return;
}
