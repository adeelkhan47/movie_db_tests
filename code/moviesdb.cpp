#include "mystring.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <sstream>  // Added to handle stringstream

using namespace std;

class MoviesDB {
public:
    static const int ALPHABETICAL = 0;
    static const int MOST_POPULAR = 1;

private:
    struct Movie {
        MyString name;
        int year;
        map<MyString, int> stars; // star name and how many times remembered
    };

    map<MyString, vector<Movie>> movieMap; // movie name to Movie details
    map<MyString, map<MyString, int>> starMovies; // star name to movies and their counts

public:
    void process_file(const string& filename) {
    cout << "Processing file: " << filename << endl;  // Debugging line

    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line, movieName;
    int year = 0;

    while (getline(file, line)) {
        cout << "Read line: " << line << endl;  // Debugging line
        if (line.empty()) continue;  // Skip empty lines

        stringstream ss(line);
        string temp;
        vector<string> words;

        // Split the line into words
        while (ss >> temp) {
            words.push_back(temp);
        }

        // Ensure the last word is a valid year
        try {
            year = stoi(words.back());  // Try converting the last word to year
            words.pop_back();  // Remove the year from the words

            // The rest of the words are the movie name
            movieName = "";
            for (const string& word : words) {
                movieName += word + " ";  // Reconstruct the movie name with spaces
            }

            // Remove trailing space
            if (!movieName.empty()) {
                movieName.pop_back();
            }

            // Process the movie name and year
            cout << "Processing movie: " << movieName << " (" << year << ")" << endl;  // Debugging line
            movieMap[movieName].push_back(Movie{MyString(movieName), year, {}});  // Store movie details

            // Now, handle the next line as a star name (skip empty lines)
            if (getline(file, line) && !line.empty()) {
                MyString star(line);
                cout << "Processing star: " << star.toString() << endl;  // Debugging line
                movieMap[movieName].back().stars[star]++;  // Add star to the movie
                starMovies[star][movieName]++;  // Track the star in the movie
            }

        } catch (const std::invalid_argument& e) {
            // If stoi fails (line does not end with a year), treat the whole line as a star name
            cout << "Invalid year, treating as star: " << line << endl;  // Debugging line
            MyString star(line);
            movieMap[movieName].back().stars[star]++;  // Add star to the last movie
            starMovies[star][movieName]++;  // Track the star in the movie
        }
    }

    file.close();
}

    void print_cast(const string& movie, const int criteria) {
    // This set will track which movies we have already printed
    static set<string> printedMovies;

    auto it = movieMap.find(movie);
    if (it == movieMap.end()) {
        cout << movie << " does not exist in the database" << endl;
        return;
    }

    vector<Movie> movies = it->second;
    map<string, set<MyString>> allStars;  // To aggregate stars for each movie

    // Process each movie and check for its cast
    for (const auto& movie : movies) {
        // If the movie has no cast, print the appropriate message and skip
        if (movie.stars.empty()) {
            if (printedMovies.find(movie.name.toString()) == printedMovies.end()) {
                // Print the movie name and message for "no cast"
                cout << movie.name.toString() << " " << movie.year << " has no cast in the database" << endl;
                cout << endl;  // Empty line after "no cast" message
                printedMovies.insert(movie.name.toString());  // Mark the movie as printed
            }
            continue;  // Skip the rest and move to the next movie
        }

        // Aggregate all stars for the movie
        for (const auto& star : movie.stars) {
            allStars[movie.name.toString()].insert(star.first);
        }

        // Track the movie, ensuring it is only printed once
        if (printedMovies.find(movie.name.toString()) == printedMovies.end()) {
            printedMovies.insert(movie.name.toString());
            cout << movie.name.toString() << " " << movie.year << endl;
        }
    }

    // Sort movies based on the name and year
    // Make sure to sort movies by year in ascending order, so they print in correct order
    for (const auto& movieStars : allStars) {
        const string& movieName = movieStars.first;
        const set<MyString>& stars = movieStars.second;

        // Sort the stars based on the specified criteria
        vector<MyString> sortedStars(stars.begin(), stars.end());
        if (criteria == ALPHABETICAL) {
            sort(sortedStars.begin(), sortedStars.end());  // Alphabetical sorting
        } else if (criteria == MOST_POPULAR) {
            // Sorting by popularity (count of mentions)
            vector<pair<MyString, int>> starCounts;
            for (const auto& star : sortedStars) {
                starCounts.push_back({star, movieMap[movieName].size()});
            }

            sort(starCounts.begin(), starCounts.end(), [](const auto& a, const auto& b) {
                return a.second == b.second ? a.first < b.first : a.second > b.second;
            });

            sortedStars.clear();
            for (const auto& sc : starCounts) {
                sortedStars.push_back(sc.first);
            }
        }

        // Print the sorted stars (cast)
        for (const auto& star : sortedStars) {
            cout << star << endl;
        }

        // Add an empty line after each movie's cast
        cout << endl;
    }
}

    void print_movies(const string& star, const int criteria) {
        auto it = starMovies.find(star);
        if (it == starMovies.end()) {
            cout << star << " does not exist in the database" << endl;
            return;
        }

        vector<pair<MyString, int>> movies(it->second.begin(), it->second.end());

        if (criteria == ALPHABETICAL) {
            sort(movies.begin(), movies.end());
        } else if (criteria == MOST_POPULAR) {
            sort(movies.begin(), movies.end(), [](const auto& a, const auto& b) {
                return a.second == b.second ? a.first < b.first : a.second > b.second;
            });
        }

        cout << star << endl;
        for (const auto& movie : movies) {
            cout << movie.first << endl;
        }

        cout << endl;
    }

    void print_costars(const string& star) {
    auto it = starMovies.find(star);
    if (it == starMovies.end()) {
        cout << star << " does not exist in the database" << endl;
        return;
    }

    map<MyString, set<int>> costars;
    for (const auto& movie : it->second) {
        // For each movie, check the cast
        for (const auto& coStar : movieMap[movie.first]) {
            if (coStar.name.toString() != star) {
                costars[coStar.name].insert(movie.second);  // Track co-stars
            }
        }
    }

    cout << star << " appeared with " << costars.size() << " different stars!" << endl;
    for (const auto& coStar : costars) {
        cout << "- Appeared with " << coStar.first << " in:" << endl;
        for (int year : coStar.second) {
            cout << "  o " << year << endl;
        }
    }
}


    vector<string> get_most_popular_movies() {
        vector<pair<string, int>> movies;
        for (const auto& entry : movieMap) {
            int popularity = accumulate(entry.second.begin(), entry.second.end(), 0,
                                         [](int acc, const Movie& m) { return acc + m.stars.size(); });
            movies.push_back({entry.first.toString(), popularity});
        }

        int maxPopularity = max_element(movies.begin(), movies.end(),
                                         [](const auto& a, const auto& b) { return a.second < b.second; })->second;

        vector<string> result;
        for (const auto& movie : movies) {
            if (movie.second == maxPopularity) result.push_back(movie.first);
        }
        sort(result.begin(), result.end());
        return result;
    }

    vector<string> get_most_popular_stars() {
        vector<pair<string, double>> stars;
        for (const auto& entry : starMovies) {
            int totalMentions = 0, totalMovies = 0;
            for (const auto& movie : entry.second) {
                totalMentions += movie.second;
                totalMovies += movieMap[movie.first].size();
            }
            stars.push_back({entry.first.toString(), static_cast<double>(totalMentions) / totalMovies});
        }

        double maxPopularity = max_element(stars.begin(), stars.end(),
                                           [](const auto& a, const auto& b) { return a.second < b.second; })->second;

        vector<string> result;
        for (const auto& star : stars) {
            if (star.second == maxPopularity) result.push_back(star.first);
        }
        sort(result.begin(), result.end());
        return result;
    }

    MoviesDB& operator+=(const MoviesDB& other) {
        for (const auto& movie : other.movieMap) {
            movieMap[movie.first].insert(movieMap[movie.first].end(), movie.second.begin(), movie.second.end());
        }

        for (const auto& star : other.starMovies) {
            for (const auto& movie : star.second) {
                starMovies[star.first][movie.first] += movie.second;
            }
        }

        return *this;
    }
};
