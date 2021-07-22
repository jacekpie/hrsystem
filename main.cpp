#include <filesystem>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <map>
#include <memory>
#include <vector>

// Local includes
#include "string_operations.h"
#include "job.h"
#include "applicant.h"
#include "hr.h"

// std library aliases: ...
namespace fs = std::filesystem; // ... filesystem
typedef fs::__cxx11::path CxxPath;          // ... short for Pathtype

/*
Design a simple system that allows HR to track the state of jobs,
applications and candidates.

Candiates can register themselves and apply for a job
All applications go through state: applied, interviewed, rejected, accepted.
When an application is accepted the job can no longer be applied to.

--new-job  SoftwareDeveloper
SoftwareDeveloper created

--show-jobs

--show-aplicants Software Developer
--show-candidate Jacek Pierzchlewski

--applcation Jacek Pierzchlewski,
--interview Jacek Pierzchlewski
--reject Jacek Pierzchlewski

--accept Software Developer,Jacek Pierzchlewski
*/

/*
job#0=SoftwareDeveloper,
job#1=GraphicDesigner,
job#2=SeniorSoftwareDeveloper,

candidate#0=JacekPierzchlewski,job#0?application,job#1?interview,job#2?reject
candidate#1=JoeDoe,job#0?pplication,job#1?interview,job#2?reject,job#3?accepted
*/


// ----------------------------------------------
//
// ----------------------------------------------
void _process_db_line(SPtr_HR hr, const S& sLine)
{
    if(is_line_starting(sLine, "job"))
    {
        std::cout << "JOB:  `" << sLine << "`" << std::endl;
        hr->add_job_from_db(sLine);
    }
    else if(is_line_starting(sLine, "candidate"))
    {
        std::cout << "CANDIDATE:  `" << sLine << "`" << std::endl;
        hr->add_applicant_from_db(sLine);
    }
}


SPtr_HR read_database(const S sDBFile)
{
    // Start a hr system
    auto hr = std::make_shared<HR>();

    // Check if database file exists
    const CxxPath pathDB = fs::path(sDBFile);
    const bool dbexists = fs::is_regular_file(pathDB);
    if(!dbexists)
    {
        return hr;
    }

    // Open the branch file
    std::ifstream branchFile;
    branchFile.open(sDBFile);

    // Temporary line
    S sLine;

    // This loop processes all the files
    while(std::getline(branchFile, sLine))
    {
        _process_db_line(hr, sLine);
    }

    // Postprocessing of the database
    hr->db_read_postprocessing();

    //
    return hr;
}


int main(int argc, char* argv[])
{
    // Read HR
    const auto hr = read_database("./db");

    // Print database
    hr->print_all();

    //
    return 0;
}


