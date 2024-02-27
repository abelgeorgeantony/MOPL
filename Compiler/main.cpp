#include<iostream>

#include "headers/cmplr_fileio.h"
#include "headers/tokeniser.h"

int main()
{
    std::string* filecontent;
    filecontent = cmplr_fileio::readsrcf("test.mop");
    tknsr::tokenise(*filecontent);
    return 0;
}