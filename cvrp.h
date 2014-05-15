#include <string>

namespace VrpSolver {
    class Cvrp {
    public:
        Cvrp() : name_() {}

        // member variable
        std::string name_;
    };

    // cvrp intialize by infile
    void read_vrp(Cvrp& cvrp, const std::string &infile);
}
