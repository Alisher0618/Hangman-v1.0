#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <fstream>
using namespace std;

#define MAX_WRONG 8

string trim(const string& str) {
    std::size_t first = str.find_first_not_of(" \t\r\n");
    std::size_t last = str.find_last_not_of(" \t\r\n");
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

int main(){
    ifstream file("words.txt");
    string str;
    vector<string>words;

    if (file.is_open()) {
        while(getline(file, str)){
            str = trim(str);
            words.push_back(static_cast<string>(str));
        }
        file.close();
    } else {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }
    
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(words.begin(), words.end());

    const string THE_WORD = words[0]; 

    int wrong = 0;
    string soFar(THE_WORD.size(), '-'); 
    string used = ""; 
    cout << "Welcome to Hangman. Good luck!" << endl;

    while ((wrong < MAX_WRONG) && (soFar != THE_WORD)){
        cout << "You have " << (MAX_WRONG - wrong) <<  " incorrect guesses left." << endl;
        cout << "\nYou have used the following letters:" << used << endl;
        cout << "So far the word is: " << soFar << endl; 

        char guess;
        cout << "\nEnter your guess: ";
        cin>>guess;
        cout << "\n+++++++++++++++++++++++++++++++++++++++++++\n" << endl;
        guess = toupper(guess);

        while(used.find(guess) != string::npos){
            cout << "You have already guessed " << guess << endl;
            cout << "Enter your guess: ";
            cin >> guess;
            cout << "\n+++++++++++++++++++++++++++++++++++++++++++\n" << endl;
            guess = toupper(guess);
        }
        used += guess;

        if(THE_WORD.find(guess) != string::npos){
            cout << "That is right! " << guess << " is in the word." << endl;
            for(int i = 0; i < THE_WORD.length(); i++){
                if(THE_WORD[i] == guess){
                    soFar[i] = guess;
                }
            }
        }else{
            cout << "Sorry. " << guess << " is not in the word." << endl;
            ++wrong;
        }
    }

    if(wrong == MAX_WRONG){
        cout << "\nYou have been hanged!" << endl;
        cout << "The word was: " << THE_WORD << endl;
    }else{
        cout << "\nYou guessed it!" << endl;
        cout << "The word is: " << THE_WORD << endl;

    }


    return 0;
}