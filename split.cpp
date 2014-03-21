#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

void usage()
{
    cerr << "Usage: split <num-times> <lines-at-a-time> <in-file>" << endl;
    exit(1);
}

unsigned long long numLines(std::string filename)
{
    ifstream myfile(filename.c_str());
    if (!myfile.is_open())
    {
        cerr << "Error opening file '" << filename.c_str() << "' for reading." << endl;
        usage();
    }
    string line;
    unsigned long long lineNumber = 0ULL;
    while (getline(myfile,line))
    {
        lineNumber++;
    }
    myfile.close();
    return lineNumber;
}

int main(int argc, char *argv[])
{

    if (argc < 5 || strcmp("-h",argv[1]) == 0)
    {
        usage();
    }
    stringstream numConverter;
    numConverter << argv[1];
    int numTimes;
    numConverter >> numTimes;
    stringstream atATimeConverter;
    int atATime;
    atATimeConverter << argv[2];
    atATimeConverter >> atATime;
    if (!numConverter)
    {
        cerr << "Error converting '" << argv[1] << "' into a number." << endl;
        usage();
    }
    if (!atATimeConverter)
    {
        cerr << "Error converting '" << argv[2] << "' into a number." << endl;
        usage();
    }
    unsigned long long lineNumber = numLines(argv[3]);
    unsigned long long part = (((lineNumber / numTimes) * atATime) * atATime);
    unsigned long long whole = lineNumber;
    cout << "Line numbers: " << lineNumber << endl;;
    cout << "part sizes: " << part << endl;

    ifstream myfile(argv[3]);
    if (!myfile.is_open())
    {
        cerr << "Error opening file '" << argv[3] << "' for reading. " << endl;
        usage();
    }

    for (int i = 1; i <= numTimes; i++)
    {
        stringstream filename;
        filename << argv[4] << ".split" << i;
        ofstream out(filename.str().c_str());
        if (!out.is_open())
        {
            cerr << "Error opening file '" << filename.str().c_str() << "' for writing." << endl;
            usage();
        }

        string line;
        unsigned long long thisPart = i != numTimes ? part : whole;
        for (unsigned long long j = 0ull; j < thisPart && getline(myfile,line); j++)
        {
            out << line << endl;
        }
        whole -= part;
    }
    myfile.close();
    return 0;
}
