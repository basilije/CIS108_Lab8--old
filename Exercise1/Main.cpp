#include <iostream>
#include <string>
#include "conio.h"
#include "MusicDB.h"

using namespace std;

string command_entered;
int number_of_songs_in_db;

// A help function that prints the possible commands
void printHelp()
{
	cout << endl << "add    : Add a new song to the database " << endl;
	cout << "list   : List the songs in the database " << endl;
	cout << "save   : Save the songs to the database " << endl;
	cout << "sort   : Sort the database " << endl;
	cout << "find   : Find the song by title " << endl;
	cout << "import : Import the IDv3 tag from the mp3 file to the database " << endl;
	cout << "help   : Display a menu explaining the commands to the users " << endl;
	cout << "exit   : Exit the program " << endl << endl;
}

// an auxiliary function that saves the song and count the number of songs
void saveTheSong()
{
	if (MusicDB::isThereANewSong())  // only if there is a new song entered
	{
		MusicDB::saveTheMusicDatabaseToFile();  // append that song to the current database
		MusicDB::loadTheMusicDatabaseFromFile();  // reload the database
		number_of_songs_in_db = MusicDB::returnTheTotalNumberOfSongs();  // get the number of total songs
	}
	else
		cout << "There is no new song to save." << endl;  // if there isn't a new songs, just warn the user about that
}


int main()
{
	MusicDB::loadTheMusicDatabaseFromFile();  // try to load music database from the file
	number_of_songs_in_db = MusicDB::returnTheTotalNumberOfSongs();  // get a total number of songs
	printHelp();  // print the help

	do  // help until command 'exit' is entered
	{
		cout << "> ";  // print the defualt terminal string
		cin >> command_entered;  // get the command

		if (command_entered == "add")  // if the command is to add the song
			MusicDB::addANewSongToTheDatabase();  // use the function to add a new song to the database

		if (command_entered == "list")  // if the commands is to list the database
		{
			cout << "There are " << number_of_songs_in_db << " songs in the database." << endl;   // print the number of the songs in the database
			MusicDB::printAllSongsInformations();  // use the function to print all songs in the database
		}

		if (command_entered == "save")  // if the command is to save a new song
			saveTheSong(); // save the song

		if (command_entered == "sort")  // if the command is to sort the database
		{
			cout << "t : Sort by song title  " << endl;
			cout << "a : Sort by artist " << endl;
			cout << "y : Sort by release year  " << endl;
			cout << ">> ";  // print the double default terminal string (wakka-wakka)
			cin >> command_entered;  // get the command
			if (command_entered == "t")
				MusicDB::sortByTitle();  // sort by title
			if (command_entered == "a")
				MusicDB::sortByArtist();  // sort by artist
			if (command_entered == "y")
				MusicDB::sortByReleaseYear();   // sort by year
		}

		if (command_entered == "find")  // if the command is to find the song
		{
			cout << "Enter the song title to find >> ";
			cin >> command_entered;  // get the song title
			MusicDB::findSongByTitle(command_entered);  // find the song
		}

		if (command_entered == "import")  // if the command is to import the song to the database
		{ 
			MusicDB::importSongByIDv3Tag();  // start the import procedure and copy it to the MusicDB::song_to_add structure
			saveTheSong();  // save the song
		}
		
		if (command_entered == "help")  // if the command is to print available commands
			printHelp();  // print the available commands

	} while (command_entered != "exit");  // if the command is to exit, exit the loop

	return 0;
}
