#include <map>
#include <memory>
#include <vector>

#ifndef APP_H
#define APP_H

// Local include
#include "string_operations.h"
#include "job.h"

// ----------------------------------------------
//
// ----------------------------------------------
class Applicant
{
    private:

        // Raw line from the database file
        S _sLine;

        //
        S _name;

        // global index
        uint _inx;

        // map jobs -> status for this applicant
        VJobs jobs;

        // job - this string will not be empty when this applicant will get a job
        S _job;

    public:

        // Constructor and destructor
        Applicant(const S& sLine);
        virtual ~Applicant();

        // Interface:
        S get_db_line() const;
        S get_name() const;
        uint get_inx() const;
        const VJobs& get_jobs() const;
        const S get_job() const;
};
typedef std::shared_ptr<Applicant> SPtr_Applicant;
typedef std::vector<SPtr_Applicant> VApplicants;

#endif // APP_H
