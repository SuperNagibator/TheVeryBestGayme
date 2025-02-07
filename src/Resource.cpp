#include "Resource.hpp"

#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>

Resource::Resource(const char *path) : path(path) {}

std::vector<char> Resource::load() {
    std::ifstream stream(path, std::ios::binary | std::ios::ate);
    if (!stream) {
        throw std::runtime_error(path + "file opening failed");
    }

    size_t size = stream.tellg();
    std::vector<char> data(size);

    stream.seekg(std::ios::beg);
    stream.read(data.data(), size);

    return data;
}