#include <iostream>
#include <vector>
#include <conio.h>

#include "Movie.h"

// https://github.com/seleznevae/libfort/wiki/Table-life-cycle-(CPP-API)
#include "fort.hpp"
#include <algorithm>

using namespace std;

int playerCount = 12;
vector<Movie> FetchMovies();
void DrawTable(vector<Movie>& movies);
void AddMovie(vector<Movie>& movies);
void RemoveMovie(vector<Movie>& movies);
bool CompareRankings(Movie& m1, Movie& m2);

int main()
{
	// PLAYER HIGH SCORE LIST 

	vector<Movie> movies = FetchMovies();
	DrawTable(movies);

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
				AddMovie(movies);
				break;

			case 'R':
				RemoveMovie(movies);
				break;
			
			case 'Q':
				cout << "App quit";
				appRunning = false;
				break;
		}	
	}	
	
	return 0;
}

bool CompareRankings(Movie &m1, Movie &m2)
{
	return (m1.ranking > m2.ranking);
}

void AddMovie(vector<Movie> &movies) 
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

	cout.flush();
	system("cls");

	DrawTable(movies);
}

void RemoveMovie(vector<Movie>& movies)
{
	int moviePosition = 0;
	cout << "Give rank of movie to remove:";
	cin >> moviePosition;
	movies.erase(movies.begin() + moviePosition - 1);

	DrawTable(movies);
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

void DrawTable(vector<Movie> &movies)
{
	cout.flush();
	system("cls");

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
		"Q - Quit application\n";
}