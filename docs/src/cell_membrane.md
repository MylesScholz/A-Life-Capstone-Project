# CellMembrane Description

## Classes

CellMembrane
Inherits: CellStructure  
Inherited by: none

Description: the CellMembrane class is a CellStructure that contains and manages nutrient receptors

### Properties
- _activationThreshold (float): the proportion (in [0.0, 1.0]) of nutrients and energy that must be met for the CellMembrane to activate (which triggers cell growth)
- _receptors (Vector\<Receptor *\>): a dynamic list of references to the current Receptors in/under this CellMembrane
- _activatedReceptors (Vector\<Receptor *\>): a dynamic list of references to the currently activated Receptors in/under this CellMembrane

### Methods
- void activate(CellState *cellState): updates the given CellState's _receptorVectors field with a list of position vectors of the currently activated Receptors in/under this CellMembrane; if the given CellState meets the activation threshold, emits a cell growth signal
- void _on_receptor_activated(Receptor *receptor): a signal callback function that adds the signalling Receptor to _activatedReceptors (if not already there)
- void _on_receptor_deactivated(Receptor *receptor): a signal callback function that removes the signalling Receptor from _activatedReceptors (if there)
- void setActivationThreshold(const float activationThreshold): sets _activationThreshold to the given value if it is in [0.0, 1.0]
- float getActivationThreshold(): returns _activationThreshold
- Vector\<Receptor *\> getReceptors(): returns _receptors
- void createReceptors(const int nReceptors): creates and adds nReceptors receptors to this CellMembrane
- void removeReceptors(const int nReceptors): removes nReceptors receptors from this CellMembrane
- Vector\<Receptor *\> getActivatedReceptors(): returns _activatedReceptors
- void _ready() override: runs once when this object is created and ready to use; sets this CellStructure's sprite property to a child Sprite2D node

## Non-Member Functions
None
