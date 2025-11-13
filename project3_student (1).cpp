#include <vector>
#include <string>
#include <iostream>
#include <fstream>		//for i/o stream class
#include <sstream>		//for stringstream class
#include "stemmer.h"	//contains a function called stemString(string word) that returns the stem of a word.
#include <iomanip>
using namespace std;

vector<vector<string>> read_tweets_csv_file();		//prototype for read_tweets_csv()
vector<string> readEmotionFile(string path);		//prototypr for readEmotionFile()

//to do 1: Create a function that takes the 2D tweets vector as parameter, creates a 1D string
//vector that includes the unique names of the senators and returns it.
vector<string> senator_names(const vector<vector<string>>& input);

vector<string> senator_names(const vector<vector<string>>& input){

    vector<string> senator_names;                           //initialized without size

    for(size_t idx = 0; idx < input.size(); idx++){         //loop through rows of the input matrix
        bool isInVec = false;
        for(size_t i = 0; i < senator_names.size(); i++){   //loop through the vector of unique senator names
            if(input[idx][3] == senator_names[i]){
                isInVec = true;
            }
        }

        if(!isInVec){
            senator_name.push_back(input[idx][3]);                       //if senator name is unique, push back to the vector
        }

    }
    return senator_names;
}


//to do 2: Create a function that takes the 2D tweets vector, 1D senator name vector, positive
//words vector and negative words vector as parameters and calculates and prints the positive
//and negative words percentage for the parameter senator name.

//name:  read_tweets_csv_file()
//argument: none
//returns: string vector matrix
//purpose: This function creates a two-dimensional string vector, fills it with tweet
//data from tweets.csv and returns it. Each row in the 2D vector contains tweet id, user id,
//datetime, senator name and tweet text.

vector<vector-<string>> read_tweets_csv_file()
{
    vector<vector<string>> tweets;
    fstream fin;
    fin.open("tweets.csv", ios::in);
    string line, word, temp;
    vector<string> row;
    getline(fin, line);
    while (getline(fin, line))
    {
        row.clear();
        stringstream s(line);
        //cout << line << endl;
        while (getline(s, word, '|')) {
          row.push_back(word);
        }
        if(row.size() == 5)
            tweets.push_back(row);
    }

    for(auto & rowV : tweets)
    {


        cout <<rowV[3] << " " <<  rowV[4] << endl;

    }

    cout << tweets.size() <<" tweets." << endl;

    return tweets;

}

//name:  readEmotionFile()
//argument: string path
//returns: string vector
//purpose: This functions takes the name of the emotion word file (e.g.
//positive-words.txt) and creates a one dimensional string vector filled with words from the
//parameter file and returns it.

vector<string> readEmotionFile(string path)
{
    vector<string> emotionWords;
    string text;
    fstream newfile;
    newfile.open(path,ios::in);  // open a file to perform write operation using file object
    if(newfile.is_open()){   //checking whether the file is open
        string line;
        while(getline(newfile, line)){ //read data from file object and put it into string.
            emotionWords.push_back(line);
        }
        newfile.close(); //close the file object.
    }
    return emotionWords;
}



int main()
{

    vector<vector<string>> tweets = read_tweets_csv_file();			//calls read_tweets_csv_file() to create a string vector matrix "tweets"
    vector<string> pos_words = readEmotionFile("positive-words.txt");	//calls readEmotionFile() to create a string vector of positive words "pos_words"
    vector<string> neg_words = readEmotionFile("negative-words.txt");	//calls readEmotionFile() to create a string vector of negative words "neg_words"

    //to do 1: Create a function that takes the 2D tweets vector as parameter, creates a 1D string
    //vector that includes the unique names of the senators and returns it.

    //to do 2: Create a function that takes the 2D tweets vector, 1D senator name vector, positive
    //words vector and negative words vector as parameters and calculates and prints the positive
    //and negative words percentage for the parameter senator name.


    /*
    //example: loop to print tweets
    for(size_t idx = 0; idx < tweets.size(); idx++){
    	cout << tweets[idx][4] << endl;

    	//splitting into words
    	stringstream ss(tweets[idx][4]);
		string word;
		while (ss >> word){
			//cout << word << endl;
			//stemString() to convert to stem
			cout << stemString(word) << " ";
			// compare the word to words in positive and negative words vectors.
			}
    */
    }

}
