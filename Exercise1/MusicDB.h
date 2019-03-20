#pragma once
#include "Song.h"
using namespace std;

namespace MusicDB
{
	// declaration of functions in MusicDB.cpp
	void loadTheMusicDatabaseFromFile();
	void saveTheMusicDatabaseToFile();
	int returnTheTotalNumberOfSongs();
	void printAllSongsInformations();
	void addANewSongToTheDatabase();
	bool isThereANewSong();
	bool sort_ascending_by_title(Song ,Song );
	void sortByTitle();
	bool sort_ascending_by_artist(Song, Song);
	void sortByArtist();
	bool sort_ascending_by_release_year(Song, Song);
	void sortByReleaseYear();
	string toLower(char*);
	void findSongByTitle(string);
	void importSongByIDv3Tag();
}
