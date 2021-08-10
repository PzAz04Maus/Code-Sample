/* * * * * * * *
* Stephen Carter
* main.cpp
*
* Created 20APR21
* No modifications
*
* Lab 3: Freecell
* Overview:
*   The program is a game object that initializes, instances, interprets, and manages a session of freecell.
* INPUT:
*   Player gives the game instructions through integer inputs across the lifespan of the game
* OUTPUT:
*   Outputs all information and results to console
 * * * * * * * */
#define DOCTEST_CONFIG_IMPLEMENT
#define _CRTDBG_MAP_ALLOC
#include "memdebug.h"

#include <io.h>
#include <fcntl.h>
#include <string>
#include "Game.h"

#include "doctest.h"

#include <crtdbg.h>

int testGame();
int unitTests(int argc, char** argv);

int main(int argc, char** argv) {

    // INITIALIZE LEAK REPORT AT EXIT AND WRITE IN CONSOLE WINDOW
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);


    int tests = 0;
    tests = testGame();
    //tests = unitTests(argc, argv);

    
    return tests; // the result from doctest is propagated here as well
}

int testGame()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::wcout << "Testing unicode -- English -- Ελληνικά -- Español." << std::endl;
    //fflush(nullptr);
    std::wcout << L"Initializing game.\n";
    Game* newgame = new Game();
    newgame->begin();

    delete newgame;

    return 0;
}

int unitTests(int argc, char** argv)
{
    // Setup DocTest and run the tests
    doctest::Context context;


    context.setOption("abort-after", 1);              // stop test execution after 1 failed assertions
    context.applyCommandLine(argc, argv);
    int res = context.run(); // run

    if (context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests


    // your program - if the testing framework is integrated in your production code
    int client_stuff_return_code = 0;
    return res + client_stuff_return_code; // the result from doctest is propagated here as well
}