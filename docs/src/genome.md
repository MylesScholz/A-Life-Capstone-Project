# Genome Description

## Classes

Genome
Inherits: none
Inherited by: none

Description: the Genome is class representing the genetic material of a cell; it contains and manages the Cell's Genes

### Properties
- genes (Vector\<Gene *\>): a list of references to Genes managed by this Genome

### Methods
- Vector<CellStructure *> expressGenes(): iterates through genes and creates the list of modified CellStructures defined by it

- void addGene(Gene *newGene): appends the given Gene reference to genes
- void setGene(Gene *newGene, int index): replaces (and deletes) the Gene at the given index with the given Gene reference
- void insertGene(Gene *newGene, int index): inserts the given Gene reference into genes at the given index
- void removeGene(int index): removes and deletes the Gene at the given index
- void swapGene(int indexA, int indexB): swaps the Gene references at indexA and indexB of genes
- Gene *getGene(int index): returns the Gene reference at the given index of genes
- int getSize(): returns the length of genes

## Non-Member Functions
None
