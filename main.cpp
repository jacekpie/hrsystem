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


void _print_help()
{
    std::cout << "no command given!" << std::endl;
}


SPtr_Applicant find_candidate_from_command(const int argc, char* argv[], SPtr_HR hr)
{
    // Find candidate
    SPtr_Applicant candidate = nullptr;
    const S sCandidate = connect_arguments_until(argc, argv, 2, "for");
    if(sCandidate.size() == 0)
    {
        std::cout << "candidate can not be empty!" << std::endl;
        return nullptr;
    }

    // If candidate starts with @ if will be found by number:
    if(sCandidate[0] == '@')
    {
        if(sCandidate.size() < 2)
        {
            std::cout << "candidate number can not be empty!" << std::endl;
            return nullptr;
        }
        if(!is_string_a_number(sCandidate.substr(1)))
        {
            std::cout << "wrong candidate number: `" << sCandidate << "`!" << std::endl;
            return nullptr;
        }

        const uint id = read_integer(sCandidate, 1);
        candidate = hr->find_candidate_by_id(id);
    }
    else
    {
        candidate = hr->find_candidate_by_name(sCandidate);
    }

    if(candidate == nullptr)
    {
        std::cout << "can not find candidate `" << sCandidate << "`!" << std::endl;
    }
    return candidate;
}

SPtr_Job find_job_from_command(const int argc, char* argv[], SPtr_HR hr)
{
    // Find job
    SPtr_Job job = nullptr;

    // Find job name
    const int inx = find_word_among_arguments("for", argc, argv, 2) + 1;
    const S sJob = connect_arguments(argc, argv, inx);
    if(sJob.size() == 0)
    {
        std::cout << "job can not be empty!" << std::endl;
        return nullptr;
    }

    // If job starts with @ if will be found by number:
    if(sJob[0] == '@')
    {
        if(sJob.size() < 2)
        {
            std::cout << "job number can not be empty!" << std::endl;
            return nullptr;
        }
        if(!is_string_a_number(sJob.substr(1)))
        {
            std::cout << "wrong job number: `" << sJob << "`!" << std::endl;
            return nullptr;
        }

        const uint id = read_integer(sJob, 1);
        job = hr->find_job_by_id(id);
    }
    else
    {
        job = hr->find_job_by_position_name(sJob);
    }

    if(job == nullptr)
    {
        std::cout << "can not find job `" << sJob << "`!" << std::endl;
    }

    return job;
}



void _command_new_job(const int argc, char* argv[], SPtr_HR hr)
{
    if(argc < 3)
    {
        std::cout << "ERROR: no position name given!" << std::endl;
        return;
    }
    const S sJobName = connect_arguments(argc, argv, 2);
    const uint inx = hr->new_job(sJobName);
    std::cout << "new job #" << inx << "  `" << sJobName << "` was created!" << std::endl;
}


void _command_new_candidate(const int argc, char* argv[], SPtr_HR hr)
{
    if(argc < 3)
    {
        std::cout << "ERROR: no candidate name given!" << std::endl;
        return;
    }
    const S sName = connect_arguments(argc, argv, 2);
    const uint inx = hr->new_candidate(sName);
    std::cout << "new candidate #" << inx << "  `" << sName << "` was created!" << std::endl;

}

void _command_job_status(const int argc, char* argv[], SPtr_HR hr, const S& sStatus)
{
    if(argc < 5)
    {
        std::cout << "ERROR: too few arguments!" << std::endl;
        return;
    }

    // Word for must be in
    if(find_word_among_arguments("for", argc, argv, 2) < 0)
    {
        std::cout << "wrong syntax! word `for` is missing!" << std::endl;
        return;
    }

    // Find candidate
    const auto candidate = find_candidate_from_command(argc, argv, hr);
    if(candidate == nullptr)
    {
        return;
    }

    // Find job
    const auto job = find_job_from_command(argc, argv, hr);
    if(job == nullptr)
    {
        return;
    }

    // Check is job is not closed
    if(job->is_closed())
    {
        std::cout << "This job is already closed!" << std::endl;
        return;
    }

    // Ok, candidate and job were found, apply!
    job->candidate(candidate, sStatus);
    candidate->job_status(job, sStatus);

    // Inform
    std::cout << "Candidate `" << candidate->get_name() << "` ";
    std::cout << "status for job `" << job->get_position_name() << "` ";
    std::cout << "is now `" << sStatus << "`" << std::endl;
}


void _command_service(const int argc, char* argv[], SPtr_HR hr)
{
    // switch to a proper command
    const S command = argv[1];
    if(command == "show-all")
    {
        // Just print the whole database
        hr->print_all();
    }
    else if(command == "show-jobs")
    {
        // Just print the jobs
        hr->print_jobs();
    }
    else if(command == "show-candidates")
    {
        // Just print the candidates
        hr->print_candidates();
    }
    else if(command == "new-job")
    {
        // Add a new job
        _command_new_job(argc, argv, hr);
    }

    else if(command == "new-candidate")
    {
        // Build a new candidate
        _command_new_candidate(argc, argv, hr);
    }

    else if(command == "apply")
    {
        // Apply the candidate
        _command_job_status(argc, argv, hr, "application");
    }

    else if(command == "interviewed")
    {
        // Mark that a candidate was interviewed
        _command_job_status(argc, argv, hr, "interviewed");
    }

    else if(command == "reject")
    {
        // Mark that a candidate was rejected
        _command_job_status(argc, argv, hr, "reject");
    }

    else if(command == "accept")
    {
        // Mark that a candidate was accepted
        _command_job_status(argc, argv, hr, "accepted");
    }
    else
    {
        // Ups, uknown command!
        std::cout << "uknown command  `" << command << "` !" << std::endl;
    }
}

// ----------------------------------------------
//
// ----------------------------------------------
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
        _print_help();
        return 0;
    }

    // Switch to command service
    _command_service(argc, argv, hr);

    // Store the hr system in txt database
    hr->store_db(sDBFile);

    // All good
    return 0;
}


