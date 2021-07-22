
#ifndef HR_H
#define HR_H

// Local include
#include "job.h"
#include "candidate.h"


// ----------------------------------------------
//
// ----------------------------------------------
class HR
{
    private:

        // Tabulator used for printing
        const S _sTab = "    ";

        // List of jobs in the HR system
        VJobs _vJobs;

        // List of candidates in the HR system
        VApplicants _vApplicants;

        // Read database functions
        void _process_db_line(const S& sLine);
        void _db_read_postprocessing();


    public:

        // Constructor and destructor
        HR();
        virtual ~HR();

        // Add a new job
        uint new_job(const S sPosition);

        // Add a new candidate
        uint new_candidate(const S sName);

        // Find candidate
        SPtr_Applicant find_candidate_by_id(const uint id) const;
        SPtr_Applicant find_candidate_by_name(const S& sName) const;

        // Find job
        SPtr_Job find_job_by_id(const uint id) const;
        SPtr_Job find_job_by_position_name(const S& sName) const;

        // Read database
        void read_db(const S sDBFile);
        void store_db(const S sDBFile);

        // Print info:
        void print_all() const;
        void print_jobs() const;
        void print_candidates() const;

};
typedef std::shared_ptr<HR> SPtr_HR;


#endif  // HR_H
