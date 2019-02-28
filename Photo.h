#ifndef HASHCODE_2019_PHOTO_H
#define HASHCODE_2019_PHOTO_H

#include <vector>
#include <string>
class Photo {

public:
    bool horizontal;
    std::vector<std::string> tags;
    Photo(bool horizontal): horizontal(horizontal) {}

    Photo withTags(std::vector<std::string> in);
};


#endif //HASHCODE_2019_PHOTO_H
