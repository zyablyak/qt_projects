#include "second_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool SecondLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* SecondLevel::get_next() {
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_ship({60, 20}, 10, 7);
	ui_factory->create_ship({80, 25}, 20, 2);
	ui_factory->create_ship({120, 20}, 10, 7);
	ui_factory->create_ship({150, 25}, 40, 2);
	ui_factory->create_ship({210, 20}, 10, 7);

	ui_factory->create_enemy({25, 10}, 3, 2);      
	ui_factory->create_enemy({80, 10}, 3, 2);      
	ui_factory->create_enemy({65, 10}, 3, 2);      
	ui_factory->create_enemy({120, 10}, 3, 2);     
	ui_factory->create_enemy({160, 10}, 3, 2);    

	ui_factory->create_ship({210, 20}, 10, 7);
	ui_factory->create_finish({210, 15}, 10, 10);
}
