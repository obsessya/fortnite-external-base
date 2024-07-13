#include <memory>
#include <vector>
#include "../reversing/entity-vectors.hpp"


struct WeaponInformation
{
	int32_t ammo_count;
	int32_t max_ammo;

	BYTE tier;
	std::string weapon_name;
	std::string buildplan;

};
std::string LocalPlayerWeapon;


WeaponInformation WeaponInfo;

class item {
public:
	uintptr_t
		Actor;

	std::string
		Name,
		isVehicle,
		isChest,
		isLamma,
		isPickup,
		isAmmoBox;
	float
		distance;
};
std::vector<item> item_pawns;

typedef struct _LootEntity {
	std::string GNames;
	uintptr_t ACurrentItem;
}LootEntity;

static std::vector<LootEntity> LootentityList;

namespace o {
	class p
	{
	public:
		uintptr_t
			uworld,
			game_instance,
			game_state,
			local_player,
			player_controller,
			acknowledged_pawn,
			skeletal_mesh,
			player_state,
			root_component,
			player_array;
		int
			team_index,
			player_array_size;
		FVector
			relative_location,
			velocity;

		std::uintptr_t Array;
		std::uintptr_t Get(std::uint32_t Index)
		{
			return pmem64->read<std::uintptr_t>(Array + (Index * 0x8));
		}
	};
} static o::p* entity_pointers = new o::p();


