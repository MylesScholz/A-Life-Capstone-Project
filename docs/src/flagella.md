#Flagella Description

## Classes

Flagella
Inherits: CellStructure
Inherited by: none

Description: the Flagella class is a CellStructure that enables the randomized motility of cells.

### Properties
-_movementForceVector (Vector2): a 2D force vector that this Cell will apply to itself when these Flagella are activated
-_positionVector (Vector2): a 2D position vector of these Flagella relative to this Cell's center
-_activationEnergyCost (float): a float defining the amount of energy expended per unit of time while these Flagella are activated
-_activationEnergyThreshold (float): a float that defines the degree of force excerted onto the cell while these Flagella are activated

### Methods
- void activate(CellState *) override: checks whether the CellState passes the activation threshold and that Flagella activation would not fully exert cell energy and if so, activates the Flagella; if there are any activated receptors, the Flagella push toward the sum of their position vectors
- - void modify(String modifierName, float modifierValue): sets relevant attributes based on a modifier Gene name and value; responds to N_SUBSTRUCTURES Genes

- void setMovementForceVector(const Vector2): sets the _movementForceVector to the given value 
- Vector2 getMovementForceVector() const: returns _movementForceVector

- void setPositionVector(const Vector2): sets the _positionVector to the given value
- Vector2 getPositionVector() const: returns _positionVector

- void setActivationEnergyCost(const float): sets the _activationEnergyCost to the given value
- float getActivationEnergyCost() const; returns _activationEnergyCost

- void setActivationEnergyThreshold(const float): sets the _activationEnergyThreshold to the given value
- float getActivationEnergyThreshold() const: returns _activationEnergyThreshold

- void _ready() override: runs once when this object enters the node tree; sets this CellStructure's sprite property to a child Sprite2D node; calls setActivationEnergyThreshold(), setActivationEnergyCost(), setMovementForceVector() for x and y, setCreationNutrientCost(), setCreationEnergyCost(), setMaintenanceNutrientCost() and setMaintenanceEnergyCost() with their respective setting in the Parameters menu within the UI

### Non-Member Functions
None