#ifndef ZTD_ERROR_H
#define ZTD_ERROR_H

#include "ztd/types.h"

namespace ztd {
    class error {
      public:
        error() : m_what(ZTD_NULL) {}
        explicit error(const char* message) : m_what(message) {}

        virtual const char* what() const {
            return m_what ? m_what : "unknown error";
        }

        bool operator==(const error& other) const {
            return m_what == other.m_what;
        }

        bool operator!=(const error& other) const {
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
