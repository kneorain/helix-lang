#ifndef __NEO_JSON_HH__
#define __NEO_JSON_HH__

#include <fstream>
#include <map>
#include <ranges>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#define TO_NEO_JSON_IMPL neo::json to_json() const

#define ADD_STRING         \
    {                      \
        add_str(key, val); \
        return *this;      \
    }

namespace neo {
inline namespace _json {
    class Json;

    constexpr inline std::string escape(const std::string &val) {
        std::string result;
        result.reserve(val.size());

        for (char car : val) {
            switch (car) {
                case '"':
                    result += "\\\"";
                    break;
                case '\\':
                    result += "\\\\";
                    break;
                case '\n':
                    result += "\\n";
                    break;
                case '\t':
                    result += "\\t";
                    break;
                case '\r':
                    result += "\\r";
                    break;
                case '\b':
                    result += "\\b";
                    break;
                case '\f':
                    result += "\\f";
                    break;
                default:
                    result += car;
                    break;
            }
        }
        return result;
    }

    template <typename _jsonable>
    concept Jsonable = requires(_jsonable a) {
        { a.to_json() } -> std::same_as<Json>;
    };

    using JsonVec_t = std::vector<Json>;
    using data_t = std::variant<std::string, Json, JsonVec_t>;
    using std::string;

    class Json {
      private:
        using data_map = std::map<string, data_t>;

        data_map _data;

        template <typename T>
        Json get(const T &val) {
            if constexpr (Jsonable<T>) {
                return val.to_json();
            } else if constexpr (std::is_same_v<T, string>) {
                return Json("\"" + escape(string(val)) + "\"", true);
            } else if constexpr (std::is_same_v<T, Json>) {
                return val;
            } else if constexpr (std::ranges::input_range<T> &&! std::is_same_v<T, string>) {
                return Json(process_iterable(val));  // Handle arrays of non-strings
            } else {
                return Json(std::to_string(val), true);
            }
        }

        template <std::ranges::input_range R>
        constexpr JsonVec_t process_iterable(const R &range) {
            JsonVec_t result;
            for (const auto &val : range) {
                result.push_back(get(val));
            }

            return result;
        }

        template <typename T>
        void add_str(const string &key, const T &val) {
            _data[key] = Json("\"" + escape(string(val)) + "\"", true);
        }

        explicit Json(string val, bool /*unused*/)
            : _val(std::move(val)) {}

      public:
        Json() = default;
        explicit Json(string key)
            : key(std::move(key)) {}
        explicit Json(JsonVec_t val)
            : _array(std::move(val)) {}

        void dump(const string &filename) const {
            std::ofstream out(filename);
            out << this->to_string();
            out.close();
        }

        Json &add(const string &key, const string &val) ADD_STRING;
        Json &add(const string &key, const char *val)   ADD_STRING;
        Json &add(const string &key, char *val)         ADD_STRING;

        template <typename T>
        Json &add(const string &key, const T &val) {
            _data[key] = get(val);

            return *this;
        }

        template <typename T>
        Json &add(const T &val) {
            _array.push_back(get(val));
            return *this;
        }

        Json &section(const string &key) {
            if (_data.contains(key)) {
                if (auto *sub_json = std::get_if<Json>(&_data[key])) {
                    return *sub_json;
                }
            }
            _data[key] = Json();
            return std::get<Json>(_data[key]);
        }

        template <typename T>
        void section(const string &key, const T &val) {
            _data[key] = get(val);
        }

        [[nodiscard]] constexpr string to_string(bool is_base = true) const {
            string result;

            if (!_val.empty()) {
                return _val;
            }

            if (!_array.empty()) {
                result += "[";
                for (const auto &val : _array) {
                    result += val.to_string(false) + ",";
                }

                if (!_array.empty()) {
                    result.pop_back();
                }

                result += "]";
                return result;
            }

            if (is_base) {
                result += "{";
                result += "\"" + key + "\":";
            }

            result += "{";
            for (const auto &[key, val] : _data) {
                result += "\"" + key + "\":";
                if (const auto *sub_json = std::get_if<Json>(&val)) {
                    result += sub_json->to_string(false) + ",";
                } else if (const auto *sub_array = std::get_if<JsonVec_t>(&val)) {
                    result += "[";
                    for (const auto &sub_val : *sub_array) {
                        result += sub_val.to_string(false) + ",";
                    }
                    if (!sub_array->empty()) {
                        result.pop_back();
                    }
                    result += "],";
                } else {
                    result += std::get<string>(val) + ",";
                }
            }

            if (!_data.empty()) {
                result.pop_back();
            }

            result += "}";
            if (is_base) {
                result += "}";
            }

            return result;
        }

        friend std::ostream &operator<<(std::ostream &os, const Json &json) {
            os << json.to_string();
            return os;
        }

      private:
        string    key;
        string    _val;
        JsonVec_t _array;
    };

}  // namespace _json

using json = _json::Json;
}  // namespace neo

#undef ADD_STRING
#endif  // __NEO_JSON_HH__
