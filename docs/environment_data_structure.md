# Environment Data Structure
```
CellSpawner (Node): an invisible node that instantiates Cells in the Environment once at the beginning of the simulation
│
├──Environment (Node2D): a container node for all elements within the simulation
│  │
│  ├──Cell (RigidBody2D): an organism in the Environment; see /docs/cell_data_structure.md for details
│  │  │
│  │  └──...
│  │
│  ├──NutrientZone (Area2D): a region in the Environment that provides nutrients to intersecting Cells
│  │  │
│  │  ├──_feedingCells (Vector<Cell *>): a list of references to all Cells currently being fed by this NutrientZone
│  │  │
│  │  ├──_on_body_entered(Node): if the intersecting Node is a Cell, begin feeding it nutrients by adding it to _feedingCells
│  │  │
│  │  ├──_on_body_exited(Node): if the exiting Node is a Cell, stop feeding it nutrients by removing it from _feedingCells
│  │  │
│  │  ├──_process(float): add nutrients to all Cells referenced in _feedingCells
│  │  │
│  │  └──...
│  │
│  ├──Obstacle (CollisionShape2D): impassable barriers in the environment to break up the space
│  │  │
│  │  ├──Sprite2D: a graphical representation of the Obstacle; the shape of the sprite should match the collision shape
│  │  │
│  │  └──...
│  │
│  ├──ViewportBoundaries (StaticBody2D): a collection of impassable barriers that define the edges of the Environment
│  │  │
│  │  ├──<Left/Right/Top/Bottom>EdgeBoundary (CollisionShape2D): an impassable barrier that defines the <Left/Right/Top/Bottom> edge of the Environment
│  │  │
│  │  └──...
│  │
│  └──...
│
└──...
```