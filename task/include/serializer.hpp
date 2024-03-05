#pragma once

#include "data.hpp"
#include <fstream>
#include <iostream>

namespace Task
{
    void SerializeToFile(const DataWrapper* data, const char* filePath);

    void DeserializeFromFile(DataWrapper*& data, const char* filePath);
} // namespace Task
