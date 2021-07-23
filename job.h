/*
 * This file contains definition of a class with job.
 */

#include <map>
#include <memory>
#include <vector>

#ifndef JOB_H
#define JOB_H

// Local include
#include "string_operations.h"

// Forward declaration
class Candidate;
typedef std::shared_ptr<Candidate> SPtr_Candidate;

// Map with status of candidates
typedef std::map<SPtr_Candidate, S> Candidates;

class Job
{
    private:

        // position name
        S _position;

        // global index of this job in HR system
        uint _inx;

        // Map with status of candidates
        Candidates _candidates;

        // employee - this string will not be empty when this job will be filled
        S _employee;

    public:

        // Constructor and Destructor
        Job(const S& sLine);                    // this is used when a job is read from a database
        Job(const S& sName, const uint _inx);   // this is used when a job is created manually
        virtual ~Job();

        // Data interface:
        S get_position_name() const;
        uint get_inx() const;
        const Candidates& get_candidates() const;
        S get_employee() const;
        bool is_closed() const;

        // Add / change status of a candidate for this job
        void candidate(const SPtr_Candidate candidate, const S& status);

        // Build a string with info about this job
        S print(const S& sTab) const;

        // Build a string for database
        S build_db_line() const;

};
typedef std::shared_ptr<Job> SPtr_Job;
typedef std::vector<SPtr_Job> VJobs;

#endif // JOB_H

