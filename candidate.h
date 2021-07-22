#include <map>
#include <memory>
#include <vector>

#ifndef CANDIDATE_H
#define CANDIDATE_H

// Local include
#include "string_operations.h"
#include "job.h"

// Map with status of jobs
typedef std::map<SPtr_Job, S> Jobs;


class Candidate
{
    // ----------------------------------------------
    // This class defines job candidate
    // ----------------------------------------------

    private:

        // candidate's full name
        S _name;

        // global index
        uint _inx;

        // Map with status of jobs
        Jobs _jobs;

        // job - this  will not be nullptr when this candidate will get a job
        SPtr_Job _job;

        // Find job by id from a given list of jobs
        static SPtr_Job _find_job_by_id(const VJobs& vJobs, const uint job_id);

    public:

        // Constructor and destructor
        Candidate(const S& sLine, const VJobs& jobs); // this is used when a candidate is read from a database
        Candidate(const S& sLine, const uint inx);    // this is used when a candidate is created manually
        virtual ~Candidate();

        // Interface:
        S get_db_line() const;
        S get_name() const;
        uint get_inx() const;
        const Jobs& get_jobs() const;
        const S get_job_name() const;
        const bool is_our_employee() const;

        // update job status
        void job_status(SPtr_Job job, const S& sStatus);

        //
        S print(const S& sTab) const;

        // Build a string for database
        S build_db_line() const;
};
typedef std::shared_ptr<Candidate> SPtr_Candidate;
typedef std::vector<SPtr_Candidate> VCandidates;

#endif // CANDIDATE_H
