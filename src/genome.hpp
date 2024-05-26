#pragma once

#include "cell_structure.hpp"
#include "gene.hpp"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/vector.hpp>

using namespace godot;

class Genome {
public:
	Genome();
	~Genome();

	void setCellMembraneChance(float, float);
	void setFlagellaChance(float, float);
	void setMitochondriaChance(float, float);
	void setNucleusChance(float, float);
	void setRibosomeChance(float, float);

	Vector<CellStructure *> expressGenes();

	void addGene(Gene *);
	void setGene(Gene *, int);
	void insertGene(Gene *, int);
	void removeGene(int);
	void swapGene(int, int);
	Gene *getGene(int);
	int getSize();

	Gene *GenerateRandomGene();

private:
	//Gene Probs. Currently setup to be out of 100. any values not in these ranges are defaulted to a random modifier gene
	float cell_membrane_chance[2] = { 0, 15 };
	float flagella_chance[2] = { 15, 30 };
	float mitochondria_chance[2] = { 30, 40 };
	float nucleus_chance[2] = { 40, 45 };
	float ribosome_chance[2] = { 45, 55 };

	Vector<Gene *> genes;
};