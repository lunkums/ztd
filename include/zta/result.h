#ifndef ZTA_RESULT_H
#define ZTA_RESULT_H

#include "zta/error.h"

namespace zta {
    struct Ok {
        explicit Ok() {}
    };

    template<typename T = Ok>
    class Result {
      public:
        Result(const T& m_data) : m_is_error(false) {
            m_storage.m_data = m_data;
        }

        Result(Error m_error) : m_is_error(true) {
            m_storage.m_error = m_error;
        }

        Result(const Result& other) : m_is_error(other.m_is_error) {
            if (m_is_error) {
                m_storage.m_error = other.m_storage.m_error;
            } else {
                m_storage.m_data = other.m_storage.m_data;
            }
        }

        Result& operator=(const Result& other) {
            if (this != &other) {
                m_is_error = other.m_is_error;
                if (m_is_error) {
                    m_storage.m_error = other.m_storage.m_error;
                } else {
                    m_storage.m_data = other.m_storage.m_data;
                }
            }
            return *this;
        }

        bool is_error() const {
            return m_is_error;
        }

        bool is_ok() const {
            return !m_is_error;
        }

        T& data() {
            return m_storage.m_data;
        }

        const T& data() const {
            return m_storage.m_data;
        }

        T& operator*() {
            return data();
        }

        const T& operator*() const {
            return data();
        }

        T* operator->() {
            return &m_storage.m_data;
        }

        const T* operator->() const {
            return &m_storage.m_data;
        }

        zta::Error& error() {
            return m_storage.m_error;
        }

        const zta::Error& error() const {
            return m_storage.m_error;
        }
      private:
        // TODO: Replace with a Type-safe union. Can't use the built-in union because it only
        // supports POD and error is a complex Type
        struct Storage {
            T m_data;
            zta::Error m_error;
        };

        Storage m_storage;
        bool m_is_error;
    };
}

#define ZTA_CONCAT_IMPL(a, b) a##b
#define ZTA_CONCAT(a, b) ZTA_CONCAT_IMPL(a, b)

#define ZTA_UNIQUE_NAME(base) ZTA_CONCAT(ZTA_CONCAT(base, _), __LINE__)

// TODO: Update this macro to allow the user to specify a Type for the result
#define ZTA_TRY(expr) \
    do { \
        zta::Result<> ZTA_UNIQUE_NAME(zta_result) = (expr); \
        if (ZTA_UNIQUE_NAME(zta_result).is_error()) { \
            return ZTA_UNIQUE_NAME(zta_result).error(); \
        } \
    } while (0)

#endif
