# Genome Description

## Classes

Genome
Inherits: none
Inherited by: none

Description: the Genome is a class that contains and manages the Cell's Genes

### Properties
- cell_membrane_chance (float[]): the range of values (0 to 100) within which a CellMembraneGene will be created in GenerateRandomGene()
- flagella_chance (float[]): the range of values (0 to 100) within which a FlagellaGene will be created in GenerateRandomGene()
- mitochondria_chance (float[]): the range of values (0 to 100) within which a MitochondriaGene will be created in GenerateRandomGene()
- nucleus_chance (float[]): the range of values (0 to 100) within which a NucleusGene will be created in GenerateRandomGene()
- ribosome_chance (float[]): the range of values (0 to 100) within which a RibosomesGene will be created in GenerateRandomGene()
- genes (Vector\<Gene *\>): a list of references to Genes managed by this Genome

### Methods
- void setCellMembraneChance(float min, float max): sets cell_membrane_chance to the given values
- float *getCellMembraneChance() const: returns a reference to cell_membrane_chance

- void setFlagellaChance(float min, float max): sets flagella_chance to the given values
- float *getFlagellaChance() const: returns a reference to flagella_chance

- void setMitochondriaChance(float min, float max): sets mitochondria_chance to the given values
- float *getMitochondriaChance() const: returns a reference to mitochondria_chance

- void setNucleusChance(float min, float max): sets nucleus_chance to the given values
- float *getNucleusChance() const: returns a reference to nucleus_chance

- void setRibosomeChance(float min, float max): sets ribosome_chance to the given values
- float *getRibosomeChance() const: returns a reference to ribosome_chance

- void setGeneChances(float cell_membrane_chance, float flagella_chance, float mitochondria_chance, float nucleus_chance, float ribosome_chance): Sets all genes chances to given values. Overflow will effectively be taken off the chance of ribosome then nucleus then mitochondria then flagella

- Vector<CellStructure *> expressGenes(): iterates through genes and creates the list of modified CellStructures defined by it

- void addGene(Gene *newGene): appends the given Gene reference to genes
- void setGene(Gene *newGene, int index): replaces (and deletes) the Gene at the given index with the given Gene reference
- void insertGene(Gene *newGene, int index): inserts the given Gene reference into genes at the given index
- void removeGene(int index): removes and deletes the Gene at the given index
- void swapGene(int indexA, int indexB): swaps the Gene references at indexA and indexB of genes
- Gene *getGene(int index): returns the Gene reference at the given index of genes
- int getSize(): returns the length of genes

- Gene *GenerateRandomGene(): creates a random Gene based on the chance properties

## Non-Member Functions
None
