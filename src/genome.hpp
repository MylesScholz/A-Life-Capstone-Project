#ifndef GENOME_CPP
#define GENOME_CPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/vector.hpp>
#include "gene.hpp"
#include "cell_structure.hpp"

namespace godot {

class Genome : public Node
{
    GDCLASS(Genome, Node)

protected:
    static void _bind_methods();

public:
    Genome();
    ~Genome();
    Vector<CellStructure*> expressGenes();
    void setGene(Gene*, int);
    void insertGene(Gene*, int);
    void removeGene(int);
    void swapGene(int, int);
    Gene* getGene(int);
    int getSize();
private:
    Vector<Gene*> genes;
};



}


#endif