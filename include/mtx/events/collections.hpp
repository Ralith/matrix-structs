#pragma once

#include <variant.hpp>

#include "../events.hpp"

namespace mtx {
namespace events {
namespace collections {

namespace states = mtx::events::state;
namespace msgs   = mtx::events::msg;

using StateEvents = mpark::variant<events::StateEvent<states::Aliases>,
                                   events::StateEvent<states::Avatar>,
                                   events::StateEvent<states::CanonicalAlias>,
                                   events::StateEvent<states::Create>,
                                   events::StateEvent<states::GuestAccess>,
                                   events::StateEvent<states::HistoryVisibility>,
                                   events::StateEvent<states::JoinRules>,
                                   events::StateEvent<states::Member>,
                                   events::StateEvent<states::Name>,
                                   events::StateEvent<states::PinnedEvents>,
                                   events::StateEvent<states::PowerLevels>,
                                   // TODO: events::StateEvent<states::Redaction>,
                                   events::StateEvent<states::Topic>>;

using StrippedEvents = mpark::variant<events::StrippedEvent<states::Aliases>,
                                      events::StrippedEvent<states::Avatar>,
                                      events::StrippedEvent<states::CanonicalAlias>,
                                      events::StrippedEvent<states::Create>,
                                      events::StrippedEvent<states::GuestAccess>,
                                      events::StrippedEvent<states::HistoryVisibility>,
                                      events::StrippedEvent<states::JoinRules>,
                                      events::StrippedEvent<states::Member>,
                                      events::StrippedEvent<states::Name>,
                                      events::StrippedEvent<states::PinnedEvents>,
                                      events::StrippedEvent<states::PowerLevels>,
                                      // TODO: events::StrippedEvent<states::Redaction>,
                                      events::StrippedEvent<states::Topic>>;

using TimelineEvents = mpark::variant<events::StateEvent<states::Aliases>,
                                      events::StateEvent<states::Avatar>,
                                      events::StateEvent<states::CanonicalAlias>,
                                      events::StateEvent<states::Create>,
                                      events::StateEvent<states::GuestAccess>,
                                      events::StateEvent<states::HistoryVisibility>,
                                      events::StateEvent<states::JoinRules>,
                                      events::StateEvent<states::Member>,
                                      events::StateEvent<states::Name>,
                                      events::StateEvent<states::PinnedEvents>,
                                      events::StateEvent<states::PowerLevels>,
                                      // TODO: events::StateEvent<states::Redaction>,
                                      events::StateEvent<states::Topic>,
                                      events::RoomEvent<msgs::Audio>,
                                      events::RoomEvent<msgs::Emote>,
                                      events::RoomEvent<msgs::File>,
                                      events::RoomEvent<msgs::Image>,
                                      // TODO: events::RoomEvent<msgs::Location>,
                                      events::RoomEvent<msgs::Notice>,
                                      events::RoomEvent<msgs::Text>,
                                      events::RoomEvent<msgs::Video>>;
}
}
}
