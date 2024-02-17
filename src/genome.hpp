#ifndef GENOME_CPP
#define GENOME_CPP

#include <godot_cpp/classes/node.hpp>
#include <vector>
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
    std::vector<CellStructure*> expressGenes();
    void setGene(Gene*, int);
    void insertGene(Gene*, int);
    void removeGene(int);
    Gene* getGene(int);
    int getSize();
private:
    std::vector<Gene*> genes;
};



}


#endif