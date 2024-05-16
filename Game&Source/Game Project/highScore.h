#ifndef _highScore_h
#define _highScore_h
#include <fstream>
#include <sstream>
using namespace std;
//các hàm liên quan đến High Score

string GetHighScoreFromFile(string path)
{
	fstream HighScoreFile;
	string highscore;

	HighScoreFile.open(path, ios::in);
	HighScoreFile >> highscore;

	return highscore;
}
const char * stringToChar(string HighScoreFile){
    const char* char_pointer = HighScoreFile.c_str();
    return char_pointer;
}
void UpdateHighScore(string path,
	const int& score,
	const string& old_high_score)
{
	int oldHighScore = 0;
	fstream HighScoreFile;
	string newHighScore;
	stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = to_string(oldHighScore);

	HighScoreFile << newHighScore;
}
#endif
