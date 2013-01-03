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
**    Harry Storbacka
**    Kenneth Gangstoe
*/

/// \addtogroup clanDisplay_Display clanDisplay Display
/// \{

#pragma once

#include "../api_display.h"
#include <memory>
#include "../../Core/IOData/virtual_directory.h"
#include "graphic_context.h"
#include "uniform_vector.h"

namespace clan
{

class ShaderObject;
class ProgramAttribute;
class ProgramUniform;
class ProgramObject_Impl;
class GraphicContext;
class GraphicContextProvider;
class ResourceManager;
class ProgramObjectProvider;

/// \brief Program Object
///
///    <p>The shader objects that are to be used by programmable stages of
///    OpenGL are collected together to form a program object. ProgramObject
///    is ClanLib's C++ interface to OpenGL program objects.</p>
///    <p>To construct a program object programatically, the procedure is
///    as follows:</p>
///    <pre>
///    ShaderObject vertex_shader(shadertype_vertex, vertex_glsl_sourcecode);
///    ShaderObject fragment_shader(shadertype_fragment, fragment_glsl_sourcecode);
///    ProgramObject program;
///    program.attach(vertex_shader);
///    program.attach(fragment_shader);
///    program.link();
///    </pre>
///    <p>For more information about program objects, see the OpenGL 2.0
///    specification at <a href="http://www.opengl.org">www.opengl.org</a>. Documentation
///    about the OpenGL Shader Language (GLSL) is also available from www.opengl.org.</p>
/// \xmlonly !group=Display/Display! !header=display.h! \endxmlonly
class CL_API_DISPLAY ProgramObject
{
/// \name Construction
/// \{
public:
	/// \brief Construct a null instance
	ProgramObject();

	/// \brief Constructs a ProgramObject
	///
	/// \param gc = Graphic Context
	ProgramObject(GraphicContext &gc);

	/// \brief Constructs a ProgramObject
	///
	/// \param gc_provider = Graphic Context Provider
	ProgramObject(GraphicContextProvider *gc_provider);

	/// \brief Constructs a ProgramObject
	///
	/// \param provider = Font Provider
	ProgramObject(ProgramObjectProvider *provider);

	/// \brief Load
	///
	/// \param gc = Graphic Context
	/// \param resource_id = String Ref
	/// \param resman = Resource Manager
	///
	/// \return Program Object
	static ProgramObject load(GraphicContext &gc, const std::string &resource_id, ResourceManager *resman);

	/// \brief Load
	///
	/// \param gc = Graphic Context
	/// \param vertex_fullname = String Ref
	/// \param fragment_fullname = String Ref
	///
	/// \return Program Object
	static ProgramObject load(GraphicContext &gc, const std::string &vertex_fullname, const std::string &fragment_fullname);

	/// \brief Load
	///
	/// \param gc = Graphic Context
	/// \param vertex_fullname = String Ref
	/// \param geometry_fullname = String Ref
	/// \param fragment_fullname = String Ref
	///
	/// \return Program Object
	static ProgramObject load(GraphicContext &gc, const std::string &vertex_fullname, const std::string &geometry_fullname, const std::string &fragment_fullname);

	/// \brief Load
	///
	/// \param gc = Graphic Context
	/// \param vertex_filename = String Ref
	/// \param fragment_filename = String Ref
	/// \param directory = Virtual Directory
	///
	/// \return Program Object
	static ProgramObject load(GraphicContext &gc, const std::string &vertex_filename, const std::string &fragment_filename, const VirtualDirectory &directory);

	/// \brief Load
	///
	/// \param gc = Graphic Context
	/// \param vertex_filename = String Ref
	/// \param geometry_filename = String Ref
	/// \param fragment_filename = String Ref
	/// \param directory = Virtual Directory
	///
	/// \return Program Object
	static ProgramObject load(GraphicContext &gc, const std::string &vertex_filename, const std::string &geometry_filename, const std::string &fragment_filename, const VirtualDirectory &directory);

	/// \brief Load
	///
	/// \param gc = Graphic Context
	/// \param vertex_file = IODevice
	/// \param fragment_file = IODevice
	///
	/// \return Program Object
	static ProgramObject load(GraphicContext &gc, IODevice &vertex_file, IODevice &fragment_file);

	/// \brief Load
	///
	/// \param gc = Graphic Context
	/// \param vertex_file = IODevice
	/// \param geometry_file = IODevice
	/// \param fragment_file = IODevice
	///
	/// \return Program Object
	static ProgramObject load(GraphicContext &gc, IODevice &vertex_file, IODevice &geometry_file, IODevice &fragment_file);

	/// \brief Load and link
	///
	/// \param gc = Graphic Context
	/// \param vertex_fullname = String Ref
	/// \param fragment_fullname = String Ref
	///
	/// \return Program Object
	static ProgramObject load_and_link(GraphicContext &gc, const std::string &vertex_fullname, const std::string &fragment_fullname);

	/// \brief Load and link
	///
	/// \param gc = Graphic Context
	/// \param vertex_fullname = String Ref
	/// \param geometry_fullname = String Ref
	/// \param fragment_fullname = String Ref
	///
	/// \return Program Object
	static ProgramObject load_and_link(GraphicContext &gc, const std::string &vertex_fullname, const std::string &geometry_fullname, const std::string &fragment_fullname);

	/// \brief Load and link
	///
	/// \param gc = Graphic Context
	/// \param vertex_filename = String Ref
	/// \param fragment_filename = String Ref
	/// \param directory = Virtual Directory
	///
	/// \return Program Object
	static ProgramObject load_and_link(GraphicContext &gc, const std::string &vertex_filename, const std::string &fragment_filename, const VirtualDirectory &directory);

	/// \brief Load and link
	///
	/// \param gc = Graphic Context
	/// \param vertex_filename = String Ref
	/// \param geometry_filename = String Ref
	/// \param fragment_filename = String Ref
	/// \param directory = Virtual Directory
	///
	/// \return Program Object
	static ProgramObject load_and_link(GraphicContext &gc, const std::string &vertex_filename, const std::string &geometry_filename, const std::string &fragment_filename, const VirtualDirectory &directory);

	/// \brief Load and link
	///
	/// \param gc = Graphic Context
	/// \param vertex_file = IODevice
	/// \param fragment_file = IODevice
	///
	/// \return Program Object
	static ProgramObject load_and_link(GraphicContext &gc, IODevice &vertex_file, IODevice &fragment_file);

	/// \brief Load and link
	///
	/// \param gc = Graphic Context
	/// \param vertex_file = IODevice
	/// \param geometry_file = IODevice
	/// \param fragment_file = IODevice
	///
	/// \return Program Object
	static ProgramObject load_and_link(GraphicContext &gc, IODevice &vertex_file, IODevice &geometry_file, IODevice &fragment_file);

	virtual ~ProgramObject();
/// \}

/// \name Attributes
/// \{
public:
	/// \brief Returns true if this object is invalid.
	bool is_null() const { return !impl; }

	/// \brief Throw an exception if this object is invalid.
	void throw_if_null() const;

	/// \brief Retrieves the provider.
	ProgramObjectProvider *get_provider() const;

	/// \brief Returns the OpenGL program object handle.
	unsigned int get_handle() const;

	/// \brief Returns the shaders attached to the program object.
	std::vector<ShaderObject> get_shaders() const;

	/// \brief Returns the current info log for the program object.
	std::string get_info_log() const;

	/// \brief Returns the count of active attributes.
	int get_attribute_count() const;

	/// \brief Returns the active attributes.
	std::vector<ProgramAttribute> get_attributes() const;

	/// \brief Returns the location of a named active attribute.
	int get_attribute_location(const std::string &name) const;

	/// \brief Returns the count of active uniform variables.
	int get_uniform_count() const;

	/// \brief Returns the active uniforms.
	std::vector<ProgramUniform> get_uniforms() const;

	/// \brief Returns the location of a named uniform variable.
	int get_uniform_location(const std::string &name) const;

	/// \brief Get the uniform block size
	///
	/// An exception is thrown of block_name was not found
	int get_uniform_buffer_size(const std::string &block_name) const;

	/// \brief Get the uniform block size
	int get_uniform_buffer_size(int block_index) const;

	/// \brief Get the uniform block index
	///
	/// Returns -1 when the block index was not found
	int get_uniform_buffer_index(const std::string &block_name) const;

	/// \brief Get the storage buffer index
	///
	/// Returns -1 when the block index was not found
	int get_storage_buffer_index(const std::string &name) const;
/// \}

/// \name Operations
/// \{
public:
	/// \brief Equality operator
	bool operator==(const ProgramObject &other) const;

	/// \brief Add shader to program object.
	void attach(const ShaderObject &obj);

	/// \brief Remove shader from program object.
	void detach(const ShaderObject &obj);

	/// \brief Bind attribute to specific location.
	/** <p>This function must be called before linking.</p>*/
	void bind_attribute_location(int index, const std::string &name);

	/// \brief Bind shader out variable a specific color buffer location.
	/** <p>This function must be called before linking.</p>*/
	void bind_frag_data_location(int color_number, const std::string &name);

	/// \brief Link program.
	/** <p>If the linking fails, get_info_log() will return the link log.</p>*/
	bool link();

	/// \brief Validate program.
	/** <p>If the validation fails, get_info_log() will return the validation log.</p>*/
	bool validate();

	/// \brief Set uniform variable(s).
	///
	/// \param name = String Ref
	/// \param value_a = value
	void set_uniform1i(const std::string &name, int value_a);

	/// \brief Set uniform variable(s).
	///
	/// \param location = Location from get_uniform_location()
	/// \param value_a = value
	void set_uniform1i(int location, int value_a);

	/// \brief Sets the UniformBuffer
	void set_uniform_buffer_index(const std::string &block_name, int bind_index);

	/// \brief Sets the UniformBuffer
	void set_uniform_buffer_index(int block_index, int bind_index);

	/// \brief Sets the UniformBuffer
	void set_storage_buffer_index(const std::string &block_name, int bind_index);

	/// \brief Sets the UniformBuffer
	void set_storage_buffer_index(int block_index, int bind_index);
/// \}

/// \name Implementation
/// \{
private:
	std::shared_ptr<ProgramObject_Impl> impl;
/// \}
};

}

/// \}
