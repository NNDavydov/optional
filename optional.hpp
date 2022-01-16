// Copyright Davydov Nikolay 2021

#ifndef INCLUDE_OPTIONAL_HPP_
#define INCLUDE_OPTIONAL_HPP_

#include <type_traits>
#include <memory>

namespace my_optional {
    template<class T>
    class optional {
        using Storage = std::aligned_storage_t<sizeof(T), alignof(T)>;
    private:
        Storage storage_;
        bool status_ = false;

    public:
        constexpr optional() noexcept: storage_(), status_(false) {}

        constexpr explicit optional(std::nullopt_t) noexcept: storage_(), status_(false) {}

        constexpr optional(const optional &copy) : storage_(), status_(copy.status_) {
            if (status_) new(&storage_) T(*copy);
        }

        constexpr optional(optional &&moved) noexcept: storage_(), status_(moved.status_) {
            if (status_) {
                new(&storage_) T(std::move(*moved));
                moved.status_ = false;
            }
        }

        constexpr explicit optional(const T &obj) : storage_(), status_(false) {
            new(&storage_) T(obj);
            status_ = true;
        }

        constexpr explicit optional(T &&obj) noexcept: storage_(), status_(false) {
            new(&storage_) T(std::move(obj));
            status_ = true;
        }

        optional &operator=(const optional &copy) {
            if (this == &copy) return *this;

            if (status_) {
                if (copy.status_) (**this) = *copy;
                else (**this).~T();
            } else if (copy.status_) new(&storage_) T(*copy);

            status_ = copy.status_;
            return *this;
        }

        optional &operator=(optional &&moved) noexcept {
            if (this == &moved) return *this;

            if (status_) {
                if (moved.status_) (**this) = std::move(*moved);
                else (**this).~T();
            } else if (moved.status_) new(&storage_) T(std::move(*moved));

            moved.status_ = false;
            status_ = true;
            return *this;
        }

        optional &operator=(const T &obj) {
            if (status_) (**this) = obj;
            else new(&storage_) T(obj);

            status_ = true;
            return *this;
        }

        optional &operator=(T &&obj) noexcept {
            if (status_) (**this) = std::move(obj);
            else new(&storage_) T(std::move(obj));

            status_ = true;
            return *this;
        }

        T &operator*() {
            return *static_cast<T *>(static_cast<void *>(&storage_));
        }

        T *operator->() {
            return static_cast<T *>(static_cast<void *>(&storage_));
        }

        const T &operator*() const {
            return *static_cast<const T *>(static_cast<const void *>(&storage_));
        }

        const T *operator->() const {
            return static_cast<const T *>(static_cast<const void *>(&storage_));
        }

        explicit operator bool() const {
            return status_;
        }

        T &value() {
            if (status_) return *static_cast<T *>(static_cast<void *>(&storage_));
            throw std::runtime_error("No value");
        }

        const T &value() const {
            if (status_) return *static_cast<const T *>(static_cast<const void *>(&storage_));
            throw std::runtime_error("No value");
        }

        template<class U>
        T value_or(U &&default_value) {
            return bool(*this) ? **this : static_cast<T>(std::forward<U>(default_value));
        }

        ~optional() noexcept {
            if (status_) (**this).~T();
        }

    };
}


#endif //INCLUDE_OPTIONAL_HPP_
