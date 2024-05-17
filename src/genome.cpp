#include "genome.hpp"
#include "modifier_gene.hpp"
#include "cell_membrane_gene.hpp"
#include "flagella_gene.hpp"
#include "mitochondria_gene.hpp"
#include "nucleus_gene.hpp"
#include "ribosomes_gene.hpp"

//Gene Probs
const static float CELL_MEMBRANE_CHANCE[2] = {0,15};
const static float FLAGELLA_CHANCE[2] = {15,30};
const static float MITOCHONDRIA_CHANCE[2] = {30,40};
const static float NUCLEUS_CHANCE[2] = {40,45};
const static float RIBOSOME_CHANCE[2] = {45,55};
const static float MODIFIER_CHANCE[2] = {55,100};

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
			currentStructure->modify(genes.get(i)->getName(), genes.get(i)->getValue());
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

//The random genes will need to be added to everytime we make a new gene type. We might want to come up with a better solution in the future.
Gene *Genome::GenerateRandomGene() {
	RandomNumberGenerator rand = RandomNumberGenerator();
	int generatedValue = rand.randf_range(0,100);

	if(generatedValue >= CELL_MEMBRANE_CHANCE[0] && generatedValue < CELL_MEMBRANE_CHANCE[1])
		return new CellMembraneGene();

	if(generatedValue >= FLAGELLA_CHANCE[0] && generatedValue < FLAGELLA_CHANCE[1])
		return new FlagellaGene();

	if(generatedValue >= MITOCHONDRIA_CHANCE[0] && generatedValue < MITOCHONDRIA_CHANCE[1])
		return new MitochondriaGene();

	if(generatedValue >= NUCLEUS_CHANCE[0] && generatedValue < NUCLEUS_CHANCE[1])
		return new NucleusGene();

	if(generatedValue >= RIBOSOME_CHANCE[0] && generatedValue < RIBOSOME_CHANCE[1])
		return new RibosomesGene();

	if(generatedValue >= MODIFIER_CHANCE[0] && generatedValue < MODIFIER_CHANCE[1])
		return randomModifierGene();
	return randomModifierGene();
}
