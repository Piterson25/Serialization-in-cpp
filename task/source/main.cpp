#include "serializer.hpp"
#include "verifier.hpp"

int main(int argc, char** argv)
{
    // TODO: 1. Prepare example data for serialization
    Task::Buffer buffers[2];

    buffers[0].data = new uint8_t[3]{'1', '2', '3'};
    buffers[0].size = 3;
    buffers[1].data = new uint8_t[2]{6, 0};
    buffers[1].size = 2;

    Task::Data data[2];
    data[0].value = 2;
    data[1].value = 3;

    Task::DataWrapper dataWrapper;
    dataWrapper.buffers    = buffers;
    dataWrapper.numBuffers = 2;
    dataWrapper.data       = data;
    dataWrapper.numData    = 2;

    // TODO: 2. Serialize data to file
    Task::SerializeToFile(&dataWrapper, "file.bin");

    // TODO: 3. Deserialize data from file
    Task::DataWrapper* newDataWrapper = nullptr;
    Task::DeserializeFromFile(newDataWrapper, "file.bin");

    // TODO: 4. Verify deserialized data is correct

    if (Task::Verify(newDataWrapper, &dataWrapper)) {
        std::cout << "Data is correct!";
    }

    for (int i = 0; i < dataWrapper.numBuffers; ++i) {
        delete[] dataWrapper.buffers[i].data;
    }

    return 0;
}
