#pragma once

#include <string>
#include <sstream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <mage/exception.hpp>

namespace Mage
{
	class TextException : public Exception
	{
		static const char* getErrorMsg(FT_Error err)
		{
			#undef __FTERRORS_H__
			#define FT_ERRORDEF(e, v, s) case e: return s;
			#define FT_ERROR_START_LIST switch (err) {
			#define FT_ERROR_END_LIST }
			#include FT_ERRORS_H

			return "Unknown error";
		}

	protected:
		std::string emsg;

	public:
		TextException(const std::string& msg, FT_Error err = 0)
		{
			std::ostringstream ss;
			ss << msg;

			if (err)
			{
				ss << ": " << getErrorMsg(err);
			}

			emsg = ss.str();
		}

		const char* what() const override
		{
			return emsg.c_str();
		}
	};
}