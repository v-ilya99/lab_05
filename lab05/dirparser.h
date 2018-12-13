#ifndef DIRPARSER_H
#define DIRPARSER_H

#include <iostream>
#include <exception>
#include <string>
#include <map>
#include "boost/filesystem.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

namespace fs = boost::filesystem;

struct acc
{
    std::string m_brocker; // название брокера
    boost::gregorian::date m_date; // дата
    int32_t m_count; // кол-во файлов

    acc(const std::string &brocker, boost::gregorian::date &dt, const int32_t count = 0)
        : m_brocker(brocker), m_date(dt), m_count(count)
    {
    }
};


class dirparser
{
public:
    explicit dirparser(std::string path);
    void parse();
private:
    void check_path(fs::path value);
    acc brockers_parse(std::string &brocker, std::string &fn);
private:
    fs::path m_path;
    std::map<std::string, acc> m_brockers;
};

#endif // DIRPARSER_H
