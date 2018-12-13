#include <iostream>
#include "boost/filesystem.hpp"
#include <vector>
#include <boost/regex.hpp>

using namespace boost::filesystem;

int main(int argc, char *argv[])
{
    if (argc < 2){
        std::cerr << "error" << std::endl;
        return 1;
    }
    path p(argv[1]);
    try {
        if (exists(p)){
           std::cout << argv[1] << " is exists" << std::endl;
           if (is_regular_file(p)){
               std::cout << p << " is file. Size = " << file_size(p) << std::endl;

               const boost::regex file_filter("balance_[0-9]{8}_[0-9]{8}.txt");
               if (boost::regex_match(p.filename(), file_filter, boost::regex_constants::match_default)){
                   std::cout << "File is good" << std::endl;
               }
           }
           else if (is_directory(p)){
               std::cout << p << " is directory" << std::endl;
              /* std::vector<path> vec;
               copy(directory_iterator(p), directory_iterator(), std::back_inserter(vec));
               for (std::vector<path>::const_iterator it(vec.begin()); it != vec.end(); ++it){
                   std::cout << "     " << *it << std::endl;
               }*/
               for (const directory_entry& x : directory_iterator{p})
               {
                  std::cout << x.path() << std::endl;
               }
           }
           else if (is_symlink(p)){
               std::cout << p << " is symlink" << std::endl;
           }
           else{

           }
        }
        else{
            std::cout << argv[1] << " is not exists" << std::endl;
        }
    }
    catch (const filesystem_error &ex){
        std::cerr << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "unknown exception" << std::endl;
    }

    std::cin.get();
    return 0;
}
