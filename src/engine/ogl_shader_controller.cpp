#include <fstream>
#include <streambuf>

#include <boost/filesystem.hpp>

#include <mage/exception.hpp>
#include <mage/engine/shader.hpp>

namespace fs = boost::filesystem;

void Mage::ShaderController::loadShadersFromDir(const std::string& path)
{
	fs::path p(path);
	fs::directory_iterator end;

	for (fs::directory_iterator it(p); it != end; ++it)
	{
		if (fs::is_directory(it->path()))
		{
			continue;
		}

		auto shaderName = it->path().stem().string();
		std::ifstream f(it->path().string());
		std::string src;

		// Reserve space in advance.
		f.seekg(0, std::ios::end);
		src.reserve(f.tellg());
		f.seekg(0, std::ios::beg);

		src.assign(
			(std::istreambuf_iterator<char>(f)),
			std::istreambuf_iterator<char>());

		// Determine shader type.
		auto ext = fs::extension(it->path());
		ShaderType t;

		if (ext == ".frag") t = ShaderType::Fragment;
		else if (ext == ".vert") t = ShaderType::Vertex;
		else if (ext == ".geom") t = ShaderType::Geometry;
		else if (ext == ".tese") t = ShaderType::TessellationEvaluation;
		else if (ext == ".tesc") t = ShaderType::TessellationControl;
		else throw Exception("Invalid shader type");
		
		// Add the source to the program's compilation stage.
		if (m_programs.find(shaderName) == m_programs.end())
		{
			m_programs[shaderName] = std::make_unique<Program>();
		}

		m_programs[shaderName]->addShaderSource(src, t);
	}

	for (auto& p : m_programs)
	{
		p.second->link();
	}
}

Mage::Program& Mage::ShaderController::getProgram(const std::string& name)
{
	return *m_programs[name];
}