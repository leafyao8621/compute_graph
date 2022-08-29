#include <sstream>
#include "../core.h"

ComputeGraph::ComputeGraph::NodeBase
    *ComputeGraph::
        ComputeGraph::
        NodeFactory::
        HandlerDivide::
        operator()(std::string line) {
    std::istringstream iss(line);
    std::string buf;
    iss >> buf;
    return new ComputeGraph::ComputeGraph::NodeDivide();
}
