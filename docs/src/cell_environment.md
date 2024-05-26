# CellEnvironment Description

## Classes

CellEnvironment
Inherits: Area2D  
Inherited by: none

Description: the habitat in which the cells live; contains living Cells, manages NutrientZones, and keeps the LineageGraph

### Properties
- _nNutrientZones (int): the number of NutrientZones to spawn
- _nutrientZoneScene (Ref<PackedScene>): a reference to a Godot scene containing a NutrientZone, from which the NutrientZones are spawned
- _lineageGraph (LineageGraph): the graph structure for the current simulation containing all Cells, living and dead, and their parent-child relationships

### Methods
- void spawnNutrientZone(): creates a randomly placed and sized NutrientZone in the environment
- void removeAllNutrientZones(): deletes all NutrientZones in the environment

- int GetAliveCount(): returns the number of living Cells currently in the environment
- int GetNutrientZoneCount(): returns the number of NutrientZones currently in the environment

- void setNutrientZoneScene(const Ref<PackedScene> nutrientZoneScene): sets _nutrientZoneScene to the given value
- Ref<PackedScene> getNutrientZoneScene() const: returns _nutrientZoneScene

- void setNNutrientZones(const int nNutrientZones): sets _nNutrientZones to the given value if it is in (0, 50]
- int getNNutrientZones() const: returns _nNutrientZones

- void addCell(Cell *cell): adds the given Cell to the environment
- void removeCell(Cell *cell): removes the given Cell from the environment
- LineageGraph *getLineageGraph(): returns _lineageGraph

- void _on_cell_death(Cell *cell): handles the given Cell's death, including freezing it, storing it, and spawning a NutrientZone in its place if it has remaining nutrients

- void _ready(): runs once when the CellEnvironment enters the node tree; sets _nNutrientZones to the value specified in the Parameters menu

## Non-Member Functions
None
