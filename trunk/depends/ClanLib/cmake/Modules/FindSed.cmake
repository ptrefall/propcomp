###
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#
# Note: Some of the libraries Totem EDK may link to may have additional
# requirements or restrictions.
#
###
# CMake system for Totem EDK was contributed by Jacob 'jacmoe' Moen
#
###

#FIND_PATH(SED_DIR bin/sed.h
#      D:/Development/3rdParty/sed/sed-4.2.1
#    )
INCLUDE(FindCygwin)
FIND_PROGRAM(SED_EXECUTABLE
	NAMES
		sed
	PATHS
		${CYGWIN_INSTALL_PATH}/bin
		/bin
		/usr/bin
		/usr/local/bin
		/sbin
		D:/Development/3rdParty/sed/sed-3.62
		D:/Development/3rdParty/sed/sed-4.2.1
)

# handle the QUIETLY and REQUIRED arguments and set SED_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SED DEFAULT_MSG SED_EXECUTABLE)

MARK_AS_ADVANCED(SED_EXECUTABLE)
	