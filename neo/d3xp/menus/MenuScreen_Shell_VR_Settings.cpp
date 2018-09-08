/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company. 

This file is part of the Doom 3 BFG Edition GPL Source Code ("Doom 3 BFG Edition Source Code").  

Doom 3 BFG Edition Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 BFG Edition Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 BFG Edition Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 BFG Edition Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 BFG Edition Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
#pragma hdrstop
#include "precompiled.h"
#include "../Game_local.h"

const static int NUM_SETTING_OPTIONS = 8;

enum settingMenuCmds_t {
	SETTING_CMD_VR_CHARACTER_OPTIONS,
	SETTING_CMD_VR_SAFETY_PROTOCOLS,
	SETTING_CMD_VR_CONTROL_OPTIONS,
	SETTING_CMD_VR_HAND_OPTIONS,
	SETTING_CMD_VR_VOICE_OPTIONS,
	SETTING_CMD_VR_UI_OPTIONS,
	SETTING_CMD_VR_RENDERING_OPTIONS,
	SETTING_CMD_VR_PROFILE_OPTIONS,
};

/*
========================
idMenuScreen_Shell_VR_Settings::Initialize
========================
*/
void idMenuScreen_Shell_VR_Settings::Initialize( idMenuHandler * data ) {
	idMenuScreen::Initialize( data );

	if ( data != NULL ) {
		menuGUI = data->GetGUI();
	}

	SetSpritePath( "menuSettings" );
	
	options = new (TAG_SWF) idMenuWidget_DynamicList();
	idList< idList< idStr, TAG_IDLIB_LIST_MENU >, TAG_IDLIB_LIST_MENU > menuOptions;	
	idList< idStr > option;

	option.Append( "Character Options" );	
	menuOptions.Append( option );
	option.Clear();
	option.Append( "Comfort Options" );
	menuOptions.Append( option );
	option.Clear();
	option.Append( "Control Options" );
	menuOptions.Append( option );
	option.Clear();
	option.Append( "Hand Options" );
	menuOptions.Append( option );
	option.Clear();
	option.Append( "Voice Options" );
	menuOptions.Append( option );
	option.Clear();
	option.Append( "UI Options" );
	menuOptions.Append( option );
	option.Clear();
	option.Append( "Rendering Options" );
	menuOptions.Append( option );
	option.Clear();
	option.Append( "Profile Options" );
	menuOptions.Append( option );
	option.Clear();
		
	options->SetListData( menuOptions );
	options->SetNumVisibleOptions( NUM_SETTING_OPTIONS );
	options->SetSpritePath( GetSpritePath(), "info", "options" );
	options->SetWrappingAllowed( true );
	AddChild( options );

	idMenuWidget_Help * const helpWidget = new ( TAG_SWF ) idMenuWidget_Help();
	helpWidget->SetSpritePath( GetSpritePath(), "info", "helpTooltip" );
	AddChild( helpWidget );

	const char * tips[] = { "Character Options.", "Comfort & Safety Options.", "Control Options.", "Hand interaction options.", "Control the game by speaking.", "UI Options.", "Rendering Options.", "Profile Options" };

	while ( options->GetChildren().Num() < NUM_SETTING_OPTIONS ) {
		idMenuWidget_Button * const buttonWidget = new (TAG_SWF) idMenuWidget_Button();
		buttonWidget->Initialize( data );
		buttonWidget->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_COMMAND, options->GetChildren().Num() );

		if ( options->GetChildren().Num() < menuOptions.Num() ) {
			buttonWidget->SetDescription( tips[options->GetChildren().Num()] );
		}

		buttonWidget->RegisterEventObserver( helpWidget );
		options->AddChild( buttonWidget );
	}
	options->Initialize( data );

	btnBack = new (TAG_SWF) idMenuWidget_Button();
	btnBack->Initialize( data );	
//	idMenuHandler_Shell * handler = dynamic_cast< idMenuHandler_Shell * >( data );
	
	btnBack->SetLabel( "#str_swf_settings" );
	
	/*if ( handler != NULL && handler->GetInGame() ) {
		btnBack->SetLabel( "#str_swf_settings" ); // "#str_swf_pause_menu"
	} else {
		btnBack->SetLabel( "#str_swf_settings" ); // "#str_02305"
	} */
	
	btnBack->SetSpritePath( GetSpritePath(), "info", "btnBack" );
	btnBack->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_GO_BACK );

	AddChild( btnBack );

	options->AddEventAction( WIDGET_EVENT_SCROLL_DOWN ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_SCROLL_DOWN_START_REPEATER, WIDGET_EVENT_SCROLL_DOWN ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_UP ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_SCROLL_UP_START_REPEATER, WIDGET_EVENT_SCROLL_UP ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_DOWN_RELEASE ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_STOP_REPEATER, WIDGET_EVENT_SCROLL_DOWN_RELEASE ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_UP_RELEASE ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_STOP_REPEATER, WIDGET_EVENT_SCROLL_UP_RELEASE ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_DOWN_LSTICK ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_SCROLL_DOWN_START_REPEATER, WIDGET_EVENT_SCROLL_DOWN_LSTICK ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_UP_LSTICK ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_SCROLL_UP_START_REPEATER, WIDGET_EVENT_SCROLL_UP_LSTICK ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_DOWN_LSTICK_RELEASE ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_STOP_REPEATER, WIDGET_EVENT_SCROLL_DOWN_LSTICK_RELEASE ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_UP_LSTICK_RELEASE ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_STOP_REPEATER, WIDGET_EVENT_SCROLL_UP_LSTICK_RELEASE ) );
}

/*
========================
idMenuScreen_Shell_VR_Settings::Update
========================
*/
void idMenuScreen_Shell_VR_Settings::Update() {

	if ( menuData != NULL ) {
		idMenuWidget_CommandBar * cmdBar = menuData->GetCmdBar();
		if ( cmdBar != NULL ) {
			cmdBar->ClearAllButtons();
			idMenuWidget_CommandBar::buttonInfo_t * buttonInfo;
			buttonInfo = cmdBar->GetButton( idMenuWidget_CommandBar::BUTTON_JOY2 );
			if ( menuData->GetPlatform() != 2 ) {
				buttonInfo->label = "#str_00395";
			}
			buttonInfo->action.Set( WIDGET_ACTION_GO_BACK );

			buttonInfo = cmdBar->GetButton( idMenuWidget_CommandBar::BUTTON_JOY1 );
			if ( menuData->GetPlatform() != 2 ) {
				buttonInfo->label = "#str_SWF_SELECT";
			}
			buttonInfo->action.Set( WIDGET_ACTION_PRESS_FOCUSED );
		}		
	}

	idSWFScriptObject & root = GetSWFObject()->GetRootObject();
	if ( BindSprite( root ) ) {
		idSWFTextInstance * heading = GetSprite()->GetScriptObject()->GetNestedText( "info", "txtHeading" );
		if ( heading != NULL ) {
			//heading->SetText( "#str_swf_settings" );
			heading->SetText( "VR OPTIONS" );
			heading->SetStrokeInfo( true, 0.75f, 1.75f );
		}

		idSWFSpriteInstance * gradient = GetSprite()->GetScriptObject()->GetNestedSprite( "info", "gradient" );
		if ( gradient != NULL && heading != NULL ) {
			gradient->SetXPos( heading->GetTextLength() );
		}
	}

	if ( btnBack != NULL ) {
		btnBack->BindSprite( root );
	}

	idMenuScreen::Update();
}

/*
========================
idMenuScreen_Shell_VR_Settings::ShowScreen
========================
*/
void idMenuScreen_Shell_VR_Settings::ShowScreen( const mainMenuTransition_t transitionType ) {
	idMenuScreen::ShowScreen( transitionType );
}

/*
========================
idMenuScreen_Shell_VR_Settings::HideScreen
========================
*/
void idMenuScreen_Shell_VR_Settings::HideScreen( const mainMenuTransition_t transitionType ) {
	idMenuScreen::HideScreen( transitionType );
}

/*
========================
idMenuScreen_Shell_VR_Settings::HandleAction h
========================
*/
bool idMenuScreen_Shell_VR_Settings::HandleAction( idWidgetAction & action, const idWidgetEvent & event, idMenuWidget * widget, bool forceHandled ) {

	if ( menuData == NULL ) {
		return true;
	}

	if ( menuData->ActiveScreen() != SHELL_AREA_VR_SETTINGS ) {
		return false;
	}

	widgetAction_t actionType = action.GetType();
	const idSWFParmList & parms = action.GetParms();

	switch ( actionType ) {
		case WIDGET_ACTION_GO_BACK: {
			menuData->SetNextScreen( SHELL_AREA_SETTINGS, MENU_TRANSITION_SIMPLE );
			return true;
		}
		case WIDGET_ACTION_COMMAND: {
			switch ( parms[0].ToInteger() ) {
				
				case SETTING_CMD_VR_CHARACTER_OPTIONS: {
					menuData->SetNextScreen( SHELL_AREA_VR_CHARACTER_OPTIONS, MENU_TRANSITION_SIMPLE );
					break;
				}
			
				case SETTING_CMD_VR_SAFETY_PROTOCOLS: {
					menuData->SetNextScreen( SHELL_AREA_VR_SAFETY_PROTOCOLS, MENU_TRANSITION_SIMPLE );
					break;
				}

				case SETTING_CMD_VR_CONTROL_OPTIONS: {
					menuData->SetNextScreen( SHELL_AREA_VR_CONTROL_OPTIONS, MENU_TRANSITION_SIMPLE );
					break;
				}

				case SETTING_CMD_VR_HAND_OPTIONS: {
					menuData->SetNextScreen( SHELL_AREA_VR_HAND_OPTIONS, MENU_TRANSITION_SIMPLE );
					break;
				}
				case SETTING_CMD_VR_VOICE_OPTIONS: {
					menuData->SetNextScreen( SHELL_AREA_VR_VOICE_OPTIONS, MENU_TRANSITION_SIMPLE );
					break;
				}
				case SETTING_CMD_VR_UI_OPTIONS: {
					menuData->SetNextScreen( SHELL_AREA_VR_UI_OPTIONS, MENU_TRANSITION_SIMPLE );
					break;
				}

				case SETTING_CMD_VR_RENDERING_OPTIONS: {
					menuData->SetNextScreen( SHELL_AREA_VR_RENDERING_OPTIONS, MENU_TRANSITION_SIMPLE );
					break;	
				}
				case SETTING_CMD_VR_PROFILE_OPTIONS: {
					menuData->SetNextScreen( SHELL_AREA_VR_PROFILE_OPTIONS, MENU_TRANSITION_SIMPLE );
					break;
				}
				
				
			}

			if ( options != NULL ) {
				int selectionIndex = options->GetViewIndex();
				if ( parms.Num() == 1 ) {
					selectionIndex = parms[0].ToInteger();
				}	

				if ( options->GetFocusIndex() != selectionIndex ) {
					options->SetFocusIndex( selectionIndex );
					options->SetViewIndex( options->GetViewOffset() + selectionIndex );
				}
			}

			return true;
		}
	}

	return idMenuWidget::HandleAction( action, event, widget, forceHandled );
}