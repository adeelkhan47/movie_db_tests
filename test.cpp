#include "/Users/AdeelKhan/Downloads/test/code/moviesdb.cpp"
#include <streambuf>
#include <sys/param.h>
#include <unistd.h>
#include <iomanip>
#include <string>

vector<string> pre2000_movies = {"A Hard Day's Night", "Batman: Mask of the Phantasm", "Blade Runner", "Crimes and Misdemeanors", "Dog Day Afternoon", "Ghostbusters", "Godzilla", "Planet of the Apes", "Star Wars", "The Guyver", "The Terminator", "Tombstone", "Good Will Hunting"};
vector<string> pre2000_stars = {"Robert De Niro", "Al Pacino", "Annie Potts", "Bill Paxton", "Cary Grant", "Gene Hackman", "Harrison Ford", "Humphrey Bogart", "Laurence Fishburne", "Mark Hamill", "Morgan Freeman", "Sigourney Weaver", "Robin Williams"};
vector<string> post2000_movies = {"Blade Runner 2049", "Cars", "Fantastic Beasts and Where to Find Them", "Ghostbusters", "Godzilla", "Howl's Moving Castle", "Inception", "Interstellar", "Man of Steel", "The Dark Knight", "Slumdog Millionaire", "The Prestige", "Shutter Island", "Whiplash", "La La Land", "The Fast and the Furious: Tokyo Drift", "Memento", "The Imitation Game", "The Matrix Reloaded", "The Wolverine", "500 Days of Summer", "Drive", "The Devil Wears Prada"};
vector<string> post2000_stars = {"Adam Sandler", "Al Pacino", "Andrew Garfield", "Anna Kendrick", "Anne Hathaway", "Ben Affleck", "Ben Stiller", "Brad Pitt", "Christian Bale", "Dakota Fanning", "Dakota Johnson", "Daniel Radcliffe", "Dev Patel", "Elizabeth Olsen", "Emily Blunt", "Emma Stone", "Emma Watson", "Harrison Ford", "Ryan Gosling", "Helena Bonham Carter", "Henry Cavill", "Hugh Jackman", "Jack Black", "Olivia Colman", "Joseph Gordon-Levitt", "Michael Fassbender", "David Tennant", "Robert De Niro", "Michael Caine", "Matt Damon"};
vector<string> bollywood_movies = {"Dangal", "3 Idiots", "Zindagi Na Milegi Dobara", "Dilwale Dulhania Le Jayenge", "Munna Bhai M.B.B.S.", "Yeh Jawaani Hai Deewani", "Kabhi Khushi Kabhie Gham...", "Kuch Kuch Hota Hai", "Jab We Met", "Kal Ho Naa Ho", "Om Shanti Om", "Dil To Pagal Hai", "Hum Aapke Hain Koun..!", "Hum Saath-Saath Hain", "CS200 The Movie", "Mohabbatein", "Kabhi Alvida Naa Kehna", "Partner", "Taare Zameen Par", "Ae Dil Hai Mushkil", "Rockstar", "Rab Ne Bana Di Jodi", "Band Baaja Baaraat", "Golmaal 3", "Karan Arjun", "Baazigar", "Chup Chup Ke", "Tees Maar Khan", "Hera Pheri", "Bajirao Mastani", "Swades: We, the People", "Chak De! India", "Ghajini", "Dhoom:3", "Housefull", "Tees Maar Khan", "Baghban"};
vector<string> bollywood_stars = {"Aamir Khan", "Irrfan Khan", "Fawad Khan", "Shah Rukh Khan", "Aishwarya Rai Bachchan", "Ajay Devgn", "Akshay Kumar", "Alia Bhatt", "Amitabh Bachchan", "Anupam Kher", "Shah Rukh Khan", "Anushka Sharma", "Deepika Padukone", "Hrithik Roshan", "Namwar Ahmad Rauf", "Janhvi Kapoor", "John Abraham", "Katrina Kaif", "Kareena Kapoor", "Mithun Chakraborty", "Nana Patekar", "Nutan Sinha", "Paresh Rawal", "Priyanka Chopra Jonas", "Rajesh Khanna", "Rajkummar Rao", "Ranbir Kapoor", "Ranveer Singh", "Rishi Kapoor", "Saif Ali Khan", "Salman Khan", "Sanjay Dutt", "Shahid Kapoor", "Shraddha Kapoor", "Suniel Shetty", "Varun Dhawan", "Vicky Kaushal", "Rani Mukerji"};
vector<string> operator_movies = {"Blade Runner", "Blade Runner 2049", "Ghostbusters", "Godzilla", "Planet of the Apes", "Star Wars", "The Terminator", "Beyond the Edge", "Charlie", "Death Race", "Death Race 2050", "Extinction", "Fantastic Four", "Final Destination", "Frozen", "Gifted", "Kill Bill: Vol. 1"};
vector<string> operator_stars = {"Robert De Niro", "Al Pacino", "Annie Potts", "Bill Paxton", "Adam Sandler", "Cary Grant", "Gene Hackman", "Harrison Ford", "Humphrey Bogart", "Laurence Fishburne", "Mark Hamill", "Morgan Freeman", "Sigourney Weaver", "Robin Williams", "Brad Pitt", "Ben Affleck", "Matt Damon"};
vector<string> complete_movies = {"Animal", "Angoor", "Agneepath", "Chef",  "Dangal", "3 Idiots", "Zindagi Na Milegi Dobara", "Dilwale Dulhania Le Jayenge", "Munna Bhai M.B.B.S.", "Yeh Jawaani Hai Deewani", "Kabhi Khushi Kabhie Gham...", "Kuch Kuch Hota Hai", "Jab We Met", "Kal Ho Naa Ho", "Om Shanti Om", "Dil To Pagal Hai", "Don", "Ghost Stories", "Genius", "Hero"};
vector<string> complete_stars = {"Aamir Khan", "Irrfan Khan", "Fawad Khan", "Shah Rukh Khan", "Ajay Devgn", "Anne Hathaway", "Ben Affleck", "Ben Stiller", "Brad Pitt", "Christian Bale", "Dakota Fanning", "Dakota Johnson", "Daniel Radcliffe", "Dev Patel", "Elizabeth Olsen", "Emily Blunt", "Emma Stone", "Emma Watson", "Harrison Ford", "Ryan Gosling", "Helena Bonham Carter", "Henry Cavill", "Hugh Jackman", "Jack Black", "Katrina Kaif", "Kareena Kapoor", "Priyanka Chopra Jonas", "Sanjay Dutt", "Amitabh Bachchan"};

vector<string> tests = {"pre2000", "post2000", "bollywood", "operator", "complete"};
vector<vector<string>> query_vecs = {pre2000_movies, post2000_movies, bollywood_movies, operator_movies, complete_movies, pre2000_stars, post2000_stars, bollywood_stars, operator_stars, complete_stars};

bool compare_files(const string test_output){
    ifstream your_stream("my_output.txt");
    ifstream test_stream(test_output);

    if(!your_stream.is_open()){
        cerr<<"Error: Could not open your output file: my_output.txt"<<endl;
        return false;
    }

    if(!test_stream.is_open()){
        cerr<<"Error: Could not open test output file: "<<test_output<<endl;
        return false;
    }

    string your_line, test_line;
    int line_number = 0;

    while(getline(test_stream, test_line)){
        getline(your_stream, your_line);
        line_number++;

        if(your_line != test_line){
            cerr<<endl<<"Mismatch at line: "<<line_number<<endl;
            cerr<<"Your file output line|"<<your_line<<"|"<<endl;
            cerr<<"Test file output line|"<<test_line<<"|"<<endl;
            return false;
        }
    }

    return true;
}

int interface_main(){
    const char* parts[] = {"Exit", "Test 1: Pre-2000 Hollywood", "Test 2: Post-2000 Hollywood", "Test 3: Bollywood", "Test 4: Operator Overload", "Test 5: Complete Test"};
    const double marks[] = {0, 28, 28, 28, 28, 28};
    int input;

    cout<<string(70, '-')<<endl;
    cout<<left<<setw(15)<<"Index"<<setw(40)<<"Test"<<setw(15)<<"Marks"<<endl;
    cout<<string(70, '-')<<endl;

    for (size_t i = 0; i < sizeof(parts) / sizeof(parts[0]); ++i) 
        cout<<left<<setw(15)<<i<<setw(40)<<parts[i]<<setw(15)<<marks[i]<<endl;
    cout<<string(70, '-')<<endl;

    cout<<"Enter the index of the test that you want to run: ";
    cin >> input;

    return input;
}

void test_print_criteria(MoviesDB& db, vector<string> data, int criteria, bool print_movie){
    ofstream file("my_output.txt", ios::out);
    streambuf* oldCoutBuf = cout.rdbuf();
    cout.rdbuf(file.rdbuf());

    if(criteria == db.ALPHABETICAL){
        for(int i = 0; i < data.size(); i++){
            if(print_movie){
                db.print_movies(data[i], db.ALPHABETICAL);
            }
            else{
                db.print_cast(data[i], db.ALPHABETICAL);
            }
        }
    }
    else{
        for(int i = 0; i < data.size(); i++){
            if(print_movie){
                db.print_movies(data[i], db.MOST_POPULAR);
            }
            else{
                db.print_cast(data[i], db.MOST_POPULAR);
            }
        }   
    }

    cout.rdbuf(oldCoutBuf);
    file.close();
}

void test_print_costar(MoviesDB& db, vector<string> data){
    ofstream file("my_output.txt", ios::out);
    streambuf* oldCoutBuf = cout.rdbuf();
    cout.rdbuf(file.rdbuf());

    for(int i = 0; i < data.size(); i++){
        db.print_costars(data[i]);
    }

    cout.rdbuf(oldCoutBuf);
    file.close();
}

void test_process(MoviesDB& db, int test){
    ifstream file(tests[test] + ".txt");
    string filename;

    while(getline(file, filename)){
        db.process_file(filename);
    }

    file.close();
}

void test_most_popular(MoviesDB& db, bool movies){
    ofstream file("my_output.txt", ios::out);
    streambuf* oldCoutBuf = cout.rdbuf();
    cout.rdbuf(file.rdbuf());

    vector<string> data;

    if(movies){
        data = db.get_most_popular_movies();
    }
    else{
        data = db.get_most_popular_stars();
    }

    for(int i = 0; i < data.size(); i++){
        cout<<data[i]<<endl;
    }

    cout.rdbuf(oldCoutBuf);
    file.close();
}

void run_tests(MoviesDB& db, int test){
    int marks = 0;
    int pass = 0;

    cout<<"\033[35mTesting Print Movies of Star (Alphabetical):\033[0m ";
    test_print_criteria(db, query_vecs[test+5], db.ALPHABETICAL, true);
    
    if(compare_files("test_output/test_" + tests[test] + "/print_movies_alphabetical.txt")){
        marks += 4;
        pass += 4;
    }

    cout<<pass<<"/"<<4<<endl<<endl;
    
    cout<<"\033[35mTesting Print Movies of Star (Popularity):\033[0m ";
    test_print_criteria(db, query_vecs[test+5], db.MOST_POPULAR, true);
    
    pass = 0;
    if(compare_files("test_output/test_" + tests[test] + "/print_movies_popularity.txt")){
        marks += 4;
        pass += 4;
    }

    cout<<pass<<"/"<<4<<endl<<endl;

    cout<<"\033[35mTesting Print Cast of Movie (Alphabetical):\033[0m ";
    test_print_criteria(db, query_vecs[test], db.ALPHABETICAL, false);
    
    pass = 0;
    if(compare_files("test_output/test_" + tests[test] + "/print_cast_alphabetical.txt")){
        marks += 4;
        pass += 4;
    }

    cout<<pass<<"/"<<4<<endl<<endl;

    cout<<"\033[35mTesting Print Cast of Movie (Popularity):\033[0m ";
    test_print_criteria(db, query_vecs[test], db.MOST_POPULAR, false);
    
    pass = 0;
    if(compare_files("test_output/test_" + tests[test] + "/print_cast_popularity.txt")){
        marks += 4;
        pass += 4;
    }

    cout<<pass<<"/"<<4<<endl<<endl;

    cout<<"\033[35mTesting Print Costars:\033[0m ";
    test_print_costar(db, query_vecs[test+5]);
    
    pass = 0;
    if(compare_files("test_output/test_" + tests[test] + "/print_costars.txt")){
        marks += 4;
        pass += 4;
    }

    cout<<pass<<"/"<<4<<endl<<endl;

    cout<<"\033[35mTesting Most Popular Movies:\033[0m ";
    test_most_popular(db, true);
    
    pass = 0;
    if(compare_files("test_output/test_" + tests[test] + "/most_popular_movies.txt")){
        marks += 4;
        pass += 4;
    }

    cout<<pass<<"/"<<4<<endl<<endl;

    cout<<"\033[35mTesting Most Popular Stars:\033[0m ";
    test_most_popular(db, false);

    pass = 0;
    if(compare_files("test_output/test_" + tests[test] + "/most_popular_stars.txt")){
        marks += 4;
        pass += 4;
    }

    cout<<pass<<"/"<<4<<endl<<endl;

    cout<<"\033[1m\033[35mTotal:\033[0m "<<marks<<"/"<<28<<endl<<endl;
}

void initialize_basic(int test){
    cout<<"\033[1m\033[36mRunning test for "<<tests[test]<<" movie database\033[0m"<<endl<<endl;
    MoviesDB db;

    cout<<"\033[35mProcessing data files:\033[0m ";
    test_process(db, test);
    cout<<"Files process complete"<<endl<<endl;

    run_tests(db, test);
}

void test_operator(){
    cout<<"\033[1m\033[36mRunning test for operator overloading\033[0m"<<endl<<endl;

    MoviesDB pre2000_db;
    MoviesDB post2000_db;

    test_process(pre2000_db, 0);
    test_process(post2000_db, 1);

    MoviesDB db;
    db += pre2000_db;
    db += post2000_db;

    run_tests(db, 3);
}

void test_complete(){
    cout<<"\033[1m\033[36mRunning complete comprehensive test\033[0m"<<endl<<endl;
    MoviesDB db;
    MoviesDB post2000_db;
    MoviesDB bollywood_db;

    test_process(db, 0);
    test_process(post2000_db, 1);
    test_process(bollywood_db, 2);

    db += post2000_db += bollywood_db;

    run_tests(db, 4);
}

void start_main(){
    chdir("test");
    int flag = 1;
    int index;

    while (flag)
    {
        index = interface_main();
        switch (index) 
        {
        case 0:
            cout<<"Exiting...\n";
            flag = 0;
            break;
        
        case 1:
            cout<<endl;
            initialize_basic(0);
            break;
          
        case 2:
            cout<<endl;
            initialize_basic(1);
            break;

        case 3:
            cout<<endl;
            initialize_basic(2);
            break;

        case 4:
            cout<<endl;
            test_operator();
            break;
        
        case 5:
            cout<<endl;
            test_complete();
            break;

        default:
            cout<<"No such test exists\n";
            break;
        }
    }
}

int main(){
    start_main();
    return 0;
}