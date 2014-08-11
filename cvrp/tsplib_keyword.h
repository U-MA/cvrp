#ifndef VRPSOLVER_TSPLIB_KEYWORD
#define VRPSOLVER_TSPLIB_KEYWORD

namespace VrpSolver {

    typedef std::string keyword;

    enum TsplibKeyword {
        // The specification part
        NAME, TYPE, COMMENT, DIMENSION, CAPACITY,
        EDGE_WEIGHT_TYPE, EDGE_WEIGHT_FORMAT, EDGE_DATA_FORMAT,
        NODE_COORD_TYPE, DISPLAY_DATA_TYPE, END_OF_FILE,

        // The data part
        NODE_COORD_SECTION, DEPOT_SECTION, DEMAND_SECTION,
        EDGE_DATA_SECTION, EDGE_WEIGHT_SECTION,
    };

    std::map<keyword, TsplibKeyword> keyword_map = {
        // The specification part
        { "NAME",                NAME },
        { "TYPE",                TYPE },
        { "COMMENT",             COMMENT },
        { "DIMENSION",           DIMENSION },
        { "CAPACITY",            CAPACITY },
        { "EDGE_WEIGHT_TYPE",    EDGE_WEIGHT_TYPE },
        { "EDGE_WEIGHT_FORMAT",  EDGE_WEIGHT_FORMAT },
        { "EDGE_DATA_FORMAT",    EDGE_DATA_FORMAT },
        { "NODE_COORD_TYPE",     NODE_COORD_TYPE },
        { "DISPLAY_DATA_TYPE",   DISPLAY_DATA_TYPE },
        { "EOF",                 END_OF_FILE },

        // The data part
        { "NODE_COORD_SECTION",  NODE_COORD_SECTION },
        { "DEPOT_SECTION",       DEPOT_SECTION },
        { "DEMAND_SECTION",      DEMAND_SECTION },
        { "EDGE_DATA_SECTION",   EDGE_DATA_SECTION },
        { "EDGE_WEIGHT_SECTION", EDGE_WEIGHT_SECTION }
    };

    enum EdgeWeightType {
        EXPLICIT, EUC_2D
    };

    std::map<keyword, EdgeWeightType> ew_type_map = {
        { "EXPLICIT", EXPLICIT },
        { "EUC_2D",   EUC_2D }
    };

    enum EdgeWeightFormat {
        LOWER_ROW
    };

    std::map<keyword, EdgeWeightFormat> ew_format_map = {
        { "LOWER_ROW", LOWER_ROW }
    };


} // namespace VrpSolver

#endif // VRPSOLVER_TSPLIB_KEYWORD
