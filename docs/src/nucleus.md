# Nucleus Description

## Classes

Nucleus
Inherits: CellStructure  
Inherited by: none

Description: the Nucleus class is CellStructure that manages reproduction

### Properties
- _reproductionNutrientThreshold (float): the quantity of nutrients that must be met for the Nucleus to begin reproduction
- _reproductionEnergyThreshold (float): the quantity of energy that must be met for the Nucleus to begin reproduction

### Methods
- void activate(CellState *cellState) override: an activation function that begins cell reproduction if the nutrient and energy thresholds are met and the Cell has sufficient resources
- void modify(String modifierName, float modifierValue): sets relevant attributes based on a modifier Gene name and value; responds to ACTIVATION_THRESHOLD Genes

- void setReproductionNutrientThreshold(const float reproductionNutrientThreshold): sets _reproductionNutrientThreshold to the given value if it is > 0.0
- float getReproductionNutrientThreshold() const: returns _reproductionNutrientThreshold

- void setReproductionEnergyThreshold(const float reproductionNutrientThreshold): sets _reproductionEnergyThreshold to the given value if it is > 0.0
- float getReproductionEnergyThreshold() const: returns reproductionEnergyThreshold

- void _ready() override: runs once when this object enters the node tree; sets this CellStructure's sprite property to a child Sprite2D node

## Non-Member Functions
None
