/*
 * This file contains implementation of functions which handle user commands.
 */

#include <iostream>

// Local includes
#include "string_operations.h"
#include "job.h"
#include "candidate.h"
#include "hr.h"


void print_help()
{
//
// Print helps to std out.
//
    std::cout << "Usage: hrsystem [command] {command options} " << std::endl;
    std::cout << "Commands: " << std::endl << std::endl;
    std::cout << "To print status of the database" << std::endl;
    std::cout << "    show-all         Print status of all the jobs and all the candidates in HR database";
    std::cout << std::endl;
    std::cout << "    show-jobs        Print status of all the jobs in HR database" << std::endl;
    std::cout << "    show-candidates  Print status of all the candidates in HR database" << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "To add job or candidate to the database:" << std::endl;
    std::cout << "    new-job [position name]     Create new job with a given position name" << std::endl;
    std::cout << "        example:  $./hrsystem  new-job  software developer" << std::endl;
    std::cout << "        example:  $./hrsystem  new-job  truck driver" << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "    new-candidate [ name]      Create new candidate with a given name" << std::endl;
    std::cout << "        example:  $./hrsystem  new-candidate  Joe Doe" << std::endl;
    std::cout << "        example:  $./hrsystem  new-candidate  Anna Doyle" << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "To change status of a candidate for a certain job:" << std::endl;
    std::cout << "    apply|interviewed|reject|accept   [name|@id] for [job|@id]  ";
    std::cout << "Change status of candidate for a job" << std::endl;
    std::cout << std::endl;
    std::cout << "                               Both candidate and job may be given by their ID number, ";
    std::cout << std::endl;
    std::cout << "                               start with @ to use ID instead of name / position name ";
    std::cout << std::endl << std::endl;
    std::cout << "        example:  $./hrsystem  apply  Joe Doe for Software developer" << std::endl;
    std::cout << "        example:  $./hrsystem  interviewed  Ann Doyle for @0" << std::endl;
    std::cout << "        example:  $./hrsystem  reject  Jimmy Page for @1" << std::endl;
    std::cout << "        example:  $./hrsystem  accept  Jackie Haskell for @0" << std::endl;
    std::cout << std::endl;
}


SPtr_Candidate find_candidate_from_command(const int argc, char* argv[], SPtr_HR hr)
{
//
// This function finds pointer to a candidate from HR system, based on his name / id.
//
// It is used by commands   apply|interviewed|reject|accept.
//
// Candidate in these commands is placed before `for` keyword, e.g.:
//
//  $./hrsystem  apply  Joe Doe for Software developer
//  $./hrsystem  apply  @0 for Software developer        <-- find candidate with gloval id `0`
//
// If candidate `Joe Doe` exists in the HR system it will return a pointer to Joe Doe from the database.
// Otherwise, function returns nullptr.
//

    // Find candidate
    SPtr_Candidate candidate = nullptr;
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
//
// This function finds pointer to a job from HR system, based on job name/ id given in user command.
//
// It is used by commands   apply|interviewed|reject|accept.
//
// Job in these commands job is placed after `for` keyword, e.g.:
//
//  $./hrsystem  apply  Joe Doe for Software developer
//  $./hrsystem  apply  Joe Doe for @0         <-- find job with global id `0`
//
// If candidate `Software developer` exists in the HR system it will return a pointer to `Software developer`
// job from the database.
// Otherwise, function returns nullptr.
//

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



void command_new_job(const int argc, char* argv[], SPtr_HR hr)
{
//
// Service for `new-job` command
//
    if(argc < 3)
    {
        std::cout << "ERROR: no position name given!" << std::endl;
        return;
    }

    // Connect arguments, so that `new-job Software Developer` will have position name `Software-Developer``
    const S sJobName = connect_arguments(argc, argv, 2);

    // Creates new job, gets its id and prints info that the job was created
    const uint inx = hr->new_job(sJobName);
    std::cout << "new job #" << inx << "  `" << sJobName << "` was created!" << std::endl;
}


void command_new_candidate(const int argc, char* argv[], SPtr_HR hr)
{
//
// Service for `new-candidate` command
//
    if(argc < 3)
    {
        std::cout << "ERROR: no candidate name given!" << std::endl;
        return;
    }

    // Connect arguments, so that `new-candidate Joe Doe` will have position name `Joe Doer``
    const S sName = connect_arguments(argc, argv, 2);

    // Creates new andidate, gets its id and prints info that the andidate was created
    const uint inx = hr->new_candidate(sName);
    std::cout << "new candidate #" << inx << "  `" << sName << "` was created!" << std::endl;

}

void command_job_status(const int argc, char* argv[], SPtr_HR hr, const S& sStatus)
{
//
// Service for apply|interviewed|reject|accept. commands
//

    if(argc < 5)
    {
        std::cout << "ERROR: too few arguments!" << std::endl;
        return;
    }

    // Word `for` must be in command
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

    // Inform user - print to console
    std::cout << "Candidate `" << candidate->get_name() << "` ";
    std::cout << "status for job `" << job->get_position_name() << "` ";
    std::cout << "is now `" << sStatus << "`" << std::endl;
}


void command_service(const int argc, char* argv[], SPtr_HR hr)
{
//
// Main command service entry point.
//

    // switch to a proper command
    const S command = argv[1];
    if(command == "help")
    {
        print_help();
    }

    else if(command == "show-all")
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
        command_new_job(argc, argv, hr);
    }

    else if(command == "new-candidate")
    {
        // Build a new candidate
        command_new_candidate(argc, argv, hr);
    }

    else if(command == "apply")
    {
        // Apply the candidate
        command_job_status(argc, argv, hr, "application");
    }

    else if(command == "interviewed")
    {
        // Mark that a candidate was interviewed
        command_job_status(argc, argv, hr, "interviewed");
    }

    else if(command == "reject")
    {
        // Mark that a candidate was rejected
        command_job_status(argc, argv, hr, "reject");
    }

    else if(command == "accept")
    {
        // Mark that a candidate was accepted
        command_job_status(argc, argv, hr, "accepted");
    }
    else
    {
        // Ups, uknown command!
        std::cout << "uknown command  `" << command << "` !" << std::endl;
    }
}