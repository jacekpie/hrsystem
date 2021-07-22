#include <sstream>
#include <iostream>

// Local include
#include "hr.h"

HR::HR()
{

}

HR::~HR()
{

}


void HR::add_job_from_db(const S& sLine)
{
    //
    const auto job = std::make_shared<Job>(sLine);
    _vJobs.push_back(job);
}


void HR::add_applicant_from_db(const S& sLine)
{
    //
    const auto applicant = std::make_shared<Applicant>(sLine);
    _vApplicants.push_back(applicant);
}


void HR::db_read_postprocessing()
{
    // Jobs
    std::cout << std::endl;
    std::cout << "jobs:" << std::endl;
    for(const auto job: _vJobs)
    {
        std::cout << job->get_db_line() << std::endl;
    }
    std::cout << std::endl;

    // Applicatnts
    std::cout << std::endl;
    std::cout << "applicants:" << std::endl;
    for(const auto applicant: _vApplicants)
    {
        std::cout << applicant->get_db_line() << std::endl;
    }
    std::cout << std::endl;
}


void HR::print_all() const
{
    const S sTab = "    ";

    // Print jobs
    std::cout << std::endl;
    std::cout << "jobs:" << std::endl;
    for(const auto job: _vJobs)
    {
        std::cout << job->print(sTab);
    }
    std::cout << std::endl;
}

