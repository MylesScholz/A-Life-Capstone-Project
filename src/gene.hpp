#ifndef GENE_HPP
#define GENE_HPP

#include <godot_cpp/classes/node.hpp>
#include "cell_structure.hpp"
namespace godot {

class Gene : public Node
{
    GDCLASS(Gene, Node)

protected:
    static void _bind_methods();

public:
    Gene(/* args */);
    ~Gene();
    virtual std::string getType();
    virtual std::string getName();
    virtual CellStructure* express();
    virtual float getValue();
private:
    /* data */
};

}

#endif