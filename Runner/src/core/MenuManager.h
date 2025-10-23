#pragma once



class MenuManager 
{
public:

	MenuManager();
	~MenuManager();

	void openMenu();

protected:


private:

	enum class State {
		MAIN_MENU,
		IN_GAME,
		WIN,
		GAME_OVER,
		PAUSE
	};

};