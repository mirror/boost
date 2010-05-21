#ifndef MENU_MODE_HPP
#define MENU_MODE_HPP

#include <iostream>
#include <boost/any.hpp>

#include "Events.hpp"
#include <boost/msm/back/favor_compile_time.hpp>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

using namespace std;
namespace msm = boost::msm;

struct MenuMode_ : public msm::front::state_machine_def<MenuMode_>
{
	typedef mpl::vector1<MenuActive>		flag_list;
	struct WaitingForSongChoice : public msm::front::state<>
	{
		template <class Event,class FSM>
		void on_entry(Event const&,FSM& ) {std::cout << "starting: MenuMode::WaitingForSongChoice" << std::endl;}
		template <class Event,class FSM>
		void on_exit(Event const&,FSM& ) {std::cout << "finishing: MenuMode::WaitingForSongChoice" << std::endl;}
	};
	struct StartCurrentSong : public msm::front::state<>
	{
		template <class Event,class FSM>
		void on_entry(Event const&,FSM& ) {std::cout << "starting: MenuMode::StartCurrentSong" << std::endl;}
		template <class Event,class FSM>
		void on_exit(Event const&,FSM& ) {std::cout << "finishing: MenuMode::StartCurrentSong" << std::endl;}
	};
	struct MenuExit : public msm::front::exit_pseudo_state<CloseMenu>
	{
		template <class Event,class FSM>
		void on_entry(Event const&,FSM& ) {std::cout << "starting: MenuMode::WaitingForSongChoice" << std::endl;}
		template <class Event,class FSM>
		void on_exit(Event const&,FSM& ) {std::cout << "finishing: MenuMode::WaitingForSongChoice" << std::endl;}
	};
	typedef WaitingForSongChoice initial_state;
	typedef MenuMode_ fsm; // makes transition table cleaner
	// Transition table for player
	struct transition_table : mpl::vector2<
		//     Start                 Event           Next                Action				   Guard
		//    +---------------------+------------------+-------------------+---------------------+----------------------+
		_row < WaitingForSongChoice , MenuMiddleButton , StartCurrentSong                                               >,
		_row < StartCurrentSong     , SelectSong       , MenuExit                                                       >
		//    +---------------------+------------------+-------------------+---------------------+----------------------+
	> {};
};
typedef msm::back::state_machine<MenuMode_> MenuMode;

#endif
