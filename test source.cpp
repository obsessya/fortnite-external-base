#include "driver/m_defines.hpp"
#include <thread>
#include "stdafx/stdafx.hpp"
#include "threads/entity-thread.hpp"

int main()
{
    pmem64->init( );

    printinfo("", FOREGROUND_GREEN); std::cout << ("welcome to project smv.") << std::endl;

    game_context = get_process_id( L"FortniteClient-Win64-Shipping.exe" );

    while ( windows == NULL )  {  XorS(wind, "Fortnite  ");   windows = FindWindowA(0, wind.decrypt());  }

    if ( game_context ) { printdbg ("", FOREGROUND_INTENSITY); std::cout << ( "found fortnite with pid -> 00000000000" ) << game_context << endl; }

    if (!pmem64->update ( game_context ) ) { printfailure("", FOREGROUND_RED); cout << ( "couldnt update fortnite's pid." ) << endl;; }

    if ( ! utils -> is_driver_loaded ( ) ) {  }

    if ( module::image_base ) { printdbg ("", FOREGROUND_INTENSITY); std::cout << ( "connected to driver with handle 000" ) << module::image_base << endl; }

    threads->Actors_call();

    cin.get();
}

