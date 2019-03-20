#pragma once

// typedefs for music's genre
typedef enum genre
{
	Unknown, Blues, Country, Electronic, Folk, HipHop, Jazz, Latin, Pop, Rock
} _genre;

// structure for every song
struct Song
{	char song_title [64];
	char artist_name [32];
	char album_name [64];
	int track_number;
	int year_released;
	genre song_genre;
};