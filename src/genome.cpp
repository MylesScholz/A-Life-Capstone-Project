#include "genome.hpp"

using namespace godot;

void Genome::_bind_methods() {

}

Genome::Genome(/* args */)
{
}

Genome::~Genome()
{
}

std::vector<CellStructure*> Genome::expressGenes() {
    std::vector<CellStructure*> cellStructures;
    CellStructure* currentStructure;
    for (int i = 0; i < genes.size(); i++)
    {
        if (genes.at(i)->getType() == "Structure")
        {
            currentStructure = genes.at(i)->express();
            cellStructures.push_back(currentStructure);
        }
        else
        {
            /*
            WIP
            get the name of modifier gene and the value and send it into the current structure. 
            something like:
            currentStructure->modify(genes.at(i).getName(), genes.at(i).getValue())
            */
        }
    }
    
	return cellStructures;
}


void godot::Genome::setGene(Gene* newGene, int index) {
    Gene* removedGene = genes.at(index);
    genes[index] = newGene;
    delete removedGene;
}


void godot::Genome::insertGene(Gene* newGene, int index) {
    std::vector<Gene*>::iterator it;
    genes.insert(it+index,newGene);
}

void godot::Genome::removeGene(int index) {
    std::vector<Gene*>::iterator it;
    Gene* removedGene = genes.at(index);
    genes.erase(it+index);
    delete removedGene;
}

Gene* godot::Genome::getGene(int index) {
	return genes.at(index);
}


int godot::Genome::getSize() {
	return genes.size();
}
