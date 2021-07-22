#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <map>
#include <memory>
#include <vector>

// Local includes
#include "string_operations.h"
#include "job.h"
#include "candidate.h"
#include "hr.h"
#include "commands.h"


int main(int argc, char* argv[])
{
    // File name for the txt database
    const S sDBFile = "./db";

    // Start a hr system and read database file
    auto hr = std::make_shared<HR>();
    hr->read_db(sDBFile);

    // If there are no commands, print help and exit
    if(argc <= 1)
    {
        print_help();
        return 0;
    }

    // Switch to command service
    command_service(argc, argv, hr);

    // Before leaving, store the hr system in txt database
    hr->store_db(sDBFile);

    // All good
    return 0;
}


