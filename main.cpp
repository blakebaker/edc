//////////////////////////////////////////////////
// Title: Edit Distance Calculator
// Writen By: Blake Baker
// Due on April 24th, 2012
// Class: CPSC485 Bioinformatics 
// Prof: Christa Mccarthy
// Platform: Windows 7
// Files: main.cpp
//////////////////////////////////////////////////


/////////////////////////////////////////////////
//             Includes
/////////////////////////////////////////////////
#include <iostream>
#include <ctype.h>
#include <string>
#include <iomanip>

using namespace std;


/////////////////////////////////////////////////
//             Functions					   //
/////////////////////////////////////////////////

void getUserInput(string & word1, string & word2);
void printMatrix(char **path, int **score,int x,int y,string word1, string word2);
void reverse(string & s);



/////////////////////////////////////////////////
//             Main							   //
/////////////////////////////////////////////////

int main(){	

			/////////////////////////////////////////////////
			//--------------------Variables----------------//
			/////////////////////////////////////////////////

	string word1;// w
	string word2;// v
	string v = "";//for the path
	string w = "";//for the path
	int min;//for calculating minimum score
	int xtemp;// for storing x for path
	int ytemp;//for storing y for path

			/////////////////////////////////////////////////
			//--------------------Setup--------------------//
			/////////////////////////////////////////////////

	getUserInput(word1,word2);

	//storing the lengths of the words
	int x = word2.length();
	int y = word1.length();
	
	//Path array - | \ for the directions
	char **path = new char*[y];
	for (int i = 0; i <= y; ++i)
		path[i] = new char[x];
	
	//Score Array for the scores
	int **score = new int*[y];
	for (int i = 0; i <= y; ++i)
		score[i] = new int[x];

	//Set default values
	for(int row = 0; row <=y; row++){
		score[row][0] = row;
	}
		for(int col = 0; col <=x; col++){
		score[0][col] = col;
	}

	for(int row = 0; row <=y; row++)
		for(int col = 0; col <=x; col++)
			path[row][col] = '+';
	path[0][0] = 'X';//For the ending point of the path
	//End Setup

			////////////////////////////////////////////////////
			//-----------------Alignment Grid-----------------//
			////////////////////////////////////////////////////

	for(int row=1; row <= y; row++)
		for(int col =1; col <= x; col++)
			if (word2[col-1] == word1[row-1]){
				score[row][col] = score[row-1][col-1];
			}
			else {
				min = score[row-1][col-1];
				if(min > score[row][col-1]){
					min = score[row][col-1];
				}
				else if(min > score[row-1][col]){
					min = score[row-1][col];
				}
				score[row][col] = min + 1;
			}
	//End allignment Grid

			/////////////////////////////////////////////////
			//-----------------Path Calculation------------//
			/////////////////////////////////////////////////

	xtemp = x;
	ytemp = y;
	while(!(xtemp == 0 && ytemp == 0)){
		min = score[ytemp][xtemp];
		 if(score[ytemp-1][xtemp]>= score[ytemp-1][xtemp-1] && score[ytemp][xtemp-1]>= score[ytemp-1][xtemp-1]){
			path[ytemp][xtemp] = '\\';
			xtemp -= 1;
			ytemp -= 1;
			v.append(1,word2[xtemp]);
			w.append(1,word1[ytemp]);
		 }
		else if(score[ytemp][xtemp-1]> score[ytemp-1][xtemp] && score[ytemp-1][xtemp-1]>= score[ytemp-1][xtemp])
		{
			path[ytemp][xtemp] = '|';
			ytemp -= 1;
			w.append(1,word1[ytemp]);
			v.append(1,'_');
		}
		else if(score[ytemp-1][xtemp]>= score[ytemp][xtemp-1] && score[ytemp-1][xtemp-1]>= score[ytemp][xtemp-1]){
			path[ytemp][xtemp] = '-';
			xtemp -= 1;
			v.append(1,word2[xtemp]);
			w.append(1,'_');
		}		//if a tie or no lower score take the missmatch and 
		else{
			path[ytemp][xtemp] = '\\';
			xtemp -= 1;
			ytemp -= 1;
			v.append(1,word2[xtemp]);
			w.append(1,word1[ytemp]);
		}
		//if it reaches the zero of either column it no longer needs to check scores it can only move towards the corner
		if(xtemp == 0 && ytemp !=0)
			while(ytemp != 0){
				path[ytemp][xtemp] = '|';
				ytemp -= 1;
				w.append(1,word1[ytemp]);
				v.append(1,'_');
			}
		if(ytemp == 0 && xtemp !=0)
			while(xtemp != 0){
				path[ytemp][xtemp] = '-';
				xtemp -= 1;
				v.append(1,word2[xtemp]);
				w.append(1,'_');
			}
	}
	//reversing the calculated v and w
	reverse(v);
	reverse(w);
	//End path Calculation

			//////////////////////////////////////////////////
			//----------------OUTPUT------------------------//
			//////////////////////////////////////////////////

	//Output the 2 words
	cout << endl << "Word1 is " << word1 << "    " << "Word2 is " << word2 << endl << endl;
	//Output the Score of the allignment
	cout << "The Edit Distance score is " << score[y-1][x-1]<< endl <<endl;
	//Output the path grid +s represent those that are not travlled.
	printMatrix(path,score,x,y,word1,word2);
	//Outputing the allignment
		cout << endl <<"The Alligment is" << endl <<"V:" << v << endl << "W:" << w <<endl;
	
	//To pause the console so it does not automatically close.	
	system("PAUSE");

	return 0;
}//end main


/////////////////////////////////////////////////
//             Function Defs.				   //
/////////////////////////////////////////////////



//             getUserInput
//----------------------------------------------
// Gets the user input from the console and store
//s them in the provide strings. Returned info is
// in the strings provided. Converts user input to
//all lower case to avoid complications.
/////////////////////////////////////////////////
void getUserInput(string & word1, string & word2){
	//Getting First word
	cout << "What is your first word ";
	getline(cin, word1);
	//for loop for converting to lower case
	for (int i=0;i<strlen(word1.c_str());i++) 
        if (word1[i] >= 0x41 && word1[i] <= 0x5A) 
            word1[i] = word1[i] + 0x20;
	cout << "Word was converted to all lowercase." <<endl;
	cout << "Your first word (v) is " << word1 << endl;
		
	//Getting Second word
	cout << "What is your second word ";
	getline(cin, word2);
	//for loop for converting to lower case
	for (int i=0;i<strlen(word2.c_str());i++) 
        if (word2[i] >= 0x41 && word2[i] <= 0x5A) 
            word2[i] = word2[i] + 0x20;
	cout << "Word was converted to all lowercase." <<endl;
	cout << "Your second word (w) is " << word2 << endl;
}


//             printMatrix
//-----------------------------------------------
//	Prints out both the scoring matrix and the 
//Direction matrix. 
/////////////////////////////////////////////////
void printMatrix(char **path, int **score,int x, int y,string word1, string word2)
{
	//Printing intro and second word
	cout << "This is the Allignment Grid:" << endl << "     ";
	for(int v=0; v<x;v++)
		cout << setw(3) << word2[v];
	cout << endl;

	//For loop for printing the Scoring matrix
	for(int rowCnt = 0; rowCnt <= y; rowCnt++){
		//if else for printing the word before the matrix
		if(rowCnt != 0)
			cout << word1[rowCnt -1] << " ";
		else 
			cout << "  ";
		for(int colCnt = 0; colCnt <= x; colCnt++)
			cout << setw(3) << score[rowCnt][colCnt];
		cout << endl;
	}

	cout << endl << "This Path" << endl << "     ";
	for(int v=0; v<x;v++)
		cout << setw(3) << word2[v];
	cout << endl;
	for(int rowCnt = 0; rowCnt <= y; rowCnt++){
		//if else for printing the word before the matrix
		if(rowCnt != 0)
			cout << word1[rowCnt -1] << " ";
		else 
			cout << "  ";
		for(int colCnt = 0; colCnt <= x; colCnt++)
			cout<< setw(3) << path[rowCnt][colCnt];
		cout << endl;
	}
}


//             reverse
//-----------------------------------------------
//	Prints out both the scoring matrix and the 
//Direction matrix. mirrors the template reverse 
//from the Alg library
/////////////////////////////////////////////////
void reverse(string & s)
{
      int c;
	  //Nested For loop for swapping the end with the begining
	  //Till it reaches the middle.
	  for (int i = 0, j = s.length()-1; i < j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
      }
}