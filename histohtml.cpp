#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

#include "exporthtml.h"

void cssHistogram(ofstream& dataOut){
	dataOut <<"\t* {" 												<< endl <<
						"\t\tbox-sizing: border-box;"	 	<< endl <<
						"\t\tfont-family: Arial;"    		<< endl <<
						"\t}"														<< endl << endl;
	dataOut <<"\t.container {"								<< endl <<
						"\t\tdisplay: flex;"						<< endl <<
						"\t\tflex-direction: row;"			<< endl <<
						"\t\talign-items: center;"			<< endl <<
						"\t\twidth: 100vw;" 						<< endl <<
						"\t\tbackground-color: #ddd;"		<< endl <<
						"\t}"														<< endl << endl;
	dataOut <<"\t.range {"										<< endl <<
						"\t\tflex-basis: 10%;"					<< endl <<
						"\t\ttext-align: center"				<< endl <<
						"\t}"														<< endl << endl;
	dataOut <<"\t.colorContainer{"						<< endl <<
						"\t\tflex-basis: 90%;"					<< endl <<
						"\t}"														<< endl << endl;
	dataOut <<"\t.freq {"											<< endl <<
						"\t\ttext-align: right;"				<< endl <<
						"\t\tpadding-top: 10px;" 				<< endl <<
						"\t\tpadding-bottom: 10px;" 		<< endl <<
						"\t\tcolor: white;" 						<< endl <<
						"\t}"														<< endl << endl;
}

vector<int> outputWidth(vector<int> count, int size){
	vector<int> width (10);

	for(int i = 0; i < 10; i++){
		width[i] = count[i]/size;
	}
	
	return width;
}

vector<double> percentWidth(vector<int> count, int size){
	vector<int> width = outputWidth(count, size);
	vector<double> tmp (10);

	for(int i = 0; i < 10; i++){
		tmp[i] = (width[i]/20.0)*100;
	}

	return tmp;
}

void csshistoBar(vector<string> range, vector<int> freq, vector<string> var, int n, ofstream& dataOut){
	vector<double> width = percentWidth(freq, n);
	vector<string> color = {"#4caf50", "#2196f3", "#f44336", "#808080", "#148F77", "#5DADE2","#34495E","#5499C7","#229954 ","#D4AC0D"};

	for(int i = 0; i < 10; i++){
		dataOut <<"\t." << var[i] << " {"													<< endl <<
							"\t\twidth: "<< width[i] <<"%;" 								<< endl <<
     					"\t\tbackground-color: " << color[i] << ";" 		<< endl <<
							"\t}" 																					<< endl ;
	}
	
}

void divHistoBar(vector<string> cssClassVar, vector<string> markRange, vector<int> weight, ofstream& dataOut){
	for(int i = 0; i < 10; i++){
		dataOut <<"\t<div class=\"container\">" 																										<< endl <<
							"\t\t<p class=\"range\">" << markRange[i] << "</p>"		     										 	<< endl <<
							"\t\t<div class=\"colorContainer\">" 												  										<< endl <<
							"\t\t\t<div class=\"freq " << cssClassVar[i] << "\">" << weight[i] << "</div>" 	 	<< endl <<
							"\t\t</div>"																																			<< endl <<
							"\t</div>"																																				<< endl << endl;
	}
}

void buildHistogram(string title, vector<string> range, vector<int> freq, vector<string> cssClassVar, int n, string starUnit, ofstream& dataOut){
	dataOut <<"<!DOCTYPE html>"								  << endl <<
						"<html lang=\"en\">"					  	<< endl <<
						"<head>"												  <<	endl <<	
						"\t<meta charset=\"UTF-8\" />"		<< endl <<
						"\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />" << endl <<
						"\t<style>"												<< endl << endl;

	cssHistogram(dataOut);
	csshistoBar(range, freq, cssClassVar, n, dataOut);

	dataOut <<"\t</style>" << endl << endl;
	titleHTML(title, dataOut);
	dataOut <<"</head>" << endl <<
						"<body>"  << endl << endl <<
						"\t<h2 style=\"text-align:center;\"> Histogram for "<< title <<" </h2>" << endl << endl;

	vector<int> weight = outputWidth(freq, n);
	divHistoBar(cssClassVar, range, weight, dataOut);

	dataOut << "\t<p># Note that each (*) represents " << starUnit <<" units. </p>" << endl << endl << "</body>" << endl << "</html>" << endl;
}

void histogramHTML(string fileName, string title, vector<string> range, vector<int> freq, string starUnit, int n){
	ofstream dataOut;   			// output file variable
	dataOut.open(fileName);		// open file

	// create var name for css because cant start with numbers
	vector<string> cssClassVar = {"ones", "tens", "twentys", "thirtys", "fortys", "fiftys", "sixtys", "seventys", "eightys", "ninetys"};

	buildHistogram(title, range, freq, cssClassVar, n, starUnit, dataOut);
	
	dataOut.close();
}