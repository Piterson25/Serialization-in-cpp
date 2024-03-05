#include "verifier.hpp"

#include <cstring>

namespace Task
{
    bool Verify(const Task::DataWrapper* wrapper, const Task::DataWrapper* referenceWrapper)
    {
        if (wrapper == referenceWrapper)
            return true;

        if ((wrapper == nullptr && referenceWrapper != nullptr) || (wrapper != nullptr && referenceWrapper == nullptr)) {
            std::cout << "V1";
            return false;
        }

        if (wrapper->numBuffers != referenceWrapper->numBuffers) {
            std::cout << "V2";
            return false;
        }

        for (size_t bufferIdx = 0; bufferIdx < wrapper->numBuffers; ++bufferIdx) {
            const auto& buffer          = wrapper->buffers[bufferIdx];
            const auto& referenceBuffer = referenceWrapper->buffers[bufferIdx];
            if (buffer.size != referenceBuffer.size) {
                std::cout << "V3";
                return false;
            }

            if (std::memcmp(buffer.data, referenceBuffer.data, buffer.size) != 0) {
                std::cout << "V4";
                return false;
            }
        }

        if (wrapper->numData != referenceWrapper->numData) {
            std::cout << "V5";
            return false;
        }

        for (size_t dataIdx = 0; dataIdx < wrapper->numData; ++dataIdx) {
            const auto& data          = wrapper->data[dataIdx];
            const auto& referenceData = referenceWrapper->data[dataIdx];

            if (data.value != referenceData.value) {
                std::cout << "V6";
                return false;
            }
        }

        return true;
    }
} // namespace Task
