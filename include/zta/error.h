#ifndef ZTA_ERROR_H
#define ZTA_ERROR_H

#include "zta/types.h"

namespace zta {
    class Error {
      public:
        Error() : m_what(ZTA_NULL) {}
        explicit Error(const char* message) : m_what(message) {}

        const char* what() const {
            return m_what ? m_what : "unknown error";
        }

        bool operator==(const Error& other) const {
            return m_what == other.m_what;
        }

        bool operator!=(const Error& other) const {
            return m_what != other.m_what;
        }

        operator int() const {
            return -1;
        }
      private:
        const char* m_what;
    };
}

#endif
