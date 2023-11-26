#include <iostream>
#include <string>
#include <random>
using namespace std;

string getWord(string& word, int guessCount);
void checkGuess(string& check, string word, string selectedWord);
void errorOutput(char& answer);
string selectWord(string& selectedWord, const string words[], int wordCount);

int main() {

    //initializing a pool of 35 5-letter words
    const int wordCount = 35;
    string words[wordCount] = {"amber", "blend", "climb", "drink", "eagle", "finch", "grasp", "happy", "icyth", "jolly",
        "kiosk", "latch", "mirth", "nudge", "opera", "prism", "quirk", "rusty", "shrub", "twist",
        "utter", "vexed", "wagon", "xerox", "yacht", "zebra", "flute", "glide", "haste", "inlay",
        "jelly", "knack", "lunge", "mango", "nifty"};

    string word;
    string selectedWord;
    
    char answer = 'Y';

    //-------------------------------------------

    cout << "Welcome to Wordle! Would you like to play? (Y or N)\t";
    cin >> answer;
    errorOutput(answer);

    while(toupper(answer) == 'Y') {
        cout << "See instructions?\t";
        cin >> answer;
        errorOutput(answer);

        while (toupper(answer) == 'Y') {
            cout << "If the letter you guess is in the correct spot, there will be an X at that spot.\nIf the letter guessed exists within the WORDLE word, but is in the incorrect spot, there will be an O at that spot.\nIf you guessed a letter that doesnt exist in the word, there will be an underscore (_) to mark it.\nGood Luck!\n\n";
            break;
        }

        //reset guess count to 0
        int guessCount = 0;

        //selecting the word for this round of the game
        selectWord(selectedWord, words, wordCount);

        //actual guessing game begins here
        while (guessCount <= 5) {
            getWord(word, guessCount);
            string check = "";
            checkGuess(check, word, selectedWord);
            if (check == "XXXXX") {
                cout << "You won!\n\n";
                break;
            } else {
                guessCount++;
            }
        }

        //outputting the word chosen to user once max guesses have been hit
        if (guessCount > 5){
            cout << "You've run out of guesses!\nThe answer was '" << selectedWord << "'\n\n";
        }

        //ask user if they want to play again
        cout << "Play again? Y or N\t";
        cin >> answer;
        errorOutput(answer);
        cout << endl;

        //exits game when answer = no
        if (toupper(answer) == 'N') {
            break;
        }
    }

    cout << "Thank you for playing Wordle!";

    return 0;
}

string getWord(string& word, int guessCount) {
    cout << "Enter guess number #" << guessCount + 1 << ":\t";
    cin >> word;
    guessCount++;
    return word;
}

void checkGuess(string& check, string word, string selectedWord) {
    for(int i = 0; i < word.length(); i++) {
        if (word[i] == selectedWord[i]) {
            check += 'X';
        } else if (selectedWord.find(word[i]) != string::npos) {
            check += 'O';
        } else {
            check += '_';
        }
    }
    cout << check << endl << endl;
}

//function to find whether answer is valid or not and displays an error message to recieve new input
void errorOutput(char& answer) {
    if (toupper(answer) != 'Y' && toupper(answer) !='N') {
        cout << "Error, input not recognized, respond with Y or N:\t";
        cin >> answer;
        errorOutput(answer);
    }
}

//uses a random number generator to pick a number between 1-34 and selects that word from the array
string selectWord(string& selectedWord, const string words[], int wordCount) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dis(0, wordCount - 1);
    int random_number = dis(gen);

    selectedWord = words[random_number];

    return selectedWord;
}