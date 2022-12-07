//John Turnbull
//20jjt
//20235355

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "jumble.h"

using namespace std;

BadJumbleException::BadJumbleException(const string& msg) : message(msg) {}
string& BadJumbleException::what() { 
    return message; 
    }

JumblePuzzle::JumblePuzzle(const string& hidden, const string& difficulty) : hiddenString(hidden) {
    int hiddenSize;
    char diff;
    int seed;

    hiddenSize = hidden.length();
    if(hiddenSize < 3)
		throw BadJumbleException("String is not big enough");

	if(hiddenSize > 10)
		throw BadJumbleException("String is too big");

    diff = difficulty.at(0);
	if(diff == 'E' || diff == 'e')
		difficultyNum = 2;
	else 
        if(diff == 'M' || diff == 'm')
		    difficultyNum = 3;
	    else 
            if(diff == 'H' || diff == 'h')
		        difficultyNum = 4;
	        else
		        throw BadJumbleException("Difficulty not in scope");
                
	size = hiddenSize * difficultyNum;
	jumble = new charArrayPtr[size];

	for(int i = 0; i < size; i++) {
		jumble[i] = new char[size];
    }

	seed = static_cast<int>(time(nullptr));
	srand(seed);

	generateJumble();
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& jp) {
	size = jp.getSize();
	rowPos = jp.getRowPos();
	colPos = jp.getColPos();
	direction = jp.getDirection();
	difficultyNum = jp.getDifficulty();
	hiddenString = string(jp.hiddenString);
    jumble = copyCharArray(jp.getJumble(), size);
}

JumblePuzzle::~JumblePuzzle() {
	deleteJumble();
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& jp) {
	if(this != &jp) {
		deleteJumble();
		size = jp.getSize();
		jumble = copyCharArray(jp.getJumble(), size);
	}
	return *this;
}

int JumblePuzzle::getSize() const {
    return size;
    }

int JumblePuzzle::getRowPos() const {
    return rowPos;
    }

int JumblePuzzle::getColPos() const { 
    return colPos; 
    }

char JumblePuzzle::getDirection() const { 
    return direction; 
    }

int JumblePuzzle::getDifficulty() const { 
    return difficultyNum; 
    }

charArrayPtr* JumblePuzzle::getJumble() const {
	return copyCharArray(jumble, size);
}
    
charArrayPtr* JumblePuzzle::copyCharArray(const charArrayPtr* copyJumble, const int copySize) const {
	int sz = copySize;
	charArrayPtr* puzzle = new charArrayPtr[sz];

	for(int i = 0; i < sz; i++) {
		puzzle[i] = new char[sz];
    }
	for(int i = 0; i < sz; i++) {
		for(int j = 0; j < sz; j++){
			puzzle[i][j] = copyJumble[i][j];
        }
    }
	return puzzle;
}

int JumblePuzzle::getRand(int number) {
    return rand() % number; 
    }

void JumblePuzzle::deleteJumble() {
	for(int i = 0; i < size; i++) {
		delete[] jumble[i];
    }
	delete[] jumble;
	jumble = nullptr;
}

void JumblePuzzle::generateJumble() {
    int row, col;
    int hiddenSize = size / difficultyNum;
    bool flag = true;
	string dir("nesw");
    
	for(row = 0; row < size; row++) {
		for(col = 0; col < size; col++) {
			jumble[row][col] = 97 + getRand(26);
		}
    }

	rowPos = getRand(size);
	colPos = getRand(size);
    jumble[rowPos][colPos] = hiddenString.at(0);

	while(flag) {
        int position = 1;
		direction = dir.at(getRand(4));
		int letters_left = hiddenSize - 1;
		int room_left;
		
		if(direction == 'n') {
			row = rowPos - 1;
			room_left = row;
			if (letters_left > room_left) {
				continue;
                //NOT ENOUGH SPACE NORTH
			}
			else{
				while(position < hiddenSize && row >= 0) {
					jumble[row][colPos] = hiddenString.at(position);
					row--;
					position++;
				}
			}
		}
		else if(direction == 'e') {
			col = colPos + 1;
			room_left = (size - 1) - col;
			if (letters_left > room_left) {
				continue;
                //NOT ENOUGH SPACE EAST
			}
			else{
				while(position < hiddenSize && col < size) {
					jumble[rowPos][col] = hiddenString.at(position);
					col++;
					position++;
				}
			}
		}
		else if(direction == 's') {
			row = rowPos + 1;
			room_left = (size - 1) - row;
			if (letters_left > room_left) {
				continue;
                //NOT ENOUGH SPACE SOUTH
			}
			else {
				while(position < hiddenSize && row < size) {
					jumble[row][colPos] = hiddenString.at(position);
					row++;
					position++;
				}
			}
		}
		else if(direction == 'w') {
			col = colPos - 1;
			room_left = col;
			if (letters_left > room_left) {
				continue;
                //NOT ENOUGH SPACE WEST
			}
			else{
				while(position < hiddenSize && col >= 0) {
					jumble[rowPos][col] = hiddenString.at(position);
					col--;
					position++;
				}
			}
		}

		if(position == hiddenSize){
			flag = false;
        }
	}
}