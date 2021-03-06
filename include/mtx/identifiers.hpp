#pragma once

#include <exception>
#include <iostream>
#include <regex>

namespace mtx {
namespace identifiers {

static std::regex LOCALPART_REGEX("[A-za-z0-9._%+-]{1,}");
static std::regex DOMAIN_NAME_REGEX("(?!\\-)(?:[a-zA-Z\\d\\-]{0,62}[a-zA-Z\\d]\\.){1,"
                                    "126}(?!\\d+)[a-zA-Z\\d]{1,63}(:\\d{0,5})?");

//! Base class for all the identifiers.
//
//! Each identifier has the following format `(sigil)``(localpart)`:`(hostname)`.
class ID
{
public:
        //! Returns the unique local part of the identifier.
        std::string localpart() const { return localpart_; }
        //! Returns the name of the originating homeserver.
        std::string hostname() const { return hostname_; }
        //! Returns the whole identifier (localpart + hostname).
        std::string toString() const { return id_; }
        //! Returns the port of the originating homeserver.
        //! It defaults to `-1` if a standard port is selected.
        int port() const { return port_; }

protected:
        //! Local part of the identifier.
        std::string localpart_;
        //! The name of the originating homeserver.
        std::string hostname_;
        //! The whole identifier.
        std::string id_;
        //! The port of the originating homeserver.
        int port_;
};

class Event : public ID
{
public:
        template<typename Identifier>
        friend Identifier parse(const std::string &id);

private:
        //! The `sigil` used to represent an Event.
        std::string sigil = "$";
};

class Room : public ID
{
public:
        template<typename Identifier>
        friend Identifier parse(const std::string &id);

private:
        std::string sigil = "!";
};

class User : public ID
{
public:
        template<typename Identifier>
        friend Identifier parse(const std::string &id);

private:
        std::string sigil = "@";
};

//! Parses the given string into a @p Identifier.
//! \param id String to parse.
//! \returns The parsed @p Identifier.
//! \throws std::invalid_argument in case of invalid input.
template<typename Identifier>
Identifier
parse(const std::string &id)
{
        Identifier identifier;

        if (id.empty()) {
                // FIXME: enable logging only in debug mode.
                /* std::cout << "mtx::identifiers - Empty matrix identifier was given" << std::endl;
                 */
                return identifier;
        }

        if (std::string(1, id.at(0)) != identifier.sigil)
                throw std::invalid_argument(
                  std::string(id + ": missing sigil " + identifier.sigil + "\n"));

        std::string localpart;
        std::string hostname;
        std::string server;
        int port = -1;

        const auto parts = id.find_first_of(':');

        // Split into localpart and server.
        if (parts != std::string::npos) {
                localpart = id.substr(1, parts - 1);
                server    = id.substr(parts + 1);
        } else {
                throw std::invalid_argument(id + ": invalid format\n");
        }

        if (!std::regex_match(server, DOMAIN_NAME_REGEX))
                throw std::invalid_argument(id + ": the domain name is not valid\n");

        // Split into hostname and port (if any).
        const auto server_parts = server.find_first_of(':');

        if (server_parts != std::string::npos) {
                hostname = server.substr(0, server_parts);
                port     = std::stoi(server.substr(server_parts + 1));
        } else {
                hostname = server;
        }

        if (port == 0 || port > 65536)
                throw std::invalid_argument(id + ": invalid port number\n");

        if (!std::regex_match(localpart, LOCALPART_REGEX))
                throw std::invalid_argument(id + ": the local part is not valid\n");

        identifier.localpart_ = localpart;
        identifier.hostname_  = hostname;
        identifier.port_      = port;
        identifier.id_        = id;

        return identifier;
}

} // namespace identifiers
} // namespace mtx
