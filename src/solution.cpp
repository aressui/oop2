#include "../include/solution.h"

Five::Five() : arraySize(0), dataArray(nullptr) {
    std::cout << "Default constructor" << std::endl;
}

Five::Five(const size_t& arraySize, unsigned char defaultValue) {
    if (defaultValue > 4) {
        throw std::invalid_argument("Digit must be from 0 to 4");
    }
    this->arraySize = arraySize;
    this->dataArray = new unsigned char[arraySize];
    for (size_t i = 0; i < arraySize; ++i) {
        this->dataArray[i] = defaultValue;
    }
}

Five::Five(const std::initializer_list<unsigned char>& initialValues) {
    arraySize = initialValues.size();
    dataArray = new unsigned char[arraySize];
    
    size_t index = 0;
    for (const auto& value : initialValues) {
        if (value > 4){
            throw std::invalid_argument("Digit must be from 0 to 4");
        }
        dataArray[index++] = value;
    }
}

Five::Five(const std::string& number) {
    arraySize = number.size();
    dataArray = new unsigned char[arraySize];
    
    for (size_t i = 0; i < arraySize; ++i) {
        char letter = number[arraySize - i - 1];
        if (letter < '0' || letter > '4'){
            throw std::invalid_argument("Invalid character in string: " + std::string(1, letter));
        }
        
        dataArray[i] = static_cast<unsigned char>(letter - '0');
    }
}

Five::Five(const Five& other) {
    arraySize = other.arraySize;
    dataArray = new unsigned char[arraySize];
    
    for (size_t i = 0; i < arraySize; ++i) {
        dataArray[i] = other.dataArray[i];
    }
}

Five::Five(Five&& other) noexcept {
    arraySize = other.arraySize;
    dataArray = other.dataArray;
    
    other.arraySize = 0;
    other.dataArray = nullptr;
}

//sum
Five Five::add(const Five& other) {
    size_t maxlen = (arraySize > other.arraySize) ? arraySize: other.arraySize;
    unsigned char* result = new unsigned char[maxlen + 1]();
    unsigned char count = 0;
    unsigned char a = 0;
    unsigned char b = 0;
    for( size_t i = 0; i < maxlen; ++i){
        if (i < arraySize) {
            a = dataArray[i];
        }
        if (i < other.arraySize) {
            b = other.dataArray[i];
        }
        unsigned char amount = a + b + count;
        if (amount > 4){
            result[i] = amount - 5;
            count = 1;
        }else{
            result[i] = amount;
            count = 0;
        }
    }

    size_t sizeNew = maxlen;
    if (count == 1){
        result[sizeNew] = count;
        sizeNew++;
    }

    Five res;
    res.arraySize = sizeNew;
    res.dataArray = new unsigned char[sizeNew];

    for (size_t i = 0; i < sizeNew; ++i) {
        res.dataArray[i] = result[i];
    }

    delete[] result;
    return res;
}

//remove
Five Five::remove(const Five& other) {
    if (arraySize < other.arraySize || this->small(other)) {
        throw std::logic_error("Subtraction result would be negative");
    }
    size_t maxlen = arraySize;
    unsigned char* result = new unsigned char[maxlen + 1]();
    unsigned char count = 0;

    for (size_t i = 0; i < arraySize; ++i) {
        int a = dataArray[i];
        int b = (i < other.arraySize) ? other.dataArray[i] : 0;
        
        a -= count;
        count = 0;

        if (a < b) {
            a += 5;
            count = 1;
        }

        result[i] = static_cast<unsigned char>(a - b);
    }

    if (count > 0) {
        delete[] result;
        throw std::logic_error("Subtraction result would be negative");
    }

    size_t sizeNew = arraySize;
    while (sizeNew > 1 && result[sizeNew - 1] == 0) {
        sizeNew--;
    }

    Five res;
    res.arraySize = sizeNew;
    res.dataArray = new unsigned char[sizeNew];

    for (size_t i = 0; i < sizeNew; ++i) {
        res.dataArray[i] = result[i];
    }

    delete[] result;
    return res;
}

//equals
bool Five::equals(const Five& other) const {
    if (arraySize > other.arraySize){
        return false;
    }else if (arraySize < other.arraySize){
        return false;
    }else{
        for (size_t i = arraySize; i-- > 0;)
        {
            if (dataArray[i] > other.dataArray[i]){
                return false;
            }else if(dataArray[i] < other.dataArray[i]){
                return false;
            }
        }
        return true;    
    }
}

//large
bool Five::large(const Five& other) const {
    if (arraySize > other.arraySize){
        return true;
    }else if (arraySize < other.arraySize){
        return false;
    }else{
        for (size_t i = arraySize; i-- > 0;)
        {
            if (dataArray[i] > other.dataArray[i]){
                return true;
            }else if(dataArray[i] < other.dataArray[i]){
                return false;
            }
        }
        return false;    
    }
}

//small
bool Five::small(const Five& other) const {
    if (arraySize > other.arraySize){
        return false;
    }else if (arraySize < other.arraySize){
        return true;
    }else{
        for (size_t i = arraySize; i-- > 0;)
        {
            if (dataArray[i] > other.dataArray[i]){
                return false;
            }else if(dataArray[i] < other.dataArray[i]){
                return true;
            }
        }
        return false;    
    }
}

std::ostream& Five::print(std::ostream& outputStream) {
    for (size_t i = arraySize; i-- > 0;) {
        outputStream << static_cast<int> (dataArray[i]);
    }
    return outputStream;
}

Five::~Five() noexcept {
    std::cout << "Destructor" << std::endl;
    
    if (dataArray != nullptr) {
        delete[] dataArray;
        dataArray = nullptr;
    }

    arraySize = 0;
}