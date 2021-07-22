#include <sstream>

// Local include
#include "job.h"
#include "applicant.h"


Job::Job(const S& sLine)
{
    // Store the raw line
    _sLine = sLine;

    // Get the job global index
    _inx = read_integer(sLine, 4);

    // Get the job name
    _position = read_string(sLine, find_equal_sign(sLine)+1);

    // Get the employee name
    _employee = read_string(sLine, find_comma(sLine)+1);
}

Job::~Job()
{

}

S Job::get_db_line() const
{
    return _sLine;
}

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
        const auto& applicants = get_applicants();
        out << sTab << "job is open, applicants (" << applicants.size() << "): " << std::endl;
        for(auto const& [applicant, status] : applicants)
        {
            out << sTab << sTab << applicant->get_name() << std::endl;
        }
    }

    return out.str();
}

