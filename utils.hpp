#ifndef OBL_CLIPCURSOR_UTILS_HPP
#define OBL_CLIPCURSOR_UTILS_HPP

#include <string>

#define EXPORT __declspec(dllexport)

std::string get_last_error_message(size_t max_size = 256);

void get_last_error_message(std::string& output);

void fatal_error(const char* message, bool include_last_error = true);

// Decodes a packed Oblivion version (MAKE_OBLIVION_VERSION: major<<24 |
// minor<<16 | build) into the "major.minor.0.build" form the modding
// community recognizes (e.g. "1.2.0.416").
std::string format_oblivion_version(unsigned int version);

#endif // Include guard.
