#pragma once

#ifdef DEBUG_ENABLED
#define DONT_RUN_IN_EDITOR                           \
	if (Engine::get_singleton()->is_editor_hint()) { \
		return;                                      \
	}
#else
#define DONT_RUN_IN_EDITOR
#endif