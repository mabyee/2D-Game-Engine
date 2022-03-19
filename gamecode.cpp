// GameCode.cpp		
#include "gamecode.h"
#include "myinputs.h"
#include <time.h>
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "enemy.h"
#include "ObjectManager.h"
#include "brickwall.h"
#include "SoundFX.h"
#include "computer.h"
#include "HUD.h"
#include "ammoBox.h"

Game::Game()
{
   // No-op
}

Game::~Game()
{
   // No-op
}

Game Game::instance;    // Singleton instance

// This is repeated, called every frame.
// It will run either Update( ), MainMenu() or PauseMenu() depending on the
// game state
ErrorType Game::Main()

{
	//Flip and clear the back buffer
	MyDrawEngine* pTheDrawEngine= MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err=SUCCESS;

	switch(m_currentState)
	{
	case MENU:

		err= MainMenu();     // Menu at start of game
		break;
	case PAUSED:
		err = PauseMenu();   // Player has paused the game
		break;
	case RUNNING:           // Playing the actual game
		err= Update();
		break;
   case GAMEOVER:
		err = FAILURE;       // Error return causes the window loop to exit
	default:
		// Not a valid state
		err = FAILURE;       // Error return causes the window loop to exit
	}

	return err;
}

// Use to change the state of the game. Private function
void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	}
}

// Starts the game engines - Draw Engine, Sound Engine, Input Engine - singletons
// This is called soon after the program runs
ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
{
	// Create the engines - this should be done before creating other DDraw objects
	if(FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	if(FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if(FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	return (SUCCESS);
}



// Terminates the game engines - Draw Engine, Sound Engine, Input Engine
// This is called just before the program exits
void Game::Shutdown()

{
   // Any clean up code here 


	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}

// **********************************************************************************************
// Placeholder menus  ***************************************************************************
// **********************************************************************************************

// Called each frame when in the pause state. Manages the pause menu
// which is currently a basic placeholder
ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu

	MyDrawEngine::GetInstance()->WriteText(450,220, L"Paused", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = {L"Resume", L"Main menu"};

   // Display menu options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

   // Get user input
	pInputs->SampleKeyboard();

   // Move choice up and down
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // If player chooses an option ....
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)      // Resume
		{
			ChangeState(RUNNING);  // Go back to running the game
		}
		if(m_menuOption ==1)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(MENU);     // Go back to the menu
		}

	}

	return SUCCESS;
}

// Called each frame when in the menu state. Manages the menu
// which is currently a basic placeholder
ErrorType Game::MainMenu()
{
	MyDrawEngine::GetInstance()->WriteText(450,220, L"Main menu", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][15] = {L"Start game", L"Exit"};

   // Display the options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
	}

   // Get keyboard input
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // User selects an option
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)          // Play
		{  
			StartOfGame();             // Initialise the game
			ChangeState(RUNNING);      // Run it
		}

		if(m_menuOption ==1)          //Quit
		{
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}


// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************


// Called at the start of the game - when changing state from MENU to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame()
{
   // Code to set up your game *********************************************
   // **********************************************************************

	pTheSoundFX = new SoundFX();
	pTheSoundFX->LoadSounds();
	
	BrickWall* pBrickWall = new BrickWall();
	Spaceship* pShip = new Spaceship();

	// creating walls ----------------------------------------------------------------------------------------
	// TODO, FIND BETTER WAY OF HANDLING THIS
	int numberRows = 23;
	int numberCol = 37;
	const int TILES = 851; //851 = amount of tiles on map, 37 columns by 23 rows
	float ang = 0.0f;
	int j = 0;
	int spawnCounter = 0;
	Vector2D pos;
	Vector2D initialArr[TILES]; 
	Vector2D endArr[TILES];
	Vector2D spawnArr[TILES];
	
	// Filling initialArr with every possible tile on the map
	for (int i = -1600; i < 1600; i = i + BLOCK_SIZE) //width
	{
		for (int k = -1000; k < 1000; k = k + BLOCK_SIZE) //height
		{
			if ((i <= -200 || i >= 200) || (k <= -200 || k >= 200)) // leaving middle of map blank
			{
				initialArr[j] = Vector2D(i, k);
			}
			j++;
		}
	}

	// Deciding where to place walls
	endArr[0] = initialArr[0];
	for (int i = 0; i < TILES;i++) //loop through entire initialArr
	{
		int n = rand() % 3 + 1; // 33% chance of creating a wall
		if (n == 1)
		{
			endArr[i] = initialArr[i];
		}
		else
		{
			spawnArr[spawnCounter] = initialArr[i];
			spawnCounter++;
		}
	}

	for (int i = 0; i < TILES; i++)
	{
		if (endArr[i] == Vector2D(0, 0))
		{
		}
		else
		{ //if the wall does not have a wall next to it, delete it
			if (endArr[i].XValue == endArr[i + 1].XValue || endArr[i].YValue == endArr[i + numberRows].YValue || endArr[i].YValue == endArr[i - numberRows].YValue || endArr[i].XValue == endArr[i - 1].XValue)
			{
			}
			else
			{
				endArr[i] = Vector2D(0, 0);
			}
		}
	}

	// Placing walls where vector != (0,0)
	for (int i = 0; i < TILES; i++)
	{
		if (endArr[i] == Vector2D(0, 0))
		{
		}
		else
		{
			BrickWall* pBrickWall = new BrickWall();
			pos = endArr[i];
			ang = 0.0f;
			pBrickWall->Initialise(pos, ang);
			ObjectManager.AddObject(pBrickWall);
		}
	}

	//float ang;
	//Vector2D pos;
	//for (int i = 0; i < 20; i++)
	//{
	//	BrickWall* pBrickWall = new BrickWall();
	//	pos.set(-500 + i * 44, 0);
	//	ang = 0.0f;
	//	pBrickWall->Initialise(pos, ang);
	//	ObjectManager.AddObject(pBrickWall);
	//}
	//for (int i = 0; i < 14; i++)
	//{
	//	BrickWall* pBrickWall = new BrickWall();
	//	pos.set(380, 0 + i * 44);
	//	ang = 0.0f;
	//	pBrickWall->Initialise(pos, ang);
	//	ObjectManager.AddObject(pBrickWall);
	//}
	//for (int i = 0; i < 6; i++)
	//{
	//	BrickWall* pBrickWall = new BrickWall();
	//	pos.set(380+i*44, 616);
	//	ang = 0.0f;
	//	pBrickWall->Initialise(pos, ang);
	//	ObjectManager.AddObject(pBrickWall);
	//}
	//for (int i = 0; i < 6; i++)
	//{
	//	BrickWall* pBrickWall = new BrickWall();
	//	pos.set(-500, 44 + i * 44);
	//	ang = 0.0f;
	//	pBrickWall->Initialise(pos, ang);
	//	ObjectManager.AddObject(pBrickWall);
	//}
	//for (int i = 0; i < 10; i++)
	//{
	//	BrickWall* pBrickWall = new BrickWall();
	//	pos.set(-500 + i * 44, 308);
	//	ang = 0.0f;
	//	pBrickWall->Initialise(pos, ang);
	//	ObjectManager.AddObject(pBrickWall);
	//}

	// finished creating walls ------------------------------------------------------------------------------

	// spawning enemies
	for (int i = 0; i < 5; i++)
	{
		Enemy* pRock = new Enemy();
		Vector2D pos;
		Vector2D vel;
		pos = spawnArr[rand() % 350]; // random available spawn point
		vel.setBearing(rand() % 628 / 100.0f, rand() % 100 + 100);
		pRock->Initialise(pos, vel, &ObjectManager, pTheSoundFX);
		ObjectManager.AddObject(pRock);
	}

	//spawn computer
	//computer* pComputer = new computer();
	//pComputer->Initialise(Vector2D(50,50),1.0f,1.0f,Vector2D(0,0));

	Vector2D startPos(0, 0);
	pShip->Initialise(startPos, &ObjectManager, pTheSoundFX);

	// spawning ammo boxes
	for (int i = 0; i < 3; i++)
	{
		ammoBox* pAmmoBox = new ammoBox();		
		Vector2D pos;
		pos = spawnArr[rand() % 350]; // random available spawn point
		pAmmoBox->Initialise(pos, &ObjectManager);
		ObjectManager.AddObject(pAmmoBox);
	}
	

	HUD* pHUD = new HUD();
	pHUD->Initialise();

	//ObjectManager.AddObject(pComputer);
	ObjectManager.AddObject(pBrickWall);
	ObjectManager.AddObject(pHUD);
	ObjectManager.AddObject(pShip);

	gt.mark();
	gt.mark();

	return SUCCESS;
}

// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	// Check for entry to pause menu
	static bool escapepressed = true;
	if(KEYPRESSED(VK_ESCAPE))
	{
		if(!escapepressed)
			ChangeState(PAUSED);
		escapepressed=true;
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->StopAllSounds(); //stop all sounds when entering menu
	}
	else
		escapepressed=false;

	
   // Your code goes here *************************************************
   // *********************************************************************

	gt.mark();

	ObjectManager.RenderAll();
	ObjectManager.UpdateAll(gt.mdFrameTime);
	ObjectManager.DeleteInactiveObjects();
	ObjectManager.CheckAllCollisions();
   
	// *********************************************************************
   // *********************************************************************

	return SUCCESS;
}

// Called when the player ends the game
// Currently this is done from the PAUSED state, when returning to the main menu
// but could be done by the gameplay programmer in other situations
// This will be used by the gameplay programmer to clean up
ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
   // Add code here to tidy up ********************************************
   // *********************************************************************
	
	delete pTheSoundFX;
	ObjectManager.DeleteAll();
	return SUCCESS;
}

