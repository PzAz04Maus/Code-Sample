#include <memory>
#ifdef _DEBUG
#define PRINT_LEAKS _CrtDumpMemoryLeaks();
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#define PRINT_LEAKS
#endif