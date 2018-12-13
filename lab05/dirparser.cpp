#include <boost/regex.hpp>
#include <algorithm>
#include "dirparser.h"

dirparser::dirparser(std::string path)
    : m_path(path)
{

}

void dirparser::parse()
{
    if (!fs::exists(m_path)){
        throw std::exception("path is not exists");
    }
    for (const fs::directory_entry& x : fs::directory_iterator{m_path})
    {
        check_path(x.path());
    }
}

void dirparser::check_path(boost::filesystem::path value)
{
    if (is_regular_file(value)){
        //std::cout << value << " is file. Size = " << file_size(value) << std::endl;
        const boost::regex file_filter("balance_[0-9]{8}_[0-9]{8}.txt");
        if (boost::regex_match(value.filename().string(), file_filter, boost::regex_constants::match_default)){

            boost::filesystem::path dir = value.parent_path();
            std::string brocker;// = value.parent_path().string();
            std::size_t sep = value.parent_path().string().find_last_of("\\/");
            if (sep != std::string::npos)
                brocker = value.parent_path().string().substr(sep + 1, value.parent_path().string().size() - sep - 1);
            //std::cout << value << "\t tmp = " <<tmp << "\t sep = " << sep << "\t sep2 = " << value.parent_path().string().size() - sep - 1 << std::endl;
            std::string filename(value.filename().string());
            std::cout << brocker << " " << filename << std::endl;
            brockers_parse(brocker, filename);
        }
    }
    else if (is_directory(value)){
        //std::cout << value << " is directory" << std::endl;
        for (const fs::directory_entry& x : fs::directory_iterator{value})
        {
            check_path(x.path());
        }
    }
    else if (is_symlink(value)){
        //std::cout << value << " is symlink" << std::endl;
    }
    else {
        throw std::exception("incorrect object");
    }
}

acc dirparser::brockers_parse(std::string &brocker, std::string &fn)
{
    std::string raw = fs::change_extension(fn, "").string();
    raw.erase(0, 8);
    std::string account(raw.substr(0, 8));
    std::string date(raw.substr(9, 8));
    std::cout << "account = " << account << "\t date = " << date << std::endl;
    //std::string tmp;
    //std::size_t sep = value.parent_path().string().find_last_of("_");
    boost::gregorian::date dt;
    acc temp(brocker, dt, 0);
    return temp;
}
