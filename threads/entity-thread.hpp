#include "../stdafx/stdafx.hpp"
#include "../reversing/entity-offsets.hpp"
#

class Actor {
public:

	static auto Actors_call( ) -> void { std::thread([&]() { for (;; ) { Actors_thread( ); } }).detach(); }

	static auto Actors_thread() -> void {

	
			temp_list.clear( );

			UWorld->Uworld( );

			UWorld->GameInstance( );

			UGameInstance->LocalPlayer( );

			UPlayer->PlayerController( );

			APlayerController->Acknowledgedpawn( );

			ACharacter->SkeletalMesh( );

			ACharacter->PlayerState( );

			AActor->RootComponent( );

			USceneComponent->relativelocation( );

			AFortPlayerStateAthena->TeamIndex( );

			UWorld->GameState( );

			AGameStateBase->PlayerArray( );

			std::cout << ("\n [+] Uworld -> ") << entity_pointers->uworld;
			std::cout << ("\n [+] Game Instance -> ") << entity_pointers->game_instance;
			std::cout << ("\n [+] local player -> ") << entity_pointers->local_player;
			std::cout << ("\n [+] player_controller -> ") << entity_pointers->player_controller;
			std::cout << ("\n [+] Acknowledgedpawn -> ") << entity_pointers->acknowledged_pawn;
			std::cout << ("\n [+] Mesh -> ") << entity_pointers->skeletal_mesh;
			std::cout << ("\n [+] PlayerState -> ") << entity_pointers->player_state;
			std::cout << ("\n [+] RootComponent -> ") << entity_pointers->root_component;
			std::cout << ("\n [+] relativelocation -> ") << entity_pointers->relative_location;
			std::cout << ("\n [+] TeamIndex -> ") << entity_pointers->team_index;
			std::cout << ("\n [+] GameState -> ") << entity_pointers->game_state;
			std::cout << ("\n [+] PlayerArray -> ") << entity_pointers->player_array;

			for (int i = 0; i < entity_pointers->player_array_size; i++) {
				
				
				//to do
			}

			entity_list.clear();

			this_thread::sleep_for(chrono::milliseconds(150));
				
	}
}; static Actor* threads = new Actor();