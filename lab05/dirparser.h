#ifndef DIRPARSER_H
#define DIRPARSER_H

#include <iostream>
#include <exception>
#include <string>
#include <map>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

struct acc
{
    std::string m_brocker; // название брокера
    uint32_t m_date; // дата
    int32_t m_count; // кол-во файлов

    acc(std::string brocker, uint32_t dt, const int32_t count = 0)
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
    acc brockers_parse(std::string &brocker, std::string &fn, acc &test_acc);
private:
    fs::path m_path;
    std::map<std::string, acc> m_brockers;
};

#endif // DIRPARSER_H
