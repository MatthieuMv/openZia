/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Windows header
 */

#pragma once

#ifdef SYSTEM_WINDOWS
# ifdef OPENZIA_PRE_WINDOWS_INCLUDE
#  include OPENZIA_PRE_WINDOWS_INCLUDE
# else
#  include <winsock.h>
# endif
# include <Windows.h>
#endif