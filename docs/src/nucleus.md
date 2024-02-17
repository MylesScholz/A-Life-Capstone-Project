# Nucleus Description

## Classes

Nucleus
Inherits: CellStructure  
Inherited by: none

Description: the Nucleus class is CellStructure that manages reproduction

### Properties
- _reproductionNutrientThreshold (float): the proportion of nutrients that must be met for the Nucleus to begin reproduction

### Methods
- void activate(CellState *cellState) override: an unfinished activation function that should begin cell reproduction if the threshold is met

- void setReproductionNutrientThreshold(const float reproductionNutrientThreshold): sets _reproductionNutrientThreshold to the given value if it is > 0.0
- float getReproductionNutrientThreshold() const: returns _reproductionNutrientThreshold

## Non-Member Functions
None
