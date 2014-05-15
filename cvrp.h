#include <string>
#include <vector>

namespace VrpSolver {
    class Cvrp {
    public:
        Cvrp() : name_(), dimension_(0), capacity_(0), demands_(0) {}

        // accessor
        unsigned int demand(unsigned int node_id);

        // member variable
        std::string name_;
        unsigned int dimension_;
        unsigned int capacity_;
        unsigned int depot_;
        std::vector<unsigned int> demands_;
    };

    // cvrp intialize by infile
    void read_vrp(Cvrp& cvrp, const std::string &infile);
}
