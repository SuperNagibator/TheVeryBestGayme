#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <vector>
#include <string>

class Resource {
    std::string path;

public:
    Resource(const char *path);

    std::vector<char> load();
};

#endif // RESOURCE_HPP