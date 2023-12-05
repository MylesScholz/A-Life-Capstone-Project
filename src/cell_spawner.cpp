#include "cell_spawner.hpp"
#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void CellSpawner::_bind_methods(){
    ClassDB::bind_method(D_METHOD("get_num_cells"), &CellSpawner::getNumCells);
    ClassDB::bind_method(D_METHOD("set_num_cells","num_cells"), &CellSpawner::setNumCells);
    ClassDB::add_property("CellSpawner",PropertyInfo(Variant::INT,"num_cells"),"set_num_cells","get_num_cells");

    ClassDB::bind_method(D_METHOD("get_cell_scene"), &CellSpawner::getCellScene);
    ClassDB::bind_method(D_METHOD("set_cell_scene","cell_scene"), &CellSpawner::setCellScene);
    ClassDB::add_property("CellSpawner",PropertyInfo(Variant::OBJECT, "cell_scene"), "set_cell_scene", "get_cell_scene");

    ClassDB::bind_method(D_METHOD("get_min_force"), &CellSpawner::getMinForce);
    ClassDB::bind_method(D_METHOD("set_min_force","min_force"), &CellSpawner::setMinForce);
    ClassDB::add_property("CellSpawner",PropertyInfo(Variant::INT, "min_force"), "set_min_force", "get_min_force");

    ClassDB::bind_method(D_METHOD("get_max_force"), &CellSpawner::getMaxForce);
    ClassDB::bind_method(D_METHOD("set_max_force","max_force"), &CellSpawner::setMaxForce);
    ClassDB::add_property("CellSpawner",PropertyInfo(Variant::INT, "max_force"), "set_max_force", "get_max_force");
}

CellSpawner::CellSpawner(){
    rand.instantiate();
}
CellSpawner::~CellSpawner(){}

void CellSpawner::setCellScene(const Ref<PackedScene> cellScene){
    _cellScene = cellScene;
}
Ref<PackedScene> CellSpawner::getCellScene() const{
    return _cellScene;
}

void CellSpawner::setNumCells(const int numCells){
    _numCells = numCells;
}
int CellSpawner::getNumCells() const {
    return _numCells;
}

void CellSpawner::setMinForce(const float minForce) {
    _minForce = minForce;
}
float CellSpawner::getMinForce() const {
    return _minForce;
}

void CellSpawner::setMaxForce(const float maxForce) {
    _maxForce = maxForce;
}
float CellSpawner::getMaxForce() const {
    return _maxForce;
}

void CellSpawner::spawnCell(){
    Node* cell = _cellScene->instantiate();
    Size2 viewportSize = get_viewport()->get_visible_rect().size;
    Size2 cellSize = cell->get_node<Sprite2D>("Sprite")->get_rect().size;
    
    Object::cast_to<Cell>(cell)->set_position(Vector2(rand->randi_range(cellSize.x/4, viewportSize.x - cellSize.x/4),
        rand->randi_range(cellSize.y/4, viewportSize.y - cellSize.y/4)));

    add_child(cell);
}

void CellSpawner::_ready(){
     // Don't run if in editor
    if(Engine::get_singleton()->is_editor_hint()) 
        return;
    
    for(int i=0; i<_numCells; ++i) 
        spawnCell();
}