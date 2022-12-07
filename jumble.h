//John Turnbull
//20jjt
//20235355

#pragma once

#include <string>

using namespace std;

typedef char* charArrayPtr;

class BadJumbleException {
    //Exception class
    public:
        BadJumbleException(const string&);
        //Constructor
        string& what();
        //Prints error message if there is an error
    private:
        string message;
        //Error message
};

class JumblePuzzle {
    public:
        JumblePuzzle(const string&, const string&);
        JumblePuzzle(const JumblePuzzle&);
        //Constructors
        ~JumblePuzzle();
        //Destructor
        JumblePuzzle& operator=(const JumblePuzzle&);
        //Equals implemented
        int getSize() const;
        int getRowPos() const;
        int getColPos() const;
        char getDirection() const;
        int getDifficulty() const;
        charArrayPtr* getJumble() const;
        //Accessors
    private:
        int size;
        //Size of the matrix of jumbled characters
        int rowPos;
        //Row number
        int colPos;
        //Column Number
        char direction;
        //North, East, South, West
        int difficultyNum;
        //Diffuclty ranging from 2-4
        string hiddenString;
        //Word to be hidden inside the jumble, must be between 3-10 characters
        charArrayPtr* jumble;
        //Pointer
        charArrayPtr* copyCharArray(const charArrayPtr*, const int) const;
        //Copy array function, returns new char pointer
        int getRand(int);
        //Returns random number
        void deleteJumble();
        //Deletes the jumble of characters and sets it to null
        void generateJumble();
        //Generates the array of letters and inserts the hidden word inside the jumble of characters
};