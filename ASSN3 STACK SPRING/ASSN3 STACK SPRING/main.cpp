/* Assignment 3: Stacks */
/* * * * * * * * * * * * * *
Overview:
    This implementation unit tests 2 types of stacks.
    The types are an array and linked list based ADT.
    Dummy data is provided as <int> templated classes, operations are unit tested.
 * * * * * * * * * * * * * */
#define DOCTEST_CONFIG_IMPLEMENT
#define _CRTDBG_MAP_ALLOC

#include "doctest.h"
#include "memdebug.h"
#include <crtdbg.h>

int main(int argc, char** argv) {
    // INITIALIZE LEAK REPORT AT EXIT AND WRITE IN CONSOLE WINDOW
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    // Setup DocTest and run the tests
    doctest::Context context;
    context.setOption("abort-after", 1);              // stop test execution after 1 failed assertions
    context.applyCommandLine(argc, argv);
    int res = context.run(); // run
    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests


    // your program - if the testing framework is integrated in your production code
    int client_stuff_return_code = 0;
   

    return res + client_stuff_return_code; // the result from doctest is propagated here as well
}
