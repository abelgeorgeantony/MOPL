#include <iostream>
#include <fstream>

#include "headers/cmplr_fileio.h"


std::string filecontent;


std::string* cmplr_fileio::readsrcf(std::string filename)
{
    std::ifstream file;
    std::string line;
    file.open(filename);
    while (getline(file, line))
    {
        filecontent = filecontent + line;
    }
    file.close();

    return &filecontent;
}