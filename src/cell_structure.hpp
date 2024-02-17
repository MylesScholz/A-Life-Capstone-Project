#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <godot_cpp/classes/node.hpp>

namespace godot {

class CellStructure : public Node
{
    GDCLASS(CellStructure, Node);

protected:
    static void _bind_methods();

private:
    /* data */
public:
    CellStructure(/* args */);
    ~CellStructure();
};

}

#endif