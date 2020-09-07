/*
#ifdef _WIN32
#include <conio.h> //For Windows
#else
#include <curses.h> //For POSIX
#define _getch() getch()
#endif
*/ //Use this when compile to windows or POSIX
#define _getch() replgetch() //remove this line when compile to Windows or POSIX
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

//compute function
void computeFunc(vector<string>, vector<vector<double>>);

//Statistics function and menu
void statMenu(vector<string>, vector<vector<double>>);

//Distinct function and menu
void distinctMenu(vector<string>, vector<vector<double>>);

//Generate Histogram
void histogramMenu(vector<string>, vector<vector<double>>);
void displayHisto(string, vector<string>, vector<int>, string, int, int);

//data above and below mean
void abvBlwMean(vector<string>, vector<double>, vector<vector<double>>);
void showMeanTable(string, vector<double>, vector<double>);
void displayTwoTable(string, vector<string>, vector<string>, vector<vector<double>>, vector<vector<double>>);

//Pearson correlation //LR
void pearsonAndLRMenu(vector<string>, vector<double>, vector<vector<double>>);



//Display Data
void displayData(string, vector<string>, vector<string>, vector<vector<double>>);


// user input function (range)
char getChoice(char bott, char upp) {
	char ch;
	cout << endl;
	cout << "Please input a selection from " << bott << " to " << upp << ": " << endl;
	ch = _getch();
	while (ch < bott || ch > upp) {
		cout << "You had entered " << ch << ", try again" << endl;
		cout << "Please input a selection from " << bott << " to " << upp << ": " << endl;
		ch = _getch();
	}
	return ch;
}

int selVector(vector<string> vect, string extra) {
	const int size = vect.size(); //get size
	cout << "Select Option : " << endl << endl;

	for (int i = 0; i < size; i++) //menu option
		cout << i + 1 << ". " << vect[i] << endl;

	int n = 0;
	if (extra != "null") {
		cout << size + 1 << ". " << extra << endl << endl;
		n++;
	}

	char c = getChoice('1', size + 48 + n);
	cout << c << endl;
	return c - 49; //get index from input
}

//Menu Function
char mainMenu() {
	cout << "=========== MAIN MENU ===========  " << endl << endl;
	cout << "1. Load another file               " << endl;
	cout << "2. Display and Export data         " << endl;
	cout << "3. Computation                     " << endl;
	cout << "4. Sort data by column             " << endl;
	cout << "5. Generate Report                 " << endl;
	cout << "6. EXIT                            " << endl << endl;

	return getChoice('1', '6');
}

char computeMenu() {
	cout << "============ COMPUTATION MENU ==============" << endl << endl;
	cout << "1. Compute Statistics                       " << endl;
	cout << "2. Show Distinct Number                     " << endl;
	cout << "3. Generate Histogram                       " << endl;
	cout << "4. Data Above and Below Mean                " << endl;
	cout << "5. Pearson correlation and Linear Regression" << endl;
	cout << "6. Back                                     " << endl << endl;

	return getChoice('1', '6');
}

void sortByColMenu(vector<string> colName, vector<vector<double>>& data) {
	const int size = colName.size(); //get size
	cout << "Choose a column : " << endl << endl;

	for (int i = 0; i < size; i++) //menu option
		cout << i + 1 << ". " << colName[i] << endl;
	cout << size + 1 << ". Back" << endl << endl;

	int i = getChoice('1', size + 48 + 1) - 49; //get index from input

	if (i == size) return; //exit without sort

	sortByCol(data, i);

	cout << endl << "The data is sorted by " << colName[i] << endl;
	cout << "Which order would you like to sort the data in ?" << endl << endl;
	cout << "1. Ascending " << endl;
	cout << "2. Decending " << endl << endl;

	if (getChoice('1', '2') == '2')
		reverse(data.begin(), data.end());
  
  clrScr();
  displayData("Data Output", {}, colName, data);
}


//compute function
void computeFunc(vector<string> title, vector<vector<double>> data) {
	vector<double> id = data[0]; //get ID as string vector
	data.erase(data.begin()); //remove ID from data
	title.erase(title.begin()); //remove ID from title

	char c = computeMenu();
	clrScr();

	switch (c)
	{
    case '1': statMenu(title, data); break;
    case '2': distinctMenu(title, data); break;
    case '3': histogramMenu(title, data); break;
    case '4': abvBlwMean(title, id, data); break;
    case '5': pearsonAndLRMenu(title, id, data); break;
    case '7': return;
	}

	//debug
	cout << "Computation End" << endl;
	_getch();
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

	int j = selVector(funcName, "All");
	if (j == funcName.size()) {
		selFunc = func;
		selFuncName = funcName;
	}else {
		selFunc.push_back(func[j]);
		selFuncName.push_back(funcName[j]);
	}

	for (int i = 0; i < selFunc.size(); i++) {
		res.emplace_back();
		for (int j = 0; j < tmp.size(); j++)
			res.back().push_back(selFunc[i](tmp[j]));
	}

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

		switch (c)
		{
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

	cout << "Would you like to :                " << endl << endl;
	cout << "1. Export to HTML                  " << endl;
	cout << "2. Export to text file             " << endl;
	cout << "3. Export to to HTML and text file " << endl;
	cout << "4. Continue                        " << endl << endl;

	char c = getChoice('1', '4');
	switch (c)
	{
    case '1': exportHTML(title + ".html", title, row, col, data); return;
    case '2': exportTxt(title + ".txt", title, row, col, data); return;
    case '3': exportHTML(title + ".html", title, row, col, data);
              exportTxt(title + ".txt", title, row, col, data); return;
    case '4': return;
	}
}

// still building==============================================
void abvBlwMean(vector<string> title, vector<double> id, vector<vector<double>> data) {
	cout << "Data Above and Below Mean " << endl;
	int n = selVector(title);

	cout << endl << "The mean is " << mean(data[n]) << endl << endl;

	showMeanTable(title[n], id, data[n]);
}

void displayTwoTable(string title, vector<string> row, vector<string> col, vector<vector<double>> dataAbv, vector<vector<double>> dataBlw) {
	cout << "Would you like to :                " << endl << endl;
	cout << "1. Export to HTML                  " << endl;
	cout << "2. Export to text file             " << endl;
	cout << "3. Export to to HTML and text file " << endl;
	cout << "4. Continue                        " << endl << endl;

	char c = getChoice('1', '4');
	switch (c)
	{
	case '1': exportHTML(title + " Mean.html", "Above", row, col, dataAbv, "new");
		exportHTML(title + " Mean.html", "Below", row, col, dataBlw, "last");
		return;
	case '2': exportTxt(title + " Mean.txt", "Above", row, col, dataAbv);
		exportTxt(title + " Mean.txt", "Below", row, col, dataBlw, "pos");
		return;
	case '3': exportHTML(title + " Mean.html", "Above", row, col, dataAbv, "new");
		exportHTML(title + " Mean.html", "Below", row, col, dataBlw, "last");
		exportTxt(title + " Mean.txt", "Above", row, col, dataAbv);
		exportTxt(title + " Mean.txt", "Below", row, col, dataBlw, "pos");
		return;
	case '4': return;
	}
}

void showMeanTable(string title, vector<double> id, vector<double> data) {
	double meanRes = mean(data);
	vector<vector<double>> cmb{ id, data };
	sortByRow(cmb, 1);

	int n = 0;
	for (int i = 0; i < cmb[1].size(); i++)
		if (cmb[1][i] >= meanRes) {
			n = i;
			break;
		}

	vector<double> blwID(cmb[0].begin(), cmb[0].begin() + n);
	vector<double> blwData(cmb[1].begin(), cmb[1].begin() + n);
	vector<double> abvID(cmb[0].begin() + n, cmb[0].end());
	vector<double> abvData(cmb[1].begin() + n, cmb[1].end());

	PrintTableByVect("Above", {}, { "ID", title }, transposeV({ abvID, abvData }));
	cout << endl;
	PrintTableByVect("Below", {}, { "ID", title }, transposeV({ blwID, blwData }));
	cout << endl;

	displayTwoTable(title, {}, { "ID", title }, transposeV({ abvID, abvData }), transposeV({ blwID, blwData }));
}

void displayHisto(string title, vector<string> markRange, vector<int> freq, string starUnit, int n, int m) {

	cout << "Would you like to :                " << endl << endl;
	cout << "1. Export to HTML                  " << endl;
	cout << "2. Export to text file             " << endl;
	cout << "3. Export to to HTML and text file " << endl;
	cout << "4. Continue                        " << endl << endl;

	char c = getChoice('1', '4');
	switch (c)
	{
	case '1': histogramHTML(title + "\'s histogram.html", title, markRange, freq, starUnit, m); return;
	case '2': cout << " create ofstream txt urself lol" << endl; return;
	case '3': histogramHTML(title + "\'s histogram.html", title, markRange, freq, starUnit, m);
		cout << " create ofstream txt urself lol" << endl; return;
	case '4': return;
	}
}

void histogramMenu(vector<string> title, vector<vector<double>> data) {
	cout << "Generate Histogram " << endl;

	int n = selVector(title);
	vector<string> markRange = { "0 - <10", "10 - <20", "20 - <30", "30 - <40", "40 - <50", "50 - <60", "60 - <70", "70 - <80", "80 - <90", "90 - 100" };
	vector<int> freq = calcMarksRange({ data[n] });
	int m = unitDistribution(freq);
	string starUnit = unitSize(m);       	  // flexible unit

	plotHistogram(title[n], markRange, freq, starUnit, m);
	cout << endl;

	displayHisto(title[n], markRange, freq, starUnit, n, m);
}

void pearsonAndLRMenu(vector<string> title, vector<double> id, vector<vector<double>> data) {
	vector<string> selTitle;
	vector<vector<double>> selData;

	string prompt = "XY";
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

	double r = pearsonCorr(selData[1], selData[0]);
	vector <string> rowName(id.size() + 1, "");
	rowName.back() = "Total";

	vector<vector<double>> c = transposeV({ id,selData[0],selData[1],productXY(selData[0],selData[1]),sqVect(selData[0]),sqVect(selData[1])});
	c.push_back({ sum(selData[0]),sum(selData[1]),sum(productXY(selData[0],selData[1])),sum(sqVect(selData[0])),sum(sqVect(selData[1])) });
	vector<vector<string>> strVect = convertDVectToSVect(c);
	strVect.back().insert(strVect.back().begin(), "");
  strVect.back().resize(6);

	PrintTableByVect("Test", rowName, { "ID","X","Y","XY","X**2","Y**2" }, strVect);
}
