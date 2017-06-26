#include <iostream>
#include <boost/program_options.hpp>
#include <vector>

using namespace std;
namespace po = boost::program_options;

// ./Test4ProgramOptions a.cpp b.cpp c.cpp -I/usr/local -I/usr

int main(int argc, char **argv) {
    try {
        int opt;

        po::positional_options_description p;
        p.add("input_file", -1);

        po::options_description desc("Test description");
        desc.add_options()
            ("help,h", "This will print help message")
            ("another_parameter", po::value<int>(&opt), "This is another parameter.")
            ("include_path,I", po::value< vector<string> >(), "include path")
            ("input_file", po::value< vector<string> >(), "input files")
            ;
        po::variables_map vm;
        //po::store(po::parse_command_line(argc, argv, desc), vm);
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help") || 0 == vm.size()) {
            cout << desc << endl;
            return 0;
        }

        if (vm.count("another_parameter")) {
            cout << "another_parameter set to " << vm["another_parameter"].as<int>() << endl;
            cout << "another_parameter set to " << opt << endl;
        } else {
            cout << "another_paramter was not set." << endl;
        }

        if (vm.count("include_path")) {
            cout << "Include path: " << endl;
            for (auto i: vm["include_path"].as< vector<string> >()) {
                cout << "\t" << i << endl;
            }
        }

        if (vm.count("input_file")) {
            cout << "Input files:" << endl;
            for (auto i: vm["input_file"].as< vector<string> >()) {
                cout << "\t" << i << endl;
            }
        }
        
    } catch (exception &e) {
        cerr << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Exception of unknown type" << endl;
        return 1;
    }

    return 0;
}
