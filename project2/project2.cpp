// project2.cpp : Defines the entry point for the console application.
//Praminda Mahesh Imaduwa-Gamage, CS225

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstring>
#include <cctype> 

using namespace std;
//structure declaration
struct Word {
	string english;
	string piglatin;
};

//function prototypes
string readConsole();
Word* splitSentence(const string words, int &);
void convertTopigLatin(Word wordArr[], int size);
void displayPigLatin(const Word wordArr[], int size);

int main()
{	
	Word* wordptr = nullptr;
	int numOfwords = 0;
	char goAgain;

	do {
		//user output from readConsole() is passed to splitSentence.
		wordptr = splitSentence(readConsole(), numOfwords);
		convertTopigLatin(wordptr, numOfwords);//converting to pigLatin
		displayPigLatin(wordptr, numOfwords);//display result

		cout << endl;
		cout << "Do you want to play again (y/n): ";
		cin >> goAgain;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			goAgain = 'n';
		} 
		else if (tolower(goAgain) != 'y' && tolower(goAgain) != 'n') {
			goAgain = 'n';
		}
		cin.ignore(INT_MAX, '\n');
	} while ((tolower(goAgain) != 'n'));

	cout << "Program Terminated" << endl;
	system("pause");
	return 0;
}
//displayPigLatin function defintion
void displayPigLatin(const Word wordArr[], int size) {

	cout << "Output:" << endl;
	for (int ind = 0; ind < size; ind++) {
		cout << wordArr[ind].piglatin << " ";
	}
	cout << endl;
}
//convertTopigLatin funtion definition
void convertTopigLatin(Word wordArr[], int size) {

	const int vowelsNum = 5;
	char vowels[vowelsNum] = {'a', 'e', 'i', 'o', 'u' };
	bool isVowel;

	for (int ind = 0; ind < size; ind++) {

		isVowel = false;

		wordArr[ind].piglatin = wordArr[ind].english;

		for (int vowels_ind = 0; vowels_ind < vowelsNum; vowels_ind++) {
			if (wordArr[ind].piglatin[0] == vowels[vowels_ind]) {
				wordArr[ind].piglatin.insert(wordArr[ind].piglatin.size(), "way");
				isVowel = true;
			}
		}
		if (!isVowel) {
			wordArr[ind].piglatin.insert(wordArr[ind].piglatin.size(), 
				string(1, wordArr[ind].piglatin.at(0)).append("ay")).erase(0, 1) ;
		}
	}
}

//spliting sentences with spilitSentence function
Word * splitSentence(const string words, int &size) {
	int ind = 0;
	size = 0;

	while (words[ind] != '\0') {
		ind++;
		bool firstSpaceFlag = false;

		if (isalpha(words[ind])) {
			firstSpaceFlag = false;
		}
		else if(isspace(words[ind]) && !firstSpaceFlag) {
			size++;
			firstSpaceFlag = true;
		}
	}

	Word* englishWords = new Word[size];//dynamic array

	int letterCount = 0;
	int firstLetterInd = 0;
	int num = 0;
	bool firstSpaceFlag = false;
	bool firstLetter = true;
	
	for (int ind = 0; ind < words.size(); ind++) {
		
		if (isalpha(words[ind])) {
			if (firstLetter) {
				firstLetter = false;
				firstLetterInd = ind;
			}
			letterCount++;
			firstSpaceFlag = false;
		}
		else if (isspace(words[ind])) {
			firstLetter = true;

			if (!firstSpaceFlag) {
				
				string aword;
				aword = words.substr(firstLetterInd, letterCount);
				
				for (int ind = 0; ind < aword.size(); ind++) {
					aword[ind] = (char)tolower(aword[ind]);
				}
				englishWords[num].english = aword;
				firstSpaceFlag = true;
				num++;
			}
			letterCount = 0;
		}
	}

	return englishWords;
}

//readConsole function defition
string readConsole() {

	string userString;
	bool flag = true;

	do {
		try {
			cout << "Please enter an English sentence to convert into PigLatin: " << endl;
			getline(cin, userString);
	
			int letterCount = 0;

			for (int ind = 0; ind < userString.size(); ind++) {

				if (userString.empty()) {
					throw string("Sentence should have atleast one word");
				}
				else if (!isalpha(userString[ind]) && !isspace(userString[ind])) {
					throw string("Your entry contains non alphabetic characters.");
				}
				else if (isalpha(userString[ind])) {
					letterCount++;
				}
			}
			if (letterCount == 0) {
				throw string("Sentence should be atleast one English word");
			}
			flag = false;
		}
		catch (string exceptionString) {
			cout << exceptionString << endl;
		}

	} while (flag);

	int ind = 0;
	//remove all space at the begining of user entry
	while (!isalpha(userString[ind])) {
		ind++;
	}
	userString.erase(0, ind);

	ind = 0;
	//remove all spaces at the end of user entry
	while (!isalpha(userString[userString.size() - 1 - ind] )) {
		ind++;
	}
	userString.erase(userString.size() - ind, ind);
	//remove more than one space between two words in user entry
	ind = 0;
	while (userString[ind] != '\0') {
		if (isspace(userString[ind]) && !isalpha(userString[ind + 1 ])) {
			userString.erase(ind + 1, 1);
		}
		else {
			ind++;
		}
	}
	//add one space to the end.
	userString.insert(userString.size(), " ");

	return userString;
}