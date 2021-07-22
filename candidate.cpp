#include <sstream>
#include <iostream>

// Local include
#include "candidate.h"

SPtr_Job Applicant::_find_job_by_id(const VJobs& vJobs, const uint job_id)
{
    for(const auto job: vJobs)
    {
        if(job->get_inx() == job_id)
        {
            return job;
        }
    }

    // Job was not found
    return nullptr;
}


Applicant::Applicant(const S& sLine, const VJobs& vJobs)
{
    // Get the job global index
    _inx = read_integer(sLine, 10);

    // Get the applicant name
    _name = read_string(sLine, find_equal_sign(sLine)+1);

    // Process all the applicants jobs
    uint inx = find_comma(sLine) + 1;
    const auto vJobsRaw = read_comma_separated(sLine, inx);
    for(const S& sJobRaw: vJobsRaw)
    {
        // Find job id - its global index and corresponding job.
        // If job can not be found, do nothing
        const uint job_id = read_integer(sJobRaw, 4);
        const auto job = _find_job_by_id(vJobs, job_id);
        if(job == nullptr)
        {
            continue;
        }

        // Find job status
        _jobs[job] = read_string(sJobRaw, find_question_mark(sJobRaw) + 1);
    }

    /// Loop through jobs and find accepted - this is the current job of this candidate
    _job = nullptr;
    for(auto const& [job, status] : _jobs)
    {
        if(status == "accepted")
        {
            _job = job;
            break;
        }
    }

}

Applicant::Applicant(const S& sName, const uint inx)
{
    // this is used when a candidate is created manually

    // Store its id
    _inx = inx;

    // Store its name
    _name = sName;

    // No job is assigned to this candidate, yet
    _job = nullptr;
}

Applicant::~Applicant()
{

}


S Applicant::get_name() const
{
    return _name;
}

uint Applicant::get_inx() const
{
    return _inx;
}

const Jobs& Applicant::get_jobs() const
{
    return _jobs;
}

const S Applicant::get_job_name() const
{
    return _job->get_position_name();
}

const bool Applicant::is_our_employee() const
{
    return (_job != nullptr);
}

void Applicant::job_status(SPtr_Job job, const S& sStatus)
{
    _jobs[job] = sStatus;

    // If this candidate was accepted, mark that this is candidate's job
    if(sStatus == "accepted")
    {
        _job = job;
    }
}


S Applicant::print(const S& sTab) const
{
    std::ostringstream out;

    // Print bacis applicant data
    out << "applicant #" << get_inx();
    out << "  `" << get_name() << "`" << std::endl;

    // Is this applicant our employee??
    if(is_our_employee())
    {
        out << sTab << "applicant is our employee, position: `" << get_job_name() << "`" << std::endl;
    }
    else
    {
        out << sTab << "applicant is not our employee" << std::endl;
    }

    // Print all the jobs applicant applied
    for(auto const& [job, status] : _jobs)
    {
        out << sTab << "applied for job: `" << job->get_position_name() << "`   ";
        out << "status: `" << status << "`" << std::endl;
    }
    return out.str();
}


S Applicant::build_db_line() const
{
    std::ostringstream out;
    out << "candidate#" << get_inx() << "=" << get_name() << ",";
    for(auto const& [job, status] : _jobs)
    {
        out << "job#" << job->get_inx() << "?" << status << ",";
    }

    return out.str();
}

