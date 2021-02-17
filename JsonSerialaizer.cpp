#include <iostream>
#include <string>

class Serializer {
public:
    Serializer() = default;

    virtual void BeginArray() = 0;

    virtual void AddArrayItem(const std::string &element) = 0;

    virtual void EndArray() = 0;

    virtual ~Serializer() {
    }
};

class JsonSerializer : public Serializer {
public:
    size_t bracket_counter;
    size_t element_counter;
    bool afterbracket = false;
    std::string ans;

    void BeginArray() override {
        if (element_counter > 0 | afterbracket) {
            ans += ",";
        }
        ans += "[";
        bracket_counter++;
        element_counter = 0;
        afterbracket = false;
    }

    void AddArrayItem(const std::string &element) override {
        if (element_counter > 0 || afterbracket) {
            ans += ",";
        }
        ans = ans + "\"" + element + "\"";
        element_counter++;
    }

    void EndArray() override {
        bracket_counter -= 1;
        ans += "]";
        if (bracket_counter == 0) {
            std::cout << ans;
            ans = "";
        } else {
            afterbracket = true;
        }
    }
};

int main() {
    Serializer *k = new JsonSerializer();
    k->BeginArray();
    k->EndArray();
    k->BeginArray();
    k->EndArray();

    return 0;
}