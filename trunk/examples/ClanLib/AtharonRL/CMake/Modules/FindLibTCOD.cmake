FIND_PATH(TCOD_DIR LibTCOD/libtcod.hpp
      ${CMAKE_SOURCE_DIR}/Include/
    )

FIND_LIBRARY(TCOD_LIBRARY
  NAMES libtcod-VS
  PATHS ${CMAKE_SOURCE_DIR}/Lib/Win32/
    )
	
FIND_LIBRARY(TCOD_GUI_LIBRARY
  NAMES libtcod-gui-VS
  PATHS ${CMAKE_SOURCE_DIR}/Lib/Win32/
    )
