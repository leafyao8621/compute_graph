#include <sstream>
#include "../core.h"

ComputeGraph::ComputeGraph::NodeBase
    *ComputeGraph::
        ComputeGraph::
        NodeFactory::
        HandlerConstant::
        operator()(std::string line) {
    std::istringstream iss(line);
    std::string buf;
    iss >> buf;
    double value;
    iss >> value;
    return new ComputeGraph::ComputeGraph::NodeConstant(value);
}
