#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

// std library aliases: ...
namespace fs = std::filesystem; // ... filesystem
typedef fs::__cxx11::path CxxPath;          // ... short for Pathtype

// Local include
#include "hr.h"


// Database service
void HR::_process_db_line(const S& sLine)
{
    if(is_line_starting(sLine, "job"))
    {
        const auto job = std::make_shared<Job>(sLine);
        _vJobs.push_back(job);
    }
    else if(is_line_starting(sLine, "candidate"))
    {
        const auto applicant = std::make_shared<Applicant>(sLine, _vJobs);
        _vApplicants.push_back(applicant);
    }
}


void HR::_db_read_postprocessing()
{
    // Loop over all candidates and update candidates jobs info
    for(const auto candidate: _vApplicants)
    {
        for(auto const& [job, status] : candidate->get_jobs())
        {
            job->candidate(candidate, status);
        }
    }
}


// Constructor and destructor:
HR::HR(){}
HR::~HR(){}


uint HR::new_job(const S sPosition)
{
    // Get the current number of jobs. This will be id of the new job
    const uint inx = _vJobs.size();

    // Build a new job
    const auto job = std::make_shared<Job>(sPosition, inx);
    _vJobs.push_back(job);

    // Function returns global id of the created job
    return inx;
}

uint HR::new_candidate(const S sName)
{
    // Get the current number of candidates. This will be id of the new candidate
    const uint inx = _vApplicants.size();

    // Build a new candidate
    const auto candidate = std::make_shared<Applicant>(sName, inx);
    _vApplicants.push_back(candidate);

    // Function returns global id of the created candidate
    return inx;
}

SPtr_Applicant HR::find_candidate_by_id(const uint id) const
{
    for(const auto candidate: _vApplicants)
    {
        if(candidate->get_inx() == id)
        {
            return candidate;
        }
    }

    // Candidate not found!
    return nullptr;
}

SPtr_Applicant HR::find_candidate_by_name(const S& sName) const
{
    for(const auto candidate: _vApplicants)
    {
        if(candidate->get_name() == sName)
        {
            return candidate;
        }
    }

    // Candidate not found!
    return nullptr;
}

SPtr_Job HR::find_job_by_id(const uint id) const
{
    for(const auto job: _vJobs)
    {
        if(job->get_inx() == id)
        {
            return job;
        }
    }

    // Candidate not found!
    return nullptr;
}

SPtr_Job HR::find_job_by_position_name(const S& sName) const
{
    for(const auto job: _vJobs)
    {
        if(job->get_position_name() == sName)
        {
            return job;
        }
    }

    // Candidate not found!
    return nullptr;
}


//
void HR::read_db(const S sDBFile)
{
    // Check if database file exists
    const CxxPath pathDB = fs::path(sDBFile);
    const bool dbexists = fs::is_regular_file(pathDB);
    if(!dbexists)
    {
        return;
    }

    // Open the db file
    std::ifstream dbFile;
    dbFile.open(sDBFile);

    // This loop processes all the files
    S sLine;
    while(std::getline(dbFile, sLine))
    {
        _process_db_line(sLine);
    }

    dbFile.close();

    // Postprocessing of the database
    _db_read_postprocessing();

    //
    return;
}


void HR::store_db(const S sDBFile)
{
    // Open the db file
    std::ofstream dbFile;
    dbFile.open(sDBFile);

    // Write all jobs to DB file
    for(const auto job: _vJobs)
    {
        dbFile << job->build_db_line() << std::endl;
    }
    //dbFile << "Jacek" << std::endl;
    dbFile << " " << std::endl;

    // Write all candidates to DB file
    for(const auto candidate: _vApplicants)
    {
        dbFile << candidate->build_db_line() << std::endl;
    }

    dbFile.close();
}



void HR::print_all() const
{
    print_jobs();
    print_candidates();
}


void HR::print_jobs() const
{
    std::cout << std::endl;
    std::cout << "All jobs  (" << _vJobs.size() << "):" << std::endl;
    for(const auto job: _vJobs)
    {
        std::cout << job->print(_sTab) << std::endl;
    }
}


void HR::print_candidates() const
{
    std::cout << std::endl << std::endl;
    std::cout << "All applicants (" << _vApplicants.size() << "):" << std::endl;
    for(const auto applicant: _vApplicants)
    {
        std::cout << applicant->print(_sTab) << std::endl;
    }
    std::cout << std::endl;
}
