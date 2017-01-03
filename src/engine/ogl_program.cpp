#include <vector>

#include <GL/glew.h>

#include <mage/exception.hpp>
#include <mage/engine/shader.hpp>
#include <mage/engine/exception.hpp>

Mage::Program::Shader::Shader(ShaderType t) :
m_hasSource(false), m_isCompiled(false)
{
	m_handle = glCreateShader(static_cast<GLenum>(t));
}

Mage::Program::Shader::Shader(Shader&& rhs)
{
	m_handle = rhs.m_handle;
	m_hasSource = rhs.m_hasSource;
	m_isCompiled = rhs.m_isCompiled;

	rhs.m_handle = 0;
}

Mage::Program::Shader& Mage::Program::Shader::operator=(Shader&& rhs)
{
	if (this != &rhs)
	{
		m_handle = rhs.m_handle;
		m_hasSource = rhs.m_hasSource;
		m_isCompiled = rhs.m_isCompiled;

		rhs.m_handle = 0;
	}

	return *this;
}

Mage::Program::Shader::~Shader()
{
	glDeleteShader(m_handle);
}

void Mage::Program::Shader::add_source(const char* src)
{
	if (m_hasSource) return;

	glShaderSource(m_handle, 1, &src, nullptr);
	m_hasSource = true;

	auto err = glGetError();
	if (err)
	{
		throw OGLException("Could not add shader source", err);
	}
}

void Mage::Program::Shader::compile()
{
	if (m_isCompiled) return;

	glCompileShader(m_handle);

	auto err = glGetError();
	if (err)
	{
		throw OGLException("Could not compile shader", err);
	}
	
	// Were we succesful?
	GLint result = 200;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &result);
	
	err = glGetError();
	if (err)
	{
		throw OGLException("Could not get shader error log", err);
	}


	if (!result)
	{
		GLint logSize;
		std::string log;
		glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &logSize);
		glGetShaderInfoLog(m_handle, logSize, &logSize, &log[0]);

		throw Mage::OGLException(log);
	}

	m_isCompiled = true;
}

Mage::Program::Program() :
m_handle(glCreateProgram()), m_isLinked(false)
{
	// do nothing...
}

Mage::Program::~Program()
{
	if (m_isLinked) {
		glDeleteProgram(m_handle);
	}
}

void Mage::Program::add_shader_source(const std::string& src, ShaderType t)
{
	Shader s(t);
	s.add_source(src.c_str());

	switch (t)
	{
	case ShaderType::Fragment:
		m_frag = std::move(s);
		break;

	case ShaderType::Vertex:
		m_vertex = std::move(s);
		break;

	case ShaderType::Geometry:
		m_geom = std::move(s);
		break;

	case ShaderType::TessellationControl:
		m_tessControl = std::move(s);
		break;

	case ShaderType::TessellationEvaluation:
		m_tessEval = std::move(s);
		break;

	default:
		throw Exception("Invalid shader type");
	}
}

void Mage::Program::link()
{
	if (m_isLinked) return;

	if (!m_frag && !m_vertex)
	{
		throw Exception("Can't link a shader without a fragment and vertex shader");
	}

	m_frag->compile();
	m_vertex->compile();

	glAttachShader(m_handle, m_frag->get_handle());
	glAttachShader(m_handle, m_vertex->get_handle());

	if (m_geom)
	{
		m_geom->compile();
		glAttachShader(m_handle, m_geom->get_handle());
	}

	if (m_tessEval && m_tessControl)
	{
		m_tessEval->compile();
		m_tessControl->compile();
		glAttachShader(m_handle, m_tessEval->get_handle());
		glAttachShader(m_handle, m_tessControl->get_handle());
	}

	GLenum err = glGetError();
	if (err)
	{
		throw OGLException("Could not attach shaders", err);
	}

	glLinkProgram(m_handle);

	// Detach shaders from the program.
	glDetachShader(m_handle, m_frag->get_handle());
	glDetachShader(m_handle, m_vertex->get_handle());

	if (m_geom)
	{
		glDetachShader(m_handle, m_geom->get_handle());
	}

	if (m_tessEval && m_tessControl)
	{
		glDetachShader(m_handle, m_tessEval->get_handle());
		glDetachShader(m_handle, m_tessControl->get_handle());
	}

	// Did everything go according to plan?
	GLint result = 0;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &result);

	if (!result)
	{
		GLint length;
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &length);

		std::vector<GLchar> log(length);
		glGetProgramInfoLog(m_handle, length, &length, &log[0]);

		throw OGLException("Could not compile shader.");
	}

	// Delete the shaders.
	m_frag = boost::none;
	m_vertex = boost::none;
	m_geom = boost::none;
	m_tessEval = boost::none;
	m_tessControl = boost::none;

	m_isLinked = true;
}
