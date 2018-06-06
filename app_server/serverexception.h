#ifndef SERVEREXCEPTION
#define SERVEREXCEPTION

#include <exception>

/**
 * @brief The UnsupportedServerMessageException struct is an exception supposed to be thrown when server receives wrong type of message
 */
struct UnsupportedServerMessageException : public std::exception {};

/**
 * @brief The WrongNumberOfPlayersException struct is an exception supposed to be thrown when server receives information with wrong number of players
 */
struct WrongNumberOfPlayersException : public std::exception {};

#endif // SERVEREXCEPTION

