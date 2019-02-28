#ifndef HASHCODE_2019_PHOTO_H
#define HASHCODE_2019_PHOTO_H

#include <vector>
#include <string>
class Photo {

public:
    bool horizontal;
    std::vector<std::string> tags;
    int id;
    Photo(bool horizontal, std::vector<std::string> tags, int id): horizontal(horizontal), tags(tags), id(id) {}

};


#endif //HASHCODE_2019_PHOTO_H
