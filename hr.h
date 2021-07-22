
#ifndef HR_H
#define HR_H

// Local include
#include "job.h"
#include "applicant.h"


// ----------------------------------------------
//
// ----------------------------------------------
class HR
{
    private:

        //
        VJobs _vJobs;
        VApplicants _vApplicants;

    public:

        // Constructor and destructor
        HR();
        virtual ~HR();

        // Add job or applicant read from database
        void add_job_from_db(const S& sLine);
        void add_applicant_from_db(const S& sLine);

        // Database post processing
        void db_read_postprocessing();

        // Print all the status
        void print_all() const;

};
typedef std::shared_ptr<HR> SPtr_HR;


#endif  // HR_H
