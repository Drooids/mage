#pragma once

#include <string>
#include <sstream>

#include <GL/glew.h>

#include <mage/exception.hpp>

namespace Mage {
	class OGLException : public Mage::Exception {
	protected:
		std::string m_what;

	public:
		explicit OGLException(const std::string& err, GLenum errCode = 0) {
			std::ostringstream ss;
			ss << err;

			if (errCode != GL_NO_ERROR) {
				auto errMsg = gluErrorString(errCode);
				ss << "(" << errCode << "): " << errMsg;
			}

			m_what = ss.str();
		}

		const char* what() const {
			return m_what.c_str();
		}
	};
}
