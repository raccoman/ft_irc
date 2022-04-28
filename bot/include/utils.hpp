#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP

#include <string>
#include <vector>

namespace ft {

	typedef std::vector<std::string> vec_string;

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
