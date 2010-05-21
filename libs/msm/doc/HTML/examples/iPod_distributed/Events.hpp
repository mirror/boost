#ifndef EVENTS_HPP
#define EVENTS_HPP

//flags 
struct MenuActive{};
// hardware-generated events
struct Hold {};
struct NoHold {};
struct SouthPressed {};
struct SouthReleased {};
struct MiddleButton {};
struct EastPressed{};
struct EastReleased{};
struct Off {};
struct MenuButton {};

// internally used events
struct PlayPause {};
struct EndPlay {};
struct CloseMenu 
{
	template<class EVENT>
	CloseMenu(EVENT const &) {}
};
struct OnOffTimer {};
struct MenuMiddleButton {};
struct SelectSong {};
struct SongFinished {};
struct StartSong 
{
	StartSong (int song_index):m_Selected(song_index){}
	int m_Selected;
};
struct PreviousSong{};
struct NextSong{};
struct NextSongDerived : public NextSong{};
struct ForwardTimer{};
struct PlayingMiddleButton{};

#endif // EVENTS_HPP
