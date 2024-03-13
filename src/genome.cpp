#include "genome.hpp"

Genome::Genome() {
}

Genome::~Genome() {
	for (int i = 0; i < genes.size(); i++) {
		delete genes.get(i);
	}
}

Vector<CellStructure *> Genome::expressGenes() {
	Vector<CellStructure *> cellStructures;
	CellStructure *currentStructure;
	for (int i = 0; i < genes.size(); i++) {
		if (genes.get(i)->getType() == "Structure") {
			currentStructure = genes.get(i)->express();
			cellStructures.push_back(currentStructure);
		} else {
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

void Genome::addGene(Gene *newGene) {
	genes.push_back(newGene);
}

void Genome::setGene(Gene *newGene, int index) {
	Gene *removedGene = genes.get(index);
	genes.set(index, newGene);
	delete removedGene;
}

void Genome::insertGene(Gene *newGene, int index) {
	genes.insert(index, newGene);
}

void Genome::removeGene(int index) {
	Gene *removedGene = genes.get(index);
	genes.remove_at(index);
	delete removedGene;
}

void Genome::swapGene(int indexA, int indexB) {
	Gene *swap = genes.get(indexA);
	genes.set(indexA, genes.get(indexB));
	genes.set(indexB, swap);
}

Gene *Genome::getGene(int index) {
	return genes.get(index);
}

int Genome::getSize() {
	return genes.size();
}
