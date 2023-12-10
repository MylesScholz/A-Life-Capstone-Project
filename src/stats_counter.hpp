#pragma once

#include <godot_cpp/classes/Engine.hpp>
#include <godot_cpp/classes/Label.hpp>

namespace godot {

  class StatsCounter : public Label { 
  	GDCLASS(StatsCounter, Label) 
  
  protected:
      static void _bind_methods();
  
  public:
      StatsCounter();
      ~StatsCounter();
  
      void _process(double delta) override;
  };

}
