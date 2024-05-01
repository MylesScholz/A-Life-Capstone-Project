# NutrientZone Description

## Classes

NutrientZone
Inherits: Area2D  
Inherited by: none

Description: The NutrientZone object represents a location within the simulation that stores nutrients that are able to be consumed and used by cells

### Properties
- _totalNutrients (float): the amount of nutrients that are currently within the zone
- _nutrientMaximum (float): the maximum amount of nutrients that can be within the zone
- _feedingRate (float): the main element that can be set to dermine how much a cell can get from a zone in one run of the _process function
- _regenerationRate (float): multiplied by delta and then used to increase _totalNutrients by that amount
- _feedingCells (Vector<Cell *>): an array that stores all of the cells that are currently in the zone
- _deleteOnEmpty (bool): if true the NutrientZone will remove itself upon running out of nutrients, otherwise it will remain onscreen

### Methods
- void _on_body_entered(Node *): puts cells into _feedingCells array when entering the zone

- void _on_body_exited(Node *): takes cells out of _feedingCells array when exiting the zone

- void applyScale(const float): applies a linear scaling to the NutrientZone; updates the Sprite2D and CollisionShape2D

- float incrementTotalNutrients(const float): increases _totalNutrients by a number, if result is less than 0 or greater than _nutrientMaximum set to respective bound

- void setTotalNutrients(const float): sets _totalNutrients to a number if it is greater than zero
- float getTotalNutrients() const: returns _totalNutrients

- void setNutrientMaximum(const float): if greater or equal 0 sets _nutrientMaximum to the float
- float getNutrientMaximum() const: returns _nutrientMaximum

- void setFeedingRate(const float): if greater than 0 sets _feedingRate to the float
- float getFeedingRate() const: returns _feedingRate

- void setRegenerationRate(const float): if greater or equal 0 sets _regenerationRate to the float
- float getRegenerationRate() const: returns _regenerationRate

- void setDeleteOnEmpty(const bool): sets _deleteOnEmpty to the bool
- bool getDeleteOnEmpty() const: returns _deleteOnEmpty

- void _ready(): runs once when this object enters the node tree; connects body_entered and body_exited signals with _on_body_entered and _on_body_exited functions; gets sprite; removes itself if spawned with no nutrients

- void _process(float): runs once per in-game frame; delta stores the real time since the last frame, will be set to 0 when sim is paused; regenerates nutrients based on _regenerationRate and increases nutrients of cells in the zone/_feedingCells based on the _feedingRate and NutrientZone scale split evenly between all cells; the total nutrients given is then removed from the NutrientZone

## Non-Member Functions
None