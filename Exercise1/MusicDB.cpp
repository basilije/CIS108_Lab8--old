#include "Song.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <id3/tag.h>
#include "id3/misc_support.h"

using namespace std;


namespace MusicDB
{

	const int MAX_SONG_RECORDS = 8;  // define a max number of song records in database
	string binary_database_file_name = "MyFavoriteSongs.db";  // define the database file name
	int total_number_of_songs;  // integer to keep total number of songs in any time
	vector<Song> all_songs; // make an vector for storing all songs
	Song song_to_add;  // make a one-element structure for adding a new song
	bool there_is_a_new_song;  // define the bool that will know if there is a new song entered
	vector<Song>::iterator all_songs_itr;  // Initializing an iterator
	Song the_song;  // Initializing a variable for picking up the current iterator *value


	// a function for loading the song database into the array and counting a number of songs
	void loadTheMusicDatabaseFromFile()
	{
		all_songs.clear();  // clear the vector
		Song the_song;  // make a one-element structure for reading song-by-song from a database
		ifstream file;  // construct a ifstream object
		total_number_of_songs = 0;  // set number of songs to 0

		try
		{
			file.open(binary_database_file_name, ios::in | ios::binary);  // open the file for reading
			file.exceptions(ifstream::eofbit | ifstream::failbit);  // set the possible exceptions when opening the file

			while (file.is_open() && !file.eof())  // repeat if file exists and it is not a end of file
			{
				file.exceptions(ifstream::badbit | ifstream::eofbit);  // set the possible exceptions when reading the file
				try
				{
					file.read((char*)& the_song, sizeof(the_song));  // read the one song from the file
					if (total_number_of_songs <= MAX_SONG_RECORDS - 1)  // if there is a space in an array
						all_songs.push_back(the_song);  // add that song to the end ov vector
					total_number_of_songs++;  // increase the number of total songs
				}
				catch (const exception & exc)
				{
					(void)exc;  // silent catch
				}
			}
			file.close();  // close the file
		}

		catch (const exception &exc)
		{
			cout << "Failed to load the music database: Failed to open file '" << binary_database_file_name << "'" << endl;  // if there is exception print the sentence defined in assginment
			(void)exc;  // silent catch
		}

	}

	// a function for returning number of songs that is in variable 'total_number_of_songs'
	int returnTheTotalNumberOfSongs()
	{
		return total_number_of_songs;  // return a number of songs
	}


	// function that prints info of all songs in the database until the defined numer
	void printAllSongsInformations()
	{
		int song_number = 0;  // define the integer for storing the song's order number
		string genre_string;  // define the string for genre output


		for (all_songs_itr = all_songs.begin(); all_songs_itr < all_songs.end(); all_songs_itr++) // through the loop
		//for (int song_number_counter = 0; song_number_counter < song_number; song_number_counter++) 
		{
			the_song = *all_songs_itr;  //picking up the current iterator value
			cout << "Song #" << song_number + 1 << ":" << endl;  // print a song order number (+1 cause the array index starts from 0)
			cout << "  Title:   " << the_song.song_title << endl; // print a song title from an array
			cout << "  Artist:  " << the_song.artist_name << endl; // print a artist name from an array
			cout << "  Album:   " << the_song.album_name << endl; // print a album name from an array
			cout << "  Track #: " << the_song.track_number << endl; // print a track number from an array
			cout << "  Year:    " << the_song.year_released << endl; // print a year released from an array

			switch (the_song.song_genre)  // decide which string to print as genre based on genre recorded in an array
			{
			case Blues:						 // cases are obvious
				genre_string = "Blues";
				break;
			case Country:
				genre_string = "Country";
				break;
			case Electronic:
				genre_string = "Electronic";
				break;
			case Folk:
				genre_string = "Folk";
				break;
			case HipHop:
				genre_string = "HipHop";
				break;
			case Jazz:
				genre_string = "Jazz";
				break;
			case Latin:
				genre_string = "Latin";
				break;
			case Pop:
				genre_string = "Pop";
				break;
			case Rock:
				genre_string = "Rock";
				break;
			default: // to avoid an error, Unknown (0) is default
				genre_string = "Unknown";
				break;
			}                               // end of switch

			cout << "  Genre:   " << genre_string << endl;  // print the genre selected
			song_number++;

		}  // end of for loop
	}


	// function that add a new song to the database
	void addANewSongToTheDatabase()
	{
		string input_str;  // define the strign for taking the input
		there_is_a_new_song = false;  // set that there is currently not a new song

		if (total_number_of_songs < MAX_SONG_RECORDS - 1)  // just if there is a pre-defined space (number of songs is lower than max - 1)
		{
			try
			{
				cout << "Enter song title: ";  // print to the user what type of data to enter
				getline(cin >> ws, input_str);  // get the input string (with spaces if needed)

				if (input_str.length() > sizeof(song_to_add.song_title))  // if string is bigger than a predicted space
					throw exception("Song title is to large! ");  // throw an exception
				else  // in other case
					strcpy_s(song_to_add.song_title, input_str.c_str());  // copy a string to the song_tgitle char array structure

				cout << "Enter artist: ";  // print to the user what type of data to enter
				getline(cin >> ws, input_str);  // get the input string (with spaces if needed)

				if (input_str.length() > sizeof(song_to_add.artist_name))  // if string is bigger than a predicted space
					throw exception("Artist name is to large! ");  // throw an exception
				else  // in other case
					strcpy_s(song_to_add.artist_name, input_str.c_str());  // copy a string to the artist_name char array structure

				cout << "Enter album name: ";  // print to the user what type of data to enter
				getline(cin >> ws, input_str);  // get the input string (with spaces if needed)

				if (input_str.length() > sizeof(song_to_add.album_name))  // if string is bigger than a predicted space
					throw exception("Album name is to large! ");  // throw an exception
				else  // in other case
					strcpy_s(song_to_add.album_name, input_str.c_str());  // copy a string to the album_name char array structure

				cout << "Enter track #: ";  // print to the user to enter the song's track number
				getline(cin >> ws, input_str);  // get the input string 
				try
				{
					song_to_add.track_number = stoi(input_str);  // try to convert entered string to integer and put it to the structure
				}
				catch (const exception &exc)  // if something went wrong
				{
					throw exception("Wrong track number format! ");  // throw the exeption
					(void)exc;  // silent catch
				}

				cout << "Enter year: ";  // print to the user to enter the song's year
				getline(cin >> ws, input_str);  // get the input string 
				try
				{
					song_to_add.year_released = stoi(input_str);  // try to convert entered string to integer and put it to the structure
				}
				catch (const exception &exc)  // if something went wrong
				{
					throw exception("Wrong year format! ");  // throw the exeption
					(void)exc;  // silent catch
				}

				cout << "Enter genre: ";  // print to the user to enter the song's genre
				getline(cin >> ws, input_str); // get the input string 

				song_to_add.song_genre = Unknown; // set genre to default value (Unknown=0) to avoid an error
				if (input_str == "Blues")                    // other cases are obvious
					song_to_add.song_genre = Blues;
				else if (input_str == "Country")
					song_to_add.song_genre = Country;
				else if (input_str == "Electronic")
					song_to_add.song_genre = Electronic;
				else if (input_str == "Folk")
					song_to_add.song_genre = Folk;
				else if (input_str == "HipHop")
					song_to_add.song_genre = HipHop;
				else if (input_str == "Jazz")
					song_to_add.song_genre = Jazz;
				else if (input_str == "Latin")
					song_to_add.song_genre = Latin;
				else if (input_str == "Pop")
					song_to_add.song_genre = Pop;
				else if (input_str == "Rock")
					song_to_add.song_genre = Rock;         // end of if

				there_is_a_new_song = true;  // set to there is a new song entered
			}
			catch (const exception &exc)  // if there is an exception
			{
				cout << exc.what() << endl << " Adding a new song is automatically canceled!" << endl;  // print type of exception and the information that adding is canceled
			}
		}
		else  // if the number of songs is larger than a max number of songs defined
			cout << "Could not add a new song, there are too many songs in the database." << endl;  // print that info to the user
	}

	// a function that append a new song to the database file
	void saveTheMusicDatabaseToFile()
	{
		ofstream output_file; // construct a ofstream object
		output_file.open(binary_database_file_name, ios::out | ios::app | ios::binary);  // open a file for binary appending
		output_file.write((char*)&song_to_add, sizeof(song_to_add));  // append a new song
		output_file.close(); // close the file
		there_is_a_new_song = false; // set to there is currently not a new song
	}

	// a function that return is there a valid new song entered
	bool isThereANewSong()
	{
		return there_is_a_new_song;  // return the value of the boolean variable
	}

	// sort song by title auxiliary function
	bool sort_ascending_by_title(Song left, Song right)
	{
		char* l = left.song_title;
		char* r = right.song_title;
		return strcmp(l, r) < 0;
	}

	// sort song by title function
	void sortByTitle()
	{
		sort(all_songs.begin(), all_songs.end(), sort_ascending_by_title);
	}

	// sort song by artist auxiliary function
	bool sort_ascending_by_artist(Song left, Song right)
	{
		char* l = left.artist_name;
		char* r = right.artist_name;
		return strcmp(l, r) < 0;
	}

	// sort song by artist function
	void sortByArtist()
	{
		sort(all_songs.begin(), all_songs.end(), sort_ascending_by_artist);
	}

	// sort song by year auxiliary function
	bool sort_ascending_by_release_year(Song left, Song right)
	{
		return (left.year_released < right.year_released);
	}

	// sort song by year function
	void sortByReleaseYear()
	{
		sort(all_songs.begin(), all_songs.end(), sort_ascending_by_release_year);
	}

	// convert char array characters to lower case
	string toLower(char* input_char_array)
	{
		const int char_array_size = sizeof(song_to_add.song_title);  // using an one element structure to find a size of the char array
		char output_char_array[char_array_size];  // define output char array

		for (unsigned int i = 0; i < char_array_size; i++)  // for every possible elements in input char array
			output_char_array[i] = tolower(input_char_array[i]);  // convert char by char to lower case

		return output_char_array;  // return an output char array
	}

	// sort song by title function
	void findSongByTitle(string search_title_song)
	{
		transform(search_title_song.begin(), search_title_song.end(), search_title_song.begin(), ::tolower); // convert search string to lowercase
		all_songs_itr = find_if(all_songs.begin(), all_songs.end(), [search_title_song](Song& s){ return toLower(s.song_title) == search_title_song;});  // find_if the position of iterator where first song title is equal to the search string (if exists)  p.s. " [&](auto s) " is also possible

		if (all_songs_itr != all_songs.end())  // if iterator isn't at the end, means that we found something
		{
			the_song = *all_songs_itr;  //picking up the current iterator value
			cout << "The title of the first that maches: " << the_song.song_title << endl << "Artist name: " << the_song.artist_name << endl << "Track number: " << the_song.track_number << endl << "Year released: " << the_song.year_released << endl; // print the song found details
		}
		else
			cout << "Song not found" << endl;  // print if song is not found

	}

	void importSongByIDv3Tag()
	{
		try
		{
			string  path_to_an_mp3_file;  // define the string to enter the path to a mp3 file
			cout << "Please enter the path to an MP3 file >> ";  // write the message to the user
			cin >> path_to_an_mp3_file;  // get the path


			// GetRawText() not working because of encoding (some ID3TE_UTF16 instead of ID3TE_ASCII), so I found the simpler method: https://sourceforge.net/p/id3lib/mailman/message/6270243/;

			ID3_Tag myTag(path_to_an_mp3_file.c_str());  // convert string to char* and link to the ID3_Tag
			ID3_Tag* pTag = &myTag;  // make a pointer could be used with ID3_* functions;
			
			char* song_title = ID3_GetTitle(pTag);  // get the song title
			char* artist_name = ID3_GetArtist(pTag);  // get the artist name
			char* album_name = ID3_GetAlbum(pTag);  // get the album name
			char* year_released = ID3_GetYear(pTag);  // get the date as char*
			char* track_number = ID3_GetTrack(pTag);  // get the track as char*
			char* song_genre = ID3_GetGenre(pTag); // get the song genre

			strcpy_s(song_to_add.song_title, song_title);  // copy a song title to the structure of song_to_add
			strcpy_s(song_to_add.artist_name, artist_name);  // copy an artist name to the structure of song_to_add
			strcpy_s(song_to_add.album_name, album_name);  // copy an album name to the structure of song_to_add
			song_to_add.year_released = stoi(year_released);  // convert char to int and add a year released to the structure of song_to_add
			song_to_add.track_number = stoi(track_number);  // convert char to int and add a track number to the structure of song_to_add

			string song_genre_string;
			song_genre_string = song_genre;  // conver char* to string for comparing;

			song_to_add.song_genre = Unknown; // set genre to default value (Unknown=0) to avoid an error
			if (song_genre_string == "Blues")                    // other cases are obvious
				song_to_add.song_genre = Blues;
			else if (song_genre_string == "Country")
				song_to_add.song_genre = Country;
			else if (song_genre_string == "Electronic")
				song_to_add.song_genre = Electronic;
			else if (song_genre_string == "Folk")
				song_to_add.song_genre = Folk;
			else if (song_genre_string == "HipHop")
				song_to_add.song_genre = HipHop;
			else if (song_genre_string == "Jazz")
				song_to_add.song_genre = Jazz;
			else if (song_genre_string == "Latin")
				song_to_add.song_genre = Latin;
			else if (song_genre_string == "Pop")
				song_to_add.song_genre = Pop;
			else if (song_genre_string == "Rock")
				song_to_add.song_genre = Rock;         // end of if

			// free the allocated memory
			ID3_FreeString(song_title);
			ID3_FreeString(artist_name);
			ID3_FreeString(album_name);
			ID3_FreeString(year_released);
			ID3_FreeString(track_number);
			ID3_FreeString(song_genre);

			there_is_a_new_song = true;  // set to there is a new song entered
			cout << "The song is imported.";
		}

		catch (const exception &exc)
		{
			cout << "Failed to import the song!" << endl;  // if there is exception print that
			(void)exc;  // silent catch
		}

	}
}

