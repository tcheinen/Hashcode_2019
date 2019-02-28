#include "Photo.h"


Photo Photo::withTags(std::vector<std::string> in) {
    this->tags = in;
    return this;
}
