# Mitochondria Description

## Classes

Mitochondria
Inherits: CellStructure  
Inherited by: none  

Description: the Mitochondria class is a CellStructure that converts nutrients into energy

### Properties
- _activationThreshold (float): the proportion (in [0.0, 1.0]) of nutrients or energy that must be met for the Mitochondria to activate
- _strength (float): a multiplier applied to the conversion between nutrients and energy
- _efficiency (float): the proportion of nutrients that are preserved when converting to energy
- _conversionRate (float): the ratio of energy units to nutrient units at which these Mitochondria convert
- _activationResource (String): the resources to which these Mitochondria "listen" to determine activation; either "energy" or "nutrients"
- _thresholdType (String): the type of the threshold; either "high-pass" or "low-pass"

### Methods
- void activate(CellState *cellState): checks whether the given CellState passes the activation threshold and if so, converts nutrients to energy

- void setActivationThreshold(const float activationThreshold): sets _activationThreshold to the given value if it is in [0.0, 1.0]
- float getActivationThreshold() const: returns _activationThreshold

- void setStrength(const float strength): sets _strength to the given value if it is > 0.0
- float getStrength() const: returns _strength

- void setEfficiency(const float efficiency): sets _efficiency to the given value if it is in [0.0, 1.0]
- float getEfficiency() const: returns _efficiency

- void setConversionRate(const float conversionRate): sets _conversionRate to the given value if it is > 0.0
- float getConversionRate() const: returns _conversionRate

- void setActivationResource(const String activationResource): sets _activationResource to the given value if it is either "energy" or "nutrients"
- String getActivationResource() const: returns _activationResource

- void setThresholdType(const String thresholdType): sets _thresholdType to the given value if it is either "high-pass" or "low-pass"
- String getThresholdType() const: returns _thresholdType

## Non-Member Functions
None