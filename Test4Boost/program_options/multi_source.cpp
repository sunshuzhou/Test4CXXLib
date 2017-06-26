#include <iostream>
#include <boost/program_options.hpp>
#include <vector>
#include <fstream>

using namespace std;
namespace po = boost::program_options;

// ./Test4ProgramOptions a.cpp b.cpp c.cpp -I/usr/local -I/usr

int main(int argc, char **argv) {
    try {
        string config_file;
        po::options_description generic("Generic options");
        generic.add_options()
            ("version,v", "print version string")
            ("help,h", "print help message")
            ("config,c", po::value<string>(&config_file)->default_value("app.config"), "configuration file")
        ;


        int opt;
        po::options_description config("Configuration");
        config.add_options()
            ("optimization", po::value<int>(&opt)->default_value(10), "optimization level")
            ("include_path,I", po::value< vector<string> >()->composing(), "include path")
        ;

        po::options_description hidden("Hidden options");
        hidden.add_options()
            ("input_file", po::value< vector<string> >(), "input files")
        ;

        po::options_description cmdline_options;
        cmdline_options.add(generic).add(config).add(hidden);

        po::options_description config_file_options;
        config_file_options.add(config).add(hidden);

        po::options_description visible("Allowed options");
        visible.add(generic).add(config);

        po::positional_options_description p;
        p.add("input_file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), vm);
        po::notify(vm);

        ifstream ifs(config_file.c_str());
        if (!ifs) {
            cerr << "can not open " << config_file << endl;
            return 1;
        } else {
            po::store(parse_config_file(ifs, config_file_options), vm);
            po::notify(vm);
        }

        if (vm.count("help")) {
            cout << visible << endl;
            return 0;
        }

        if (vm.count("version")) {
            cout << "0.0.1" << endl;
            return 0;
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
