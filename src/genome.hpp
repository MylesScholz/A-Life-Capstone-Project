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

	Vector<CellStructure *> expressGenes();

	void addGene(Gene *);
	void setGene(Gene *, int);
	void insertGene(Gene *, int);
	void removeGene(int);
	void swapGene(int, int);
	Gene *getGene(int);
	int getSize();

private:
	Vector<Gene *> genes;
};