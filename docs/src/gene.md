# Gene Description

## Classes

Gene
Inherits: none 
Inherited by: CellMembraneGene, FlagellaGene, MitochondriaGene, NucleusGene, RibosomesGene

Description: an abstract class representing a gene in a genome; genes either define a structure in the cell or modify an existing structure

### Properties
None

### Methods
- virtual String getType(): an abstract method that should return the type of the Gene ("Structure" or "Modifier")
- virtual String getName(): an abstract method that should return the name of the Gene (e.g., "Flagella" or "ACTIVATION_THRESHOLD")
- virtual CellStructure *express(): an abstract method for structure Genes that should return a new instance of the associated CellStructure
- virtual float getValue(): an abstract method for modifier Genes that should return the modifier value of the Gene
- virtual Gene *clone(): an abstract method that should return a copy of the Gene

## Non-Member Functions
None
