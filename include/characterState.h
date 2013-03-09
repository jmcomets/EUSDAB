//-----------file characterState.h----------//
//ceci est l'etat général dont les autres hériteront

#ifndef CHARACTER_STATE_H_INCLUDED_
#define CHARACTER_STATE_H_INCLUDED_

//includes

class CharacterState
{
	protected:
	character myCharacter;
	view myView;

	public:
	enum Id {};
	view();
	enter();
	leave();
	update();
}
