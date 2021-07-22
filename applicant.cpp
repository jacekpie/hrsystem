
// Local include
#include "applicant.h"


Applicant::Applicant(const S& sLine)
{
    _sLine = sLine;
}

Applicant::~Applicant()
{

}

S Applicant::get_db_line() const
{
    return _sLine;
}


S Applicant::get_name() const
{
    return _name;
}

uint Applicant::get_inx() const
{
    return _inx;
}

const VJobs& Applicant::get_jobs() const
{
    return jobs;
}

const S Applicant::get_job() const
{
    return _job;
}


