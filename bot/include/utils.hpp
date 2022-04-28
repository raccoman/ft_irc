#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP

#include <string>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

namespace ft {

	typedef std::vector<std::string> vec_string;

	template<typename ... Args>
	std::string string_format(const std::string &format, Args ... args) {
		int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
		auto size = static_cast<size_t>( size_s );
		std::unique_ptr<char[]> buf(new char[size]);
		std::snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}

	static inline vec_string split(const std::string &message) {
		std::string buf;
		std::stringstream ss(message);
		vec_string args;

		while (ss >> buf)
			args.push_back(buf);

		return args;
	}

	static inline std::string join(const std::string &separator, vec_string vec) {
		std::string str;
		for (auto it = vec.begin(); it != vec.end(); it++)
			str.append(*it).append(it + 1 == vec.end() ? "" : separator);
		return str;
	}

	static inline vec_string splitBySpace(const std::string &message) {
		std::string buf;
		std::stringstream ss(message);
		vec_string args;

		while (ss >> buf)
			args.push_back(buf);

		return args;
	}

}

#endif
