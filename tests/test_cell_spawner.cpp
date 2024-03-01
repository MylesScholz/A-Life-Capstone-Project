#include "test_header.hpp"

#include "cell_spawner.hpp"

#include <godot_cpp/classes/object.hpp>

using namespace godot;

TEST_CASE("Test CellSpawner") {
	CellSpawner CellSpawner{};

	REQUIRE(CellSpawner.getMinForce() == 50.0);
	REQUIRE(CellSpawner.getMaxForce() == 150.0);

	SUBCASE("Test setting min force") {
		CellSpawner.setMinForce(40.0);
		CHECK(CellSpawner.getMinForce() == 40.0);

		CellSpawner.setMinForce(CellSpawner.getMaxForce() + 1);
		CHECK(CellSpawner.getMinForce() == CellSpawner.getMaxForce());
	}

	SUBCASE("Test setting max force") {
		CellSpawner.setMaxForce(160.0);
		CHECK(CellSpawner.getMaxForce() == 160.0);

		CellSpawner.setMaxForce(CellSpawner.getMinForce() - 1);
		CHECK(CellSpawner.getMaxForce() == CellSpawner.getMinForce());
	}
}