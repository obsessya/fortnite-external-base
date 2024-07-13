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

class uSceneComponent : UActorComponent {
public:
	uintptr_t componentvelocity( ) {

		FVector Component = pmem64->read <FVector> ( entity_pointers -> root_component + offsets::velocity );

		entity_pointers->velocity = Component;

		if (Component)
			return 0;
	}
	
	FVector relativelocation( ) {

		FVector RelativeLoc = pmem64->read <FVector> ( entity_pointers -> root_component + offsets::root_component );

		entity_pointers->relative_location = RelativeLoc;

		if (RelativeLoc)
			return entity_pointers->relative_location;
	}
	
}; static uSceneComponent* USceneComponent = new uSceneComponent();

class UPrimitiveComponent : uSceneComponent {
public:
};

class UMeshComponent : UPrimitiveComponent {
public:
};

class aActor : UObject {
public:
	uintptr_t RootComponent( ) {

		uintptr_t RootComp = pmem64->read <uintptr_t> ( entity_pointers -> acknowledged_pawn + offsets::root_component);

		entity_pointers -> root_component = RootComp;

		return 0;
	}
}; static aActor* AActor = new aActor();

class USkinnedMeshComponent : UMeshComponent {
public:

};

struct USkeletalMeshComponent : USkinnedMeshComponent {

};

class AInfo : aActor {
public:

};

class AController: aActor{
public:
};

class UDataAsset : UObject {
public:
};

class UPrimaryDataAsset : UDataAsset {
public:
};

class UMcpItemDefinitionBase : UPrimaryDataAsset {
public:
};

class FText {
public:

};

class UFortItemDefinition : UMcpItemDefinitionBase {
public:

};

class UFortWorldItemDefinition : UFortItemDefinition {
public:
};

class UFortWeaponItemDefinition : UFortWorldItemDefinition {
public:
};

class AFortWeapon : aActor {
public:
	
};

class APawn : aActor {
public:

};

class APlayerState : AInfo {
public:
	

};

class AFGF_PlayerState : APlayerState {
public:

};

class AFortPlayerState : AFGF_PlayerState {
public:
};

class AFortPlayerStateZone : AFortPlayerState {
public:

};

class aFortPlayerStateAthena : AFortPlayerStateZone {
public:
	char TeamIndex() {
		char TeamID = pmem64->read<char>(entity_pointers->player_state + offsets::team_index);
		entity_pointers->team_index = TeamID;
		if (TeamID)
			return 0;
	}

}; static aFortPlayerStateAthena* AFortPlayerStateAthena = new aFortPlayerStateAthena();

class aCharacter : public APawn {
public:
	uintptr_t SkeletalMesh() {
		uintptr_t Mesh = pmem64->read<uintptr_t>(entity_pointers->acknowledged_pawn + offsets::skeletal_mesh);
		entity_pointers->skeletal_mesh = Mesh;
		if (Mesh)
			return 0;
	}
	
	uintptr_t PlayerState() {
		uintptr_t PlayerS = pmem64->read<uintptr_t>(entity_pointers->acknowledged_pawn + offsets::player_state);
		entity_pointers->player_state = PlayerS;
		if (PlayerS)
			return 0;
	}


}; static aCharacter* ACharacter = new aCharacter();

struct AFGF_Character : aCharacter {

};

struct AFortPawn : AFGF_Character {

};

struct AFortPlayerPawn : AFortPawn {

};

struct AFortPlayerPawnAthena : AFortPlayerPawn {


};

class aPlayerController : AController {
public:
	uintptr_t Acknowledgedpawn() {
		uintptr_t LocalPawn = pmem64->read<uintptr_t>(entity_pointers->player_controller + offsets::acknowledged_pawn);
		entity_pointers->acknowledged_pawn = LocalPawn;
		if (LocalPawn)
			return 0;
	}
	
}; static aPlayerController* APlayerController = new aPlayerController();

struct AFGF_PlayerController : aPlayerController {


};

struct AFortPlayerController : AFGF_PlayerController {

};

class uPlayer : UObject {
public:
	uintptr_t PlayerController() {
		uintptr_t playerc = pmem64->read<uintptr_t>(entity_pointers->local_player + offsets::player_controller);
		entity_pointers->player_controller = playerc;
		if (playerc)
			return 0;
	}

}; static uPlayer* UPlayer = new uPlayer();

struct ULocalPlayer : uPlayer {

};

struct UFortGenericRecord : UObject {

};

struct UFortClientSettingsRecord : UFortGenericRecord {
	
};

struct UFortLocalPlayer : ULocalPlayer {
	
};

//class UGameInstance : UObject {
//	UFortLocalPlayer* LocalPlayer() {
//		uintptr_t LocalPlayers = pmem64->read<uintptr_t>(current_address + offsets::local_player);
//		if (LocalPlayers) {
//			return pmem64->read<UFortLocalPlayer*>(LocalPlayers);
//		}
//		return nullptr;
//	}
//};

class aGameStateBase : AInfo {
public:
	uintptr_t PlayerArray() {
		uintptr_t pa = pmem64->read<uintptr_t>(entity_pointers->game_state + offsets::player_array);
		entity_pointers->player_array = pa;
		if (pa)
			return 0;
	}

}; aGameStateBase* AGameStateBase = new aGameStateBase();

class uGameInstance {
public:
	uintptr_t LocalPlayer() {
		uintptr_t LocalPlayers = pmem64->read<uintptr_t>( pmem64->read <uintptr_t>( entity_pointers -> game_instance + offsets::local_player ) );
		entity_pointers -> local_player = LocalPlayers;
		if ( LocalPlayers )
			return 0;
	}
}; static uGameInstance* UGameInstance = new uGameInstance();


struct UWorldd : UObject {

	uintptr_t Uworld( ) {
		uintptr_t uworld = pmem64->read<uintptr_t>(module::image_base + offsets::UWorldd1);
		entity_pointers->uworld = uworld;
		if (uworld)
			return 0;

	}

	uintptr_t GameInstance() {
		uintptr_t GameI = pmem64->read<uintptr_t>(entity_pointers->uworld + offsets::OwningGameInstance);
		entity_pointers->game_instance = GameI;

		if (GameI)
			return 0;
	}

	uintptr_t GameState() {
		uintptr_t GameS = pmem64->read<uintptr_t>(entity_pointers->uworld + offsets::game_state);
		entity_pointers->game_state = GameS;

		if ( GameS )
			return 0;
	}

}; static UWorldd* UWorld = new UWorldd();

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