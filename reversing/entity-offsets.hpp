#include <stdint.h>
#include "../driver/m_driver.hpp"
#include "entity-structs.hpp"
#include "ida.hpp"

enum offsets {
	UWorldd1 = 0x10C628D8,
	PrimaryPickupItemEntry = 0x350,
	levels = 0x178,
	ItemDefinition = 0x18,
	OwningGameInstance = 0x1d8,
	displayname = 0x38,
	tier = 0x13B,
	bIsBot = 0x29a,
	pawn_private = 0x308,
	last_sumbit = 0x2E8,
	last_render = 0x2F0,
	current_wepon = 0xa20,
	weapon_data = 0x4f0,
	btargetedbuild = 0x1710,
	game_state = 0x160,
	kill_score = 0x1264,
	local_player = 0x38,
	player_controller = 0x30,
	ammo_count = 0xe54,
	bisdying = 0x758,
	bisdbno = 0x93a,
	acknowledged_pawn = 0x338,
	skeletal_mesh = 0x318,
	player_state = 0x2b0,
	root_component = 0x198,
	velocity = 0x168,
	relative_location = 0x120,
	relative_rotation = 0x138,
	team_index = 0x1251,
	player_array = 0x2A8,
	component_to_world = 0x1c0,
	bone_array = 0x598,
	pname = 0xaf0,
};

struct UObject {
};

class UActorComponent : UObject {
public:
};


class entity {
public:
	uintptr_t
		entity,
		root_component,
		player_state,
		skeletal_mesh;
	aFortPlayerStateAthena* PawnPrivate;
	aFortPlayerStateAthena* PlayerState;

	int
		team_index,
		kills;
	char
		team_number;
	FVector
		relative_location;
	float
		lastrendertime;
	bool
		is_visible;
};
std::vector<entity> entity_list;
std::vector<entity> temp_list;
