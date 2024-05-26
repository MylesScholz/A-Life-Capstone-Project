#include "genome.hpp"
#include "cell_membrane_gene.hpp"
#include "cell_spawner.hpp"
#include "flagella_gene.hpp"
#include "mitochondria_gene.hpp"
#include "modifier_gene.hpp"
#include "nucleus_gene.hpp"
#include "ribosomes_gene.hpp"

#include "helpers.hpp"

#include <godot_cpp/classes/spin_box.hpp>

Genome::Genome() {
}

Genome::~Genome() {
	for (int i = 0; i < genes.size(); i++) {
		delete genes.get(i);
	}
}

void Genome::setCellMembraneChance(float min, float max) {
	this->cell_membrane_chance[0] = min;
	this->cell_membrane_chance[1] = max;
}
float *Genome::getCellMembraneChance() const { return (float *)cell_membrane_chance; }

void Genome::setFlagellaChance(float min, float max) {
	this->flagella_chance[0] = min;
	this->flagella_chance[1] = max;
}
float *Genome::getFlagellaChance() const { return (float *)flagella_chance; }

void Genome::setMitochondriaChance(float min, float max) {
	this->mitochondria_chance[0] = min;
	this->mitochondria_chance[1] = max;
}
float *Genome::getMitochondriaChance() const { return (float *)mitochondria_chance; }

void Genome::setNucleusChance(float min, float max) {
	this->nucleus_chance[0] = min;
	this->nucleus_chance[1] = max;
}
float *Genome::getNucleusChance() const { return (float *)nucleus_chance; }

void Genome::setRibosomeChance(float min, float max) {
	this->ribosome_chance[0] = min;
	this->ribosome_chance[1] = max;
}
float *Genome::getRibosomeChance() const { return (float *)ribosome_chance; }

Vector<CellStructure *> Genome::expressGenes() {
	Vector<CellStructure *> cellStructures;
	CellStructure *currentStructure = nullptr;
	for (int i = 0; i < genes.size(); i++) {
		if (genes.get(i)->getType() == "Structure") {
			currentStructure = genes.get(i)->express();
			cellStructures.push_back(currentStructure);
		} else if (currentStructure) {
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
	int generatedValue = rand.randf_range(0, 100);

	if (generatedValue >= this->cell_membrane_chance[0] && generatedValue < this->cell_membrane_chance[1])
		return new CellMembraneGene();

	if (generatedValue >= this->flagella_chance[0] && generatedValue < this->flagella_chance[1])
		return new FlagellaGene();

	if (generatedValue >= this->mitochondria_chance[0] && generatedValue < this->mitochondria_chance[1])
		return new MitochondriaGene();

	if (generatedValue >= this->nucleus_chance[0] && generatedValue < this->nucleus_chance[1])
		return new NucleusGene();

	if (generatedValue >= this->ribosome_chance[0] && generatedValue < this->ribosome_chance[1])
		return new RibosomesGene();

	//Default to a Random modifier gene.
	return randomModifierGene();
}