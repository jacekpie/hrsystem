#include <map>
#include <memory>
#include <vector>

#ifndef APP_H
#define APP_H

// Local include
#include "string_operations.h"
#include "job.h"

// Map with status of jobs
typedef std::map<SPtr_Job, S> Jobs;

// ----------------------------------------------
//
// ----------------------------------------------
class Applicant
{
    private:

        // candidate's full name
        S _name;

        // global index
        uint _inx;

        // Map with status of jobs
        Jobs _jobs;

        // job - this string will not be empty when this applicant will get a job
        SPtr_Job _job;

        // Find job by id from a given list of jobs
        static SPtr_Job _find_job_by_id(const VJobs& vJobs, const uint job_id);

    public:

        // Constructor and destructor
        Applicant(const S& sLine, const VJobs& jobs); // this is used when a candidate is read from a database
        Applicant(const S& sLine, const uint inx);    // this is used when a candidate is created manually
        virtual ~Applicant();

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
typedef std::shared_ptr<Applicant> SPtr_Applicant;
typedef std::vector<SPtr_Applicant> VApplicants;

#endif // APP_H
