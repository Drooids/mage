#pragma once

#include <memory>
#include <map>

#include <boost/optional.hpp>
#include <GL/glew.h>

#include <mage/noncopyable.hpp>

namespace Mage
{
	enum class ShaderType
	{
		Fragment = GL_FRAGMENT_SHADER,
		Vertex = GL_VERTEX_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		TessellationEvaluation = GL_TESS_EVALUATION_SHADER,
		TessellationControl = GL_TESS_CONTROL_SHADER,
	};

	class Program : Noncopyable
	{
		class Shader : Noncopyable
		{
		protected:
			GLuint m_handle;
			bool m_hasSource;
			bool m_isCompiled;

		public:
			Shader(ShaderType);
			Shader(Shader&&);
			Shader& operator=(Shader&&);
			~Shader();

			void add_source(const char*);
			void compile();

			GLuint get_handle() const
			{
				return m_handle;
			}
		};

	protected:
		GLuint m_handle;
		bool m_isLinked;
		
		boost::optional<Shader> m_frag;
		boost::optional<Shader> m_vertex;
		boost::optional<Shader> m_geom;
		boost::optional<Shader> m_tessEval;
		boost::optional<Shader> m_tessControl;

	public:
		Program();
		~Program();

		void add_shader_source(const std::string&, ShaderType);
		void link();
		void use()
		{
			glUseProgram(m_handle);
		}

		GLuint get_handle() const
		{
			return m_handle;
		}
	};

	class ShaderController : Noncopyable
	{
	protected:
		std::map<std::string, std::unique_ptr<Program>> m_programs;

	public:
		void load_shaders_from_dir(const std::string& path);

		Program& get_program(const std::string&);
	};
}
