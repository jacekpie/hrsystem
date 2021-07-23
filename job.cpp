/*
 * This file contains implementation of a job class.
 */

#include <sstream>
#include <iostream>

// Local include
#include "job.h"
#include "candidate.h"


Job::Job(const S& sLine)
{
//
// Constructor - used when reading a line from database
//
    // Get the global job index
    _inx = read_integer(sLine, 4);

    // Get the job name
    _position = read_string(sLine, find_equal_sign(sLine)+1);

    // Get the employee name
    _employee = read_string(sLine, find_comma(sLine)+1);
}


Job::Job(const S& sPosition, const uint inx)
{
//
// Constructor - used when user builds a new job.
//
    // Stores global job index
    _inx = inx;

    // Store job position
    _position = sPosition;
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

const Candidates& Job::get_candidates() const
{
    return _candidates;
}

S Job::get_employee() const
{
    return _employee;
}

bool Job::is_closed() const
{
//
// Returns true is this job is closed.
//

    return (_employee != "");
}

void Job::candidate(
    const SPtr_Candidate candidate,
    const S& status)
{
//
// Add a candidate to a job.
//

    // Store status of the given candidate
    _candidates[candidate] = status;

    // If this candidate was accepted, make him an employee for this job
    if(status == "accepted")
    {
        _employee = candidate->get_name();
    }
}


S Job::print(const S& sTab) const
{
//
// Print all the data about the job
//

    std::ostringstream out;
    out << "job #" << get_inx();
    out << "  `" << get_position_name() << "`" << std::endl;
    if(is_closed())
    {
        out << sTab << "job is closed, chosen employee: `" << get_employee() << "`" << std::endl;
    }
    else
    {
        out << sTab << "job is open, candidates (" << _candidates.size() << "): " << std::endl;
        for(auto const& [candidate, status] : _candidates)
        {
            out << sTab << sTab << candidate->get_name() << "  status: `" << status << "`" << std::endl;
        }
    }

    return out.str();
}

S Job::build_db_line() const
{
//
// Build a txt line for database describing the candidate.
//
    std::ostringstream out;
    out << "job#" << get_inx() << "=" << get_position_name() << ",";
    return out.str();
}

