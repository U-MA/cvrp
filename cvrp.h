#include <string>

namespace VrpSolver {
    class Cvrp {
    public:
        Cvrp() : name_() {}

        // member variable
        std::string name_;
        unsigned int dimension_;
        unsigned int capacity_;
    };

    // cvrp intialize by infile
    void read_vrp(Cvrp& cvrp, const std::string &infile);
}
