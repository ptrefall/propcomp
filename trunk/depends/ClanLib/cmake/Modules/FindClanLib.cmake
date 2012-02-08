
FIND_PATH(CL_DIR include/ClanLib/core.h
      D:/Development/3rdParty/ClanLib
    )

FIND_PATH(CL_INCLUDE_PATH ClanLib/core.h
      D:/Development/3rdParty/ClanLib/include
    )
	
FIND_LIBRARY(CL_CORE_LIB_RELEASE
	NAMES clanCore-static-mt
    PATHS D:/Development/3rdParty/ClanLib/Lib/Win32
    )

FIND_LIBRARY(CL_CORE_LIB_DEBUG
	NAMES clanCore-static-mt-debug
    PATHS D:/Development/3rdParty/ClanLib/Lib/Win32
    )
	
FIND_LIBRARY(CL_NET_LIB_RELEASE
	NAMES clanNetwork-static-mt
    PATHS D:/Development/3rdParty/ClanLib/Lib/Win32
    )

FIND_LIBRARY(CL_NET_LIB_DEBUG
	NAMES clanNetwork-static-mt-debug
    PATHS D:/Development/3rdParty/ClanLib/Lib/Win32
    )
	
FIND_LIBRARY(CL_ZLIB_LIB_RELEASE
	NAMES zlib-static-mt
    PATHS D:/Development/3rdParty/ClanLib/Lib/Win32
    )

FIND_LIBRARY(CL_ZLIB_LIB_DEBUG
	NAMES zlib-static-mt-debug
    PATHS D:/Development/3rdParty/ClanLib/Lib/Win32
    )
