#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <cstring>
#include <string>

using namespace std;

void usage()
{
    cerr << "Usage: sample <infile> <outfile> <percentage>" << endl
        << "  where <percentage> is a number between 0 and 1." << endl;
    exit(1);
}

int main(int argc, char *argv[])
{

    if (argc < 4 || strcmp("-h",argv[1]) == 0)
    {
        usage();
    }
    ifstream myfile;
    myfile.open(argv[1]);
    if (!myfile.is_open())
    {
        cerr << "Error opening file '" << argv[2] << "' for reading." << endl;
        usage();
    }
    ofstream out(argv[2]);
    if (!out.is_open())
    {
        cerr << "Error opening file '" << argv[2] << "' for writing." << endl;
        usage();
    }
    stringstream numConverter;
    numConverter << argv[3];
    double number;
    numConverter >> number;
    if (!numConverter)
    {
        cerr << "Error converting '" << argv[3] << "' into a number." << endl;
        usage();
    }
    if (number < 0.0 || number > 1.0)
    {
        cerr << "Third argument must be a number between 0 and 1." << endl;
        usage();
    }
    std::mt19937_64 generator(time(NULL));
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    string line;
    while (getline(myfile,line))
    {
        double dice = distribution(generator);
        if (dice < number)
        {
            out << line << endl;
        }
    }
    return 0;
}
