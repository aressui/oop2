#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>


class Five {
public:
    Five();
    Five(const size_t& arraySize, unsigned char defaultValue = 0);
    Five(const std::initializer_list<unsigned char>& digits);
    Five(const std::string& number);
    Five(const Five& other);
    Five(Five&& other) noexcept;

    Five add(const Five& other);
    Five remove(const Five& other);

    bool equals(const Five& other) const;
    bool small(const Five& other) const;
    bool large(const Five& other) const;
    
    std::ostream& print(std::ostream& outputStream);

    virtual ~Five() noexcept;

private:
    size_t arraySize;
    unsigned char* dataArray;
};
