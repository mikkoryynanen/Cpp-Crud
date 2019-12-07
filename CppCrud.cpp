#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include "Movie.h"

// https://github.com/seleznevae/libfort/wiki/Table-life-cycle-(CPP-API)
#include "fort.hpp"

using namespace std;

vector<Movie> movies;
int playerCount = 12;

vector<Movie> FetchMovies();
void DrawTable();
void AddMovie();
void ClearWindow();
void RemoveMovie();
void UpdateMovie();
bool CompareRankings(Movie& m1, Movie& m2);

int main()
{
	//movies = FetchMovies();
	DrawTable();

	bool appRunning = true;
	while (appRunning)
	{
		char inputChar[100] = {};
		cin >> inputChar;
		
		if (strlen(inputChar) > 1)
		{
			cout << "Invalid input\n";
			continue;
		}

		switch (toupper(inputChar[0]))
		{
			case 'A':
				AddMovie();
				break;

			case 'R':
				RemoveMovie();
				break;

			case 'U':
				UpdateMovie();
				break;
			
			case 'Q':
				cout << "App quit";
				appRunning = false;
				break;
		}	
	}		
	return 0;
}

bool CompareRankings(Movie& m1, Movie& m2)
{
	return (m1.ranking > m2.ranking);
}

void AddMovie()
{
	string inputString = "";
	float ranking = 0;

	cout << "A: ";
	getline(cin >> ws, inputString);
	cout << "Added " << inputString << " to list" << endl;
	cout << "Add ranking to '" << inputString << "' from 0 to 10: ";

	while (true)
	{
		cin.clear();
		cin >> ranking;
		if (ranking > 10 || ranking < 0)
		{
			cout << ranking << " is not valid ranking. Add a rank between 0 and 10\n";
			cout << "Add ranking to " << inputString << "from 0 to 10: ";
		}
		else
		{
			break;
		}
	}

	Movie movie;
	movie.title = inputString;
	movie.ranking = ranking;
	movies.push_back(movie);

	sort(movies.begin(), movies.end(), CompareRankings);

	ClearWindow();

	DrawTable();
}

void RemoveMovie()
{
	int moviePosition = 0;
	cout << "Give rank of movie to UPDATE:";
	cin >> moviePosition;
	movies.erase(movies.begin() + moviePosition - 1);

	DrawTable();
}

void UpdateMovie()
{
	int moviePosition = 0;
	cout << "Give rank of movie to UPDATE:";
	cin >> moviePosition;

	moviePosition--;
	Movie& m = movies[moviePosition];

	string newTitle;
	cout << "Change '" << m.title << "' title to: ";
	cin >> newTitle;
	m.title = newTitle;

	int newRanking;
	cout << "Change '" << m.title << "' ranking from " << m.ranking << " to: ";
	cin >> newRanking;
	m.ranking = newRanking;

	DrawTable();
}

vector<Movie> FetchMovies()
{
	vector<Movie> movies;
	for (size_t i = 0; i < playerCount; i++)
	{
		Movie movie;
		movie.title = "a very long Movie title" + std::to_string(i + 1);
		movie.ranking = i + 1;

		movies.push_back(movie);
	}
	return movies;
}

void ClearWindow()
{
	cout.flush();
	system("cls");
}

void DrawTable()
{
	ClearWindow();

	fort::char_table table;
	table << fort::header
		<< "Rank" << "Title" << "Rating" << fort::endr;
	for (size_t i = 0; i < movies.size(); i++)
	{
		table << to_string(i + 1) << movies[i].title << movies[i].ranking << fort::endr;
	}

	cout << table.to_string() << endl;

	cout << "Commands:\n" <<
		"A- Add a movie\n" <<
		"R - Remove movie\n" <<
		"U - Update movie\n" <<
		"Q - Quit application\n";
}