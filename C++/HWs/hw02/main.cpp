#include <iostream>
#include <vector>
#include <iomanip>
#include "doprava.hpp"

//Feel free to create your solution in multiple files
// and add the includes here. e.g.:
//#include "solution.hpp"


void print_header(Line &tmp_line, const std::string &stop, int j);

int main(int argc, char **argv) {

    // Load files:
    DriverList dl;
    dl.loadFromFile("driver_list.txt");

    Network net;
    net.loadFromFile("network.txt");

    // variables for argument decoding
    std::string flag_in;
    std::list<std::string> stop_in;

    if (argc > 1)
        flag_in = std::string(argv[1]);
    else {
        std::cerr << "Missing argument. Terminating." << "\n";
        return 1;
    }

    if ((!flag_in.compare("--schedule"))) {
        // input check - do not edit
        if (argc > 2) {
            for (int i = 2; i < argc; i++) {
                std::string temp = argv[i];
                replace(temp.begin(), temp.end(), '_', ' ');
                stop_in.push_back(temp);
            }
        } else {
            std::cerr << "Missing stop name. Terminating." << "\n";
            return 2;
        }
        // end of input check

        Time_table_fwd time_fwd; // time_fwd struct
        Time_table_bwd time_bwd; // time_bwd struct
        Line tmp_line;
        int nmb_of_lines = net.nlines(); // number of lines
        for (std::string stop: stop_in) {
            for (int j = 0; j < nmb_of_lines; ++j) {
                tmp_line = net.getLine(j);
                auto find_stop = std::find(tmp_line.stops.begin(), tmp_line.stops.end(),
                                           stop); // try to find input stop in current line
                if (find_stop != tmp_line.stops.end()) { // if our stop is in current line
                    print_header(tmp_line, stop, j); // printing header

                    time_fwd.counter = 0;
                    time_bwd.counter = 0;
                    std::vector<Time_table_fwd> time_fwd_vec;
                    std::vector<Time_table_bwd> time_bwd_vec;
                    char oldFill = std::cout.fill(' '); // default fill
                    auto index = std::distance(tmp_line.stops.begin(), find_stop); // get index of our station
                    for (unsigned int k = 0; k < net.getLine(j).conns_fwd.size(); ++k) {
                        auto time_def_fwd = net.getLine(j).conns_fwd[k];
                        auto time_def_bwd = net.getLine(j).conns_bwd[k];
                        //todo - if change conns_fwd to conns_bwd ---> print right values
                        //todo - solve printing righting colum
                        time_fwd.seconds = time_def_fwd.at(index).ti.gets();
                        time_fwd.hours = time_fwd.seconds / 3600;
                        time_fwd.minutes = (time_fwd.seconds % 3600) / 60;
                        time_bwd.seconds = time_def_bwd.at(index).ti.gets();
                        time_bwd.hours = time_bwd.seconds / 3600;
                        time_bwd.minutes = (time_bwd.seconds % 3600) / 60;
                        time_fwd_vec.push_back(time_fwd);
                        time_bwd_vec.push_back(time_bwd);
                    }
                    for (unsigned int t = 0; t < 24; ++t) {
                        std::cout << "\n| " << std::setw(2) << std::setfill('0') << t << " |";
                        for (unsigned int n = 0; n < time_fwd_vec.size(); ++ n){
                            if (time_fwd_vec[n].hours == t){
                                std::cout << " " << std::setw(2) << std::setfill('0') << time_fwd_vec[n].minutes;
                                time_fwd.counter ++;
                            }
                        }
                        std::cout << std::setw(33 - 3 * time_fwd.counter) << std::setfill(' ') << " ";
                        time_fwd.counter = 0;
                        std::cout << "|| " << std::setw(2) << std::setfill('0') << t << " |";
                        for (unsigned int m = 0; m < time_bwd_vec.size(); ++ m){
                            if (time_bwd_vec[m].hours == t){
                                std::cout << " " << std::setw(2) << std::setfill('0') << time_bwd_vec[m].minutes;
                                time_bwd.counter ++;
                            }
                        }
                        std::cout << std::setw(34 - 3 * time_bwd.counter) << std::setfill(' ') << " |";
                        time_bwd.counter = 0;
                    }


                    std::cout.fill(oldFill); // set fill to default
                    std::cout << "\n+----+---------------------------------++----+---------------------------------+\n";
                }
            }
        }



        /* here should start the code for printing timetables*/
        /* stop_in contains names of stops, for which the timetable is to be printed. */

        // This is an example, how it can be done using lambda-function
//        for_each(stop_in.begin(), stop_in.end(), [&] (std::string stop_name) {print_timetable(net,stop_name);} );
        // This is an example, how it can be done using for-loop
        // for( auto iter = stop_in.begin(); iter != stop_in.end(); iter++) print_timetable(net,*iter);

        /* here should end the code for printing timetables*/
    } else if ((!flag_in.compare("--line-routing"))) {

/* here should start the code for printing line routes without stats*/



/* here should end the code for printing line routes without stats*/
    } else if ((!flag_in.compare("--driver-stops"))) {

/* here should start the code for stops statistics for drivers */



/* here should end the code for stops statistics for drivers */
    } else {
        std::cout << "Flag not recognized, terminating." << "\n";
    }

    return 0;
}

void print_header(Line &tmp_line, const std::string &stop, int j) {
    std::cout << "+------------------------------------------------------------------------------+\n";
    std::cout << "| " << stop << std::setw(75 - stop.length()) << "Line: " << j << " |\n";
    std::cout << "+--------------------------------------++--------------------------------------+\n";

    std::string last_stop;
    size_t  index = tmp_line.stops.back().find("\r");
    if(index == std::string::npos){
        last_stop = tmp_line.stops.back();
    }else{
        last_stop = tmp_line.stops.back().erase(tmp_line.stops.back().find("\r"),2);
    }
    std::cout << "| To: " << last_stop << std::setw(40 - last_stop.length()) << "|| To: "
              << tmp_line.stops[0] << std::setw(35 - tmp_line.stops[0].length()) << "|\n";
    std::cout << "+----+---------------------------------++----+---------------------------------+";
}
