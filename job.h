#include <map>
#include <memory>
#include <vector>

#ifndef JOB_H
#define JOB_H

// Local include
#include "string_operations.h"

// Forward declaration
class Applicant;
typedef std::shared_ptr<Applicant> SPtr_Applicant;

// Status of an applicant for a job
enum Status {applied, interviewed, rejected, accepted};

// Map with status of applicants, used by jobs
typedef std::map<SPtr_Applicant, Status> Applicants;

// ----------------------------------------------
//
// ----------------------------------------------
class Job
{
    private:

        // Raw line from the database file
        S _sLine;

        //
        S _position;

        // global index of this job in HR system
        uint _inx;

        // map applicant -> status for this job
        Applicants _applicants;

        // employee - this string will not be empty when this job will be filled
        S _employee;

    public:

        // Constructor and Destructor
        Job(const S& sLine);
        virtual ~Job();

        // Interface:
        S get_db_line() const;
        S get_position_name() const;
        uint get_inx() const;
        const Applicants& get_applicants() const;
        S get_employee() const;
        bool is_closed() const;

        //
        S print(const S& sTab) const;
};
typedef std::shared_ptr<Job> SPtr_Job;
typedef std::vector<SPtr_Job> VJobs;

#endif // JOB_H

