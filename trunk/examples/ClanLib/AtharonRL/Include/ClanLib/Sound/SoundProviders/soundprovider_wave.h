/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

/// \addtogroup clanSound_Sound_Providers clanSound Sound Providers
/// \{

#pragma once

#include "../api_sound.h"
#include "soundprovider.h"
#include "../../Core/IOData/virtual_directory.h"

namespace clan
{

class InputSourceProvider;
class SoundProvider_Wave_Impl;

/// \brief Windows WAVE sample format (.wav) sound provider.
///
/// \xmlonly !group=Sound/Sound Providers! !header=sound.h! \endxmlonly
class CL_API_SOUND SoundProvider_Wave : public SoundProvider
{
/// \name Construction
/// \{

public:
	/// \brief Constructs a sound provider based on a Windows wave (.wav) file.
	///
	/// \param filename Filename of wave file.
	/// \param provider Input source provider used to retrieve wave file.
	/// \param stream If true, will stream from disk. If false, will load it to memory.
	SoundProvider_Wave(
		const std::string &filename,
		const VirtualDirectory &directory,
		bool stream = false);

	SoundProvider_Wave(
		const std::string &fullname,
		bool stream = false);

	SoundProvider_Wave(
		IODevice &file,
		bool stream = false);

	virtual ~SoundProvider_Wave();

/// \}
/// \name Operations
/// \{

public:
	/// \brief Called by SoundBuffer when a new session starts.
	/** \return The soundbuffer session to be attached to the newly started session.*/
	virtual SoundProvider_Session *begin_session();

	/// \brief Called by SoundBuffer when a session has finished. After this call,
	/** <p>SoundBuffer will not access the session anymore. It can safely be deleted
	    here (and in most cases should be delete here).</p>*/
	virtual void end_session(SoundProvider_Session *session);

/// \}
/// \name Implementation
/// \{

private:
	std::shared_ptr<SoundProvider_Wave_Impl> impl;

	friend class SoundProvider_Wave_Session;
/// \}
};

}

/// \}
