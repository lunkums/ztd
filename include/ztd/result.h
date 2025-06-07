#ifndef ZTD_RESULT_H
#define ZTD_RESULT_H

#include "ztd/error.h"

namespace ztd {
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

        ztd::Error& error() {
            return m_storage.m_error;
        }

        const ztd::Error& error() const {
            return m_storage.m_error;
        }
      private:
        // TODO: Replace with a Type-safe union. Can't use the built-in union because it only
        // supports POD and error is a complex Type
        struct Storage {
            T m_data;
            ztd::Error m_error;
        };

        Storage m_storage;
        bool m_is_error;
    };
}

#define ZTD_CONCAT_IMPL(a, b) a##b
#define ZTD_CONCAT(a, b) ZTD_CONCAT_IMPL(a, b)

#define ZTD_UNIQUE_NAME(base) ZTD_CONCAT(ZTD_CONCAT(base, _), __LINE__)

// TODO: Update this macro to allow the user to specify a Type for the result
#define ZTD_TRY(expr) \
    do { \
        ztd::Result<> ZTD_UNIQUE_NAME(ztd_result) = (expr); \
        if (ZTD_UNIQUE_NAME(ztd_result).is_error()) { \
            return ZTD_UNIQUE_NAME(ztd_result).error(); \
        } \
    } while (0)

#endif
