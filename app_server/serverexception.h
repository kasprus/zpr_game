#ifndef SERVEREXCEPTION
#define SERVEREXCEPTION

#include <exception>

struct UnsupportedServerMessageException : public std::exception {};

struct WrongNumberOfPlayersException : public std::exception {};

#endif // SERVEREXCEPTION

