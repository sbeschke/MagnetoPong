#include <ClanLib/core.h>
#include <ClanLib/application.h>

class ConsoleProgram
{
public:
   static int main(const std::vector<CL_String> &args)
   {
       CL_SetupCore setup_core;
       CL_ConsoleWindow console_window("Console", 80, 200);

       CL_String now = CL_DateTime::get_current_local_time().to_short_datetime_string();

       CL_Console::write_line("At %1, we say Hello ClanLib!", now);
       CL_Console::wait_for_key();

       return 0;
   }
};

// Create global application object, you MUST include this line or
// the application start-up will fail to locate your application object.
CL_ClanApplication app(&ConsoleProgram::main);
