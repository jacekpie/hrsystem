#include <sstream>
#include <iostream>

// Local include
#include "job.h"
#include "applicant.h"


Job::Job(const S& sLine)
{
    // Get the global job index
    _inx = read_integer(sLine, 4);

    // Get the job name
    _position = read_string(sLine, find_equal_sign(sLine)+1);

    // Get the employee name
    _employee = read_string(sLine, find_comma(sLine)+1);
}


Job::Job(const S& sPosition, const uint inx)
{
    // Stores global job index
    _inx = inx;

    // Store job position
    _position = sPosition;
    std::cout << "building job with position `" << sPosition << "`" << std::endl;

}

Job::~Job(){}


S Job::get_position_name() const
{
    return _position;
}

uint Job::get_inx() const
{
    return _inx;
}

const Applicants& Job::get_applicants() const
{
    return _applicants;
}

S Job::get_employee() const
{
    return _employee;
}

bool Job::is_closed() const
{
    return (_employee != "");
}

void Job::candidate(
    const SPtr_Applicant candidate,
    const S& status)
{
    // Store status of the given candidate
    _applicants[candidate] = status;

    // If this candidate was accepted, make him an employee for this job
    if(status == "accepted")
    {
        _employee = candidate->get_name();
    }
}


S Job::print(const S& sTab) const
{
    std::ostringstream out;
    out << "job #" << get_inx();
    out << "  `" << get_position_name() << "`" << std::endl;
    if(is_closed())
    {
        out << sTab << "job is closed, chosen employee: `" << get_employee() << "`" << std::endl;
    }
    else
    {
        out << sTab << "job is open, applicants (" << _applicants.size() << "): " << std::endl;
        for(auto const& [applicant, status] : _applicants)
        {
            out << sTab << sTab << applicant->get_name() << "  status: `" << status << "`" << std::endl;
        }
    }

    return out.str();
}

S Job::build_db_line() const
{
    std::ostringstream out;
    out << "job#" << get_inx() << "=" << get_position_name() << ",";
    return out.str();
}

