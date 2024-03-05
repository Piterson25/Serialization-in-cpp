#include "serializer.hpp"

namespace Task
{
    void SerializeToFile(const DataWrapper* data, const char* filePath)
    {
        // TODO: Implement
        std::ofstream file(filePath, std::ios::binary);

        if (!file.is_open()) {
            std::cout << "Cannot save to file";
        }

        file.write(reinterpret_cast<const char*>(&data->numBuffers), sizeof(size_t));
        file.write(reinterpret_cast<const char*>(&data->numData), sizeof(size_t));

        for (int i = 0; i < data->numBuffers; ++i) {
            file.write(reinterpret_cast<const char*>(&data->buffers[i].size), sizeof(size_t));
            file.write(reinterpret_cast<const char*>(data->buffers[i].data), data->buffers[i].size);
        }

        for (int i = 0; i < data->numData; ++i) {
            file.write(reinterpret_cast<const char*>(&data->data[i].value), sizeof(uint32_t));
        }

        file.close();
    }

    void DeserializeFromFile(DataWrapper*& data, const char* filePath)
    {
        // TODO: Implement
        std::ifstream file(filePath, std::ios::binary);

        if (!file.is_open()) {
            std::cout << "Cannot open file";
        }

        size_t numBuffers, numData;

        file.read(reinterpret_cast<char*>(&numBuffers), sizeof(size_t));
        file.read(reinterpret_cast<char*>(&numData), sizeof(size_t));

        data             = new DataWrapper;
        data->numBuffers = numBuffers;
        data->numData    = numData;
        data->buffers    = new Buffer[numBuffers];
        data->data       = new Data[numData];

        for (int i = 0; i < numBuffers; ++i) {
            size_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
            data->buffers[i].size = size;
            data->buffers[i].data = new uint8_t[size];
            file.read(reinterpret_cast<char*>(data->buffers[i].data), size);
        }

        for (int i = 0; i < numData; ++i) {
            uint32_t value;
            file.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
            data->data[i].value = value;
        }

        file.close();
    }
} // namespace Task
