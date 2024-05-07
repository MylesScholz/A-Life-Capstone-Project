# Ribosomes Description

## Classes

Ribosomes
Inherits: CellStructure  
Inherited by: none  

Description: the Ribosomes class is a CellStructure that converts energy into nutrients

### Properties
- _activationThreshold (float): the proportion (in [0.0, 1.0]) of nutrients or energy that must be met for the Ribosomes to activate
- _strength (float): a multiplier applied to the conversion between energy and nutrients
- _efficiency (float): the proportion of energy that is preserved when converting to nutrients
- _preferredConversionRate (float): the ratio of nutrients to energy that these Ribosomes will try to set as the conversion rate of the Cell
- _activationResource (String): the resources to which these Ribosomes "listen" to determine activation; either "energy" or "nutrients"
- _thresholdType (String): the type of the threshold; either "high-pass" or "low-pass"

### Methods
- void activate(CellState *cellState): checks whether the given CellState passes the activation threshold and if so, converts energy to nutrients; if the CellState's _nutrientEnergyConversionRate is unset, it will be set to _preferredConversionRate
- - void modify(String modifierName, float modifierValue): sets relevant attributes based on a modifier Gene name and value; responds to ACTIVATION_THRESHOLD, STRENGTH, CONVERSION_RATE, ACTIVATION_RESOURCE, and THRESHOLD_TYPE Genes

- void setActivationThreshold(const float activationThreshold): sets _activationThreshold to the given value if it is in [0.0, 1.0]
- float getActivationThreshold() const: returns _activationThreshold

- void setStrength(const float strength): sets _strength to the given value if it is > 0.0
- float getStrength() const: returns _strength

- void setEfficiency(const float efficiency): sets _efficiency to the given value if it is in [0.0, 1.0]
- float getEfficiency() const: returns _efficiency

- void setPreferredConversionRate(const float preferredConversionRate): sets _preferredConversionRate to the given value if it is > 0.0
- float getPreferredConversionRate() const: returns _preferredConversionRate

- void setActivationResource(const String activationResource): sets _activationResource to the given value if it is either "energy" or "nutrients"
- String getActivationResource() const: returns _activationResource

- void setThresholdType(const String thresholdType): sets _thresholdType to the given value if it is either "high-pass" or "low-pass"
- String getThresholdType() const: returns _thresholdType

- void _ready() override: runs once when this object enters the node tree; sets this CellStructure's sprite property to a child Sprite2D node

## Non-Member Functions
None
