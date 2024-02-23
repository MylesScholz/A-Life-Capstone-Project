# Cell Data Structure
```
Cell
│
├──CellState: a container for state variables of this Cell
│  │
│  ├──Alive: whether this Cell is alive or not
│  │
│  ├──Birth Time: the time when this Cell was created
│  │
│  ├──Lifespan: the duration after which this Cell has a chance to die
│  │
│  ├──Scale: the scaling factor of this Cell relative to the default size (50 px-wide Sprite)
│  │
│  ├──Homeostasis Nutrient Cost: the amount of nutrients expended per unit of time to keep this Cell alive
│  │
│  ├──Reproduction Nutrient Cost: the amount of nutrients expended when this Cell reproduces
│  │
│  ├──Total Nutrients: the total amount of nutrients stored in this Cell currently
│  │
│  ├──Nutrient Maximum: the maximum amount of nutrients this Cell can store at one time
│  │
│  ├──Homeostasis Energy Cost: the amount of energy expended per unit of time to keep this Cell alive
│  │
│  ├──Reproduction Energy Cost: the amount of energy expended when this Cell reproduces; scales with genome length
│  │
│  ├──Total Energy: the total amount of usable energy stored in this Cell currently
│  │
│  ├──Energy Maximum: the maximum amount of usable energy this Cell can store at one time
│  │
│  ├──Receptor Vectors: a list of vectors pointing from this Cell's center to activated CellMembrane Receptors
│  │
│  └──...
│
├──CellStructure: an abstract class representing physical structures within this Cell; pointers to each structure are stored in this Cell
│  │
│  ├──Creation Nutrient Cost: the amount of nutrients required to create this CellStructure
│  │
│  ├──Creation Energy Cost: the amount of energy required to create this CellStructure
│  │
│  ├──Maintenance Nutrient Cost: the amount of nutrients required to maintain this CellStructure; the structure cannot activate if this cost is not met
│  │
│  ├──Maintenance Energy Cost: the amount of energy required to maintain this CellStructure; the structure cannot activate if this cost is not met
│  │
│  ├──activate(CellState): tests the current CellState against the activation conditions of this CellStructure and executes any actions if the conditions are met
│  │
│  ├──Nucleus: the decision-making center of the cell
│  │  │
│  │  ├──Reproduction Nutrient Threshold: the amount of nutrients in this Cell above which the Cell will reproduce (should be > reproduction cost)
│  │  │
│  │  ├──Reproduction Energy Threshold: the amount of energy int this Cell above which the Cell will reproduce (should be > reproduction cost)
│  │  │
│  │  └──...
│  │
│  ├──CellMembrane: the external lipid barrier of this Cell; embedded with numerous proteins and structures that enable complex environmental interactions
│  │  │
│  │  ├──Receptor: an Area2D over this Cell that detects environmental nutrients; a CellMembrane may have multiple
│  │  │  │
│  │  │  ├──_on_body_entered(): when a collision is detected on the nutrient collision layer, this updates the CellState Receptor Vectors
│  │  │  │
│  │  │  └──...
│  │  │
│  │  └──...
│  │
│  ├──Ribosomes: chemical complexes that produce gene-coded proteins in cells
│  │  │
│  │  ├──Strength: a multiplier applied to the conversion between energy and nutrients
│  │  │
│  │  ├──Efficiency: the proportion of energy that is preserved when converting to nutrients
│  │  │
│  │  ├──Conversion Rate: the ratio of nutrient units to energy units at which these Ribosomes convert
│  │  │
│  │  ├──Activation Theshold: the proportional amount of resources in this Cell above or below which these Ribosomes will activate, depending on the threshold type and activation resource
│  │  │
│  │  ├──Theshold Type: the type of the activation threshold: high-pass or low-pass
│  │  │
│  │  ├──Activation Resource: the resources to which these Ribosomes "listen" to determine activation: nutrients or energy
│  │  │
│  │  └──...
│  │
│  ├──Mitochondria: the primary energy-producing organelles of Eukaryotic cells
│  │  │
│  │  ├──Strength: a multiplier applied to the conversion between nutrients and energy
│  │  │
│  │  ├──Efficiency: the proportion of nutrients that are preserved when converting to energy
│  │  │
│  │  ├──Conversion Rate: the ratio of energy units to nutrient units at which these Mitochondria convert
│  │  │
│  │  ├──Activation Theshold: the proportional amount of resources in this Cell above or below which these Mitochondria will activate, depending on the threshold type and activation resource
│  │  │
│  │  ├──Theshold Type: the type of the activation threshold: high-pass or low-pass
│  │  │
│  │  ├──Activation Resource: the resources to which these Mitochondria "listen" to determine activation: nutrients or energy
│  │  │
│  │  └──...
│  │
│  ├──Flagella: external cell components that enable motility
│  │  │
│  │  ├──Position Vector: the position vector of these Flagella relative to this Cell's center
│  │  │
│  │  ├──Movement Force: a 2D force vector that this Cell will apply to itself when these Flagella are activated
│  │  │
│  │  ├──Activation Energy Cost: the amount of energy expended per unit of time while these Flagella are activated
│  │  │
│  │  └──...
│  │
│  └──...
│
├──Genome: the genetic code of this Cell; contains a list of Genes (the gene sequence) and handles gene expression
│  │
│  ├──expressGenes(): iterates through the gene sequence, expressing each and applying modifiers; runs once at cell creation
│  │
│  ├──Gene: an abstract class representing a single gene; stored in a list in the Genome node
│  │  │
│  │  ├──getType(): returns whether this Gene is a structure gene or a modifier gene
│  │  │
│  │  ├──getName(): returns the unique name of this Gene
│  │  │
│  │  ├──express(): if this Gene is a structure gene, instantiate the structure and return it; otherwise, throw an error
│  │  │
│  │  ├──getValue(): if this Gene is a modifier gene, return the strength value of this modifier, from [0.0, 1.0]; otherwise, throw an error
│  │  │
│  │  ├──Structure Gene: a semantic type of Gene that defines a structure in the cell
│  │  │
│  │  ├──Modifier Gene: a semantic type of Gene that modifies a structure in the cell
│  │  │
│  │  └──...
│  │
│  └──...
│
└──...
```