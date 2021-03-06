/*
 * Copyright 2010-2021 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ExtendedGeoscapeLinksState.h"
#include "FundingState.h"
#include "GeoscapeState.h"
#include "../Engine/Game.h"
#include "../Engine/Action.h"
#include "../Engine/Options.h"
#include "../Engine/LocalizedText.h"
#include "../Engine/Unicode.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Interface/TextButton.h"
#include "../Menu/NotesState.h"
#include "../Menu/TestState.h"
#include "../Mod/Mod.h"
#include "../Savegame/SavedGame.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the ExtendedGeoscapeLinksState screen.
 */
ExtendedGeoscapeLinksState::ExtendedGeoscapeLinksState(GeoscapeState* parent) : _parent(parent)
{
	_screen = false;
	int dY = 0;

	// Create objects
	_window = new Window(this, 256, 180, 32, 10, POPUP_BOTH);
	_txtTitle = new Text(220, 17, 50, 33);
	_btnOk = new TextButton(220, 12, 50, 167);
	if (_game->getMod()->getIsFTAGame())
	{
		dY = 26;
	}
	_btnFunding = new TextButton(220, 12, 50, 50);
	_btnTechTree = new TextButton(220, 12, 50, 63);
	_btnGlobalResearch = new TextButton(220, 12, 50, 76 - dY);
	_btnGlobalProduction = new TextButton(220, 12, 50, 89 - dY);
	_btnUfoTracker = new TextButton(220, 12, 50, 102 - dY);
	_btnPilotExp = new TextButton(220, 12, 50, 115 - dY);
	_btnNotes = new TextButton(220, 12, 50, 128 - dY);
	_btnMusic = new TextButton(220, 12, 50, 141 - dY);
	_btnTest = new TextButton(220, 12, 50, 154 - dY);

	// Set palette
	setInterface("oxceGeoLinks");

	add(_window, "window", "oxceGeoLinks");
	add(_txtTitle, "text", "oxceGeoLinks");
	add(_btnOk, "button", "oxceGeoLinks");

	add(_btnFunding, "button", "oxceGeoLinks");
	add(_btnTechTree, "button", "oxceGeoLinks");
	add(_btnGlobalResearch, "button", "oxceGeoLinks");
	add(_btnGlobalProduction, "button", "oxceGeoLinks");
	add(_btnUfoTracker, "button", "oxceGeoLinks");
	add(_btnPilotExp, "button", "oxceGeoLinks");
	add(_btnNotes, "button", "oxceGeoLinks");
	add(_btnMusic, "button", "oxceGeoLinks");
	add(_btnTest, "button", "oxceGeoLinks");

	centerAllSurfaces();

	// Set up objects
	setWindowBackground(_window, "oxceGeoLinks");

	_txtTitle->setBig();
	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setText(tr("STR_EXTENDED_LINKS"));

	_btnOk->setText(tr("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnOkClick);
	_btnOk->onKeyboardPress((ActionHandler)&ExtendedGeoscapeLinksState::btnOkClick, Options::keyCancel);

	_btnFunding->setText(_game->getMod()->getIsFTAGame() ? tr("STR_GRAPHS") : tr("STR_FUNDING_UC"));
	_btnFunding->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnFundingClick);

	std::string tmp = tr("STR_TECH_TREE_VIEWER");
	Unicode::upperCase(tmp);
	_btnTechTree->setText(tmp);
	_btnTechTree->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnTechTreeClick);

	if (_game->getMod()->getIsFTAGame()) // #FINNIKTODO: temporal solution, before graphs and global covert operations states would be done
	{
		_btnFunding->setVisible(false);
		_btnTechTree->setVisible(false);
	}

	_btnGlobalResearch->setText(tr("STR_RESEARCH_OVERVIEW"));
	_btnGlobalResearch->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnGlobalResearchClick);

	_btnGlobalProduction->setText(tr("STR_PRODUCTION_OVERVIEW"));
	_btnGlobalProduction->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnGlobalProductionClick);

	tmp = tr("STR_UFO_TRACKER");
	Unicode::upperCase(tmp);
	_btnUfoTracker->setText(tmp);
	_btnUfoTracker->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnUfoTrackerClick);

	tmp = tr("STR_DAILY_PILOT_EXPERIENCE");
	Unicode::upperCase(tmp);
	_btnPilotExp->setText(tmp);
	_btnPilotExp->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnPilotExpClick);

	tmp = tr("STR_NOTES");
	Unicode::upperCase(tmp);
	_btnNotes->setText(tmp);
	_btnNotes->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnNotesClick);

	tmp = tr("STR_SELECT_MUSIC_TRACK");
	Unicode::upperCase(tmp);
	_btnMusic->setText(tmp);
	_btnMusic->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnMusicClick);

	_btnTest->setText(tr("STR_TEST_SCREEN"));
	_btnTest->onMouseClick((ActionHandler)&ExtendedGeoscapeLinksState::btnTestClick);
	_btnTest->setVisible(_game->getSavedGame()->getDebugMode());
}

void ExtendedGeoscapeLinksState::btnFundingClick(Action *)
{
	_game->popState();
	_game->pushState(new FundingState);
}

void ExtendedGeoscapeLinksState::btnTechTreeClick(Action *)
{
	_game->popState();
	_parent->btnTechTreeViewerClick(nullptr);
}

void ExtendedGeoscapeLinksState::btnGlobalResearchClick(Action *)
{
	_game->popState();
	_parent->btnGlobalResearchClick(nullptr);
}

void ExtendedGeoscapeLinksState::btnGlobalProductionClick(Action *)
{
	_game->popState();
	_parent->btnGlobalProductionClick(nullptr);
}

void ExtendedGeoscapeLinksState::btnUfoTrackerClick(Action *)
{
	_game->popState();
	_parent->btnUfoTrackerClick(nullptr);
}

void ExtendedGeoscapeLinksState::btnPilotExpClick(Action *)
{
	_game->popState();
	_parent->btnDogfightExperienceClick(nullptr);
}

void ExtendedGeoscapeLinksState::btnNotesClick(Action *)
{
	_game->popState();
	_game->pushState(new NotesState(OPT_GEOSCAPE));
}

void ExtendedGeoscapeLinksState::btnMusicClick(Action *)
{
	_game->popState();
	_parent->btnSelectMusicTrackClick(nullptr);
}

void ExtendedGeoscapeLinksState::btnTestClick(Action *)
{
	_game->popState();
	_game->pushState(new TestState);
}

/**
 * Returns to the previous screen.
 * @param action Pointer to an action.
 */
void ExtendedGeoscapeLinksState::btnOkClick(Action *)
{
	_game->popState();
}

}
