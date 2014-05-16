#ifndef VRPSOLVER_TSPLIB_FORMAT_H
#define VRPSOLVER_TSPLIB_FORMAT_H

namespace VrpSolver {
    // TSPLIB format用のキーワード、value集
    namespace Tsplib {
        const std::string NAME      = "NAME";
        const std::string TYPE      = "TYPE";
        const std::string DIMENSION = "DIMENSION";
        const std::string CAPACITY  = "CAPACITY";

        const std::string EDGE_WEIGHT_TYPE   = "EDGE_WEIGHT_TYPE";
        const std::string EDGE_WEIGHT_FORMAT = "EDGE_WEIGHT_FORMAT";
        const std::string EDGE_DATA_FORMAT   = "EDGE_DATA_FORMAT";
        const std::string NODE_COORD_TYPE    = "NODE_COORD_TYPE";
        const std::string DISPLAY_DATA_TYPE  = "DISPLAY_DATA_TYPE";

        const std::string NODE_COORD_SECTION  = "NODE_COORD_SECTION";
        const std::string DEPOT_SECTION       = "DEPOT_SECTION";
        const std::string DEMAND_SECTION      = "DEMAND_SECTION";
        const std::string EDGE_DATA_SECTION   = "EDGE_DATA_SECTION";
        const std::string EDGE_WEIGHT_SECTION = "EDGE_WEIGHT_SECTION";

        // EDGE_WEIGHT_TYPEのvalue
        namespace EdgeWeightType {
            const std::string EXPLICIT = "EXPLICIT";
            const std::string EUC_2D   = "EUC_2D";
        }

        // EDGE_WEIGHT_FORMATのvalue
        namespace EdgeWeightFormat {
            const std::string LOWER_ROW = "LOWER_ROW";
        }

        // DISPLAY_DATA_TYPEのvalue
        namespace DisplayDataType {
            const std::string NO_DISPLAY = "NO_DISPLAY";
        }
    }
}

#endif // VRPSOLVER_TSPLIB_FORMAT_H
