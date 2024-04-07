# CellMembrane Description

## Classes

CellMembrane
Inherits: CellStructure  
Inherited by: none

Description: the CellMembrane class is a CellStructure that contains and manages nutrient Receptors

### Properties
- _activationThreshold (float): the proportion (in [0.0, 1.0]) of nutrients and energy that must be met for the CellMembrane to activate (which triggers cell growth)
- _nReceptors (int): the number of Receptors in this CellMembrane
- _receptors (Vector\<Receptor *\>): a dynamic list of references to the current Receptors in this CellMembrane
- _activatedReceptors (Vector\<Receptor *\>): a dynamic list of references to the currently activated Receptors in this CellMembrane

### Methods
- void activate(CellState *cellState): updates the given CellState's _receptorVectors field with a list of position vectors of the currently activated Receptors in this CellMembrane; if the given CellState meets the activation threshold, emits a cell growth signal
- modify(String modifierName, float modifierValue): sets relevant attributes based on a modifier Gene name and value; responds to N_SUBSTRUCTURES Genes
- applyScale(const float scale): applies a given linear scaling to this CellMembrane's Sprite2D, CollisionShape2D, and Receptors

- void _on_receptor_activated(Receptor *receptor): a signal callback function that adds the signalling Receptor to _activatedReceptors (if not already there)
- void _on_receptor_deactivated(Receptor *receptor): a signal callback function that removes the signalling Receptor from _activatedReceptors (if there)

- void setActivationThreshold(const float activationThreshold): sets _activationThreshold to the given value if it is in [0.0, 1.0]
- float getActivationThreshold(): returns _activationThreshold

- void setNReceptors(const int nReceptors): sets _nReceptors to the given value and updates the Receptors
- int getNReceptors(): returns _nReceptors

- Vector\<Receptor *\> getReceptors(): returns _receptors
- Vector\<Receptor *\> getActivatedReceptors(): returns _activatedReceptors

- void _ready() override: runs once when this object is created and ready to use; sets this CellStructure's sprite property to a child Sprite2D node

- void _rearrangeReceptors(): resets the position, rotation, and scaling of each Receptor in _receptors

- void _createReceptor(): instantiates a single Receptor, adds it as a child of this CellMembrane, and connects its signals
- void _createReceptors(const int nReceptors): creates and adds nReceptors Receptors to this CellMembrane, rearranging all Receptors to accommodate
- void _removeReceptor(): deletes a single Receptor from this CellMembrane
- void _removeReceptors(const int nReceptors): removes nReceptors Receptors from this CellMembrane and rearranges the remaining Receptors

- void _updateReceptors(): creates or removes Receptors in this CellMembrane to match _nReceptors

## Non-Member Functions
None
