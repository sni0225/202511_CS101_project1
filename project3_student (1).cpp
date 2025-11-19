#include <vector>
#include <string>
#include <iostream>
#include <fstream>		//for i/o stream class
#include <sstream>		//for stringstream class
#include "stemmer.h"	//contains a function called stemString(string word) that returns the stem of a word.
#include <iomanip>
using namespace std;

//PROVIDED FUNCTIONS
/*
	NAME:  read_tweets_csv_file()
	ARGUMENT: none
	RETURNS: string vector matrix
	PURPOSE: This function creates a two-dimensional string vector, fills it with tweet
	data from tweets.csv and returns it. Each row in the 2D vector contains tweet id, user id,
	datetime, senator name and tweet text.
*/
vector<vector<string>> read_tweets_csv_file();	

vector<vector<string>> read_tweets_csv_file()
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

	//commented out because we don't need
    /*
	for(auto & rowV : tweets)
    {
    	
		
        cout <<rowV[3] << " " <<  rowV[4] << endl;

    }
    */
    cout << tweets.size() <<" tweets." << endl;

    return tweets;

}

/*
	NAME:  readEmotionFile()
	ARGUMENT: string path
	RETURNS: string vector
	PURPOSE: This functions takes the name of the emotion word file (e.g.
	positive-words.txt) and creates a one dimensional string vector filled with words from the
	parameter file and returns it.
*/
vector<string> readEmotionFile(string path);

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

//TO DO 1: Create a function that takes the 2D tweets vector as parameter, creates a 1D string
//vector that includes the unique names of the senators and returns it.

/*
	NAME: senator_names()
	ARGUMENTS: vector<vector<string>> input
	RETURNS: vector<string> senator_names
	PURPOSE: This function takes a 2D string vector filled with tweet data,
	and returns a 1D string vector of unique senator names.
*/

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
            senator_names.push_back(input[idx][3]);         //if senator name is unique, push back to the new vector
        }
    }
    return senator_names;
}


//TO DO 2: Create a function that takes the 2D tweets vector, 1D senator name vector, positive
//words vector and negative words vector as parameters and calculates and prints the positive
//and negative words percentage for the parameter senator name.

/*
	NAME: stem_all()
	ARGUMENTS: vector<string> unstemmed
	RETURNS: vector<string> stemmed
	PURPOSE: This function takes a string vector,
	and returns a string vector with all the elements converted to its stem.
*/
vector<string> stem_all(const vector<string>& unstemmed);

vector<string> stem_all(const vector<string>& unstemmed){
	
	vector<string> stemmed(unstemmed.size());
	
	for(size_t idx = 0; idx < unstemmed.size(); idx++){
		stemmed[idx] = stemString(unstemmed[idx]);
	}
	
	return stemmed;
}

/*
	NAME: remove_dupe()
	ARGUMENTS: vector<string> input
	RETURNS: vector<string> unique
	PURPOSE: This function takes a string vector,
	and returns a string vector with all the duplicate elements removed.
*/
vector<string> remove_dupe(const vector<string>& input);

vector<string> remove_dupe(const vector<string>& input){
	
	vector<string> unique;
	
	for(size_t i = 0; i < input.size(); i++){		//loop through list of positive/negative words
		
		bool isInVec = false;
		
		for(size_t j = 0; j < unique.size(); j++){	//loop through vector of unique words found
			if(input[i] == unique[j]){
				isInVec = true;
			}
		}
		
		if(!isInVec){
			unique.push_back(input[i]);				//if a word is unique, push back onto new vector
		}
		
	}
	return unique;
}

/*
	NAME: calc_percent()
	ARGUMENTS: vector<vector<string>> tweets, vector<string> senators, vector<string> pos_list, vector<string> neg_list
	RETURNS: void
	PURPOSE: This function takes the 2D tweets vector, 1D senator name vector, positive
	words vector and negative words vector as parameters and calculates and prints the positive
	and negative words percentage for the parameter senator name.
*/

void calc_percent(const vector<vector<string>>& tweets, const vector<string>& senators, const vector<string>& pos_list, const vector<string>& neg_list);

void calc_percent(const vector<vector<string>>& tweets, const vector<string>& senators, const vector<string>& pos_list, const vector<string>& neg_list){
	
    size_t vec_size = senators.size();		//three vectors are declared with same size as senators, their index each corresponsing to a senator
    vector<int>pos_count(vec_size);			//this integer vector keeps track of count of positive words for each senator
    vector<int>neg_count(vec_size);			//this integer vector keeps track of count of negative words for each senator
    vector<int>total(vec_size);				//this integer vector keeps track of count of total words for each senator
    
    vector<string> pos_stem_unique = remove_dupe(stem_all(pos_list));		//vectors for lists of positive words and negative words are first turned to stems 
    vector<string> neg_stem_unique = remove_dupe(stem_all(neg_list));		//and the duplicates in the list are removed
        
    for(size_t row = 0; row < tweets.size(); row++){						//loop through rows of "tweets" vector 
    	
    	//cout << "Row " << row << " : ";		//print line for debugging
    	
		//possible opti: compare twitter id instead, maybe more efficient than comparing string?
    	for(size_t sen = 0; sen < senators.size(); sen++){					//loop through "senators" vector to check if name match
    		
    		if(tweets[row][3] == senators[sen]){			//if senator name matches							
    			
    			stringstream ss(tweets[row][4]);			//convert tweet text into a string stream
    			string word, stem;				
    			while(ss >> word){				
    				total[sen]++;				//increment total word count for corresponding senator[sen]
    				stem = stemString(word);	//word is converted to stem
    				
    				for(size_t i = 0; i < pos_stem_unique.size(); i++){		//loop through processed pos_list to check for match
    					
    					if(stem == pos_stem_unique[i]){
							//cout << stem << " ";		//print line for debugging
							pos_count[sen]++;			//pos_count for corresponding senator is incremented
    					}

    				}
    				for(size_t i = 0; i < neg_stem_unique.size(); i++){		//loop through processed neg_list to check for match
    					
    					if(stem == neg_stem_unique[i]){
							//cout << stem << " ";		//print line for debugging
							neg_count[sen]++;			//neg_count for corresponding senator is incremented
    					}

    				}
    			}
    		}
    	}
    	//cout << endl;	//print line for debugging
    }
    
    /*
    //print statements for debugging
    for(size_t idx = 0; idx < total.size(); idx++){
    	cout << total[idx] << " ";
    }
    cout << endl;
    
    for(size_t idx = 0; idx < pos_count.size(); idx++){
    	cout << pos_count[idx] << " ";
    }
    cout << endl;
    */
    
    //print heading
    cout << fixed << right << setw(20) << "Senator" << setw(15) << "Positive %" << setw(15) << "Negative %" << endl;
    for(size_t idx = 0; idx < senators.size(); idx++){		//loop through each senator and print
        //print: name; positive/total; negative/total
        //count is first multiplied with 100.00 to convert from int to double
        cout << setw(20) << senators[idx] << setw(15) << 100.00 * pos_count[idx] / total[idx] << setw(15) << 100.00 * neg_count[idx] / total[idx] << endl;
    }
}



int main()
{
    vector<vector<string>> tweets = read_tweets_csv_file();				//calls read_tweets_csv_file() to create a string vector matrix "tweets"
    vector<string> pos_words = readEmotionFile("positive-words.txt");	//calls readEmotionFile() to create a string vector of positive words "pos_words"
    vector<string> neg_words = readEmotionFile("negative-words.txt");	//calls readEmotionFile() to create a string vector of negative words "neg_words"

    vector<string> senators;				//declare a vector for senator names
    senators = senator_names(tweets);       //call senator_names() to create a vector of senator names
    
    /*
    //print statements for debugging
    for(size_t idx = 0; idx < senators.size(); idx++){
    	cout << senators[idx] << endl;
    }
    cout << endl;
    */

    calc_percent(tweets, senators, pos_words, neg_words);		//call calc_percent to print things
}
