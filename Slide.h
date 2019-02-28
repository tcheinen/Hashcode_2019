#ifndef SLIDE_H
#define SLIDE_H

#include <vector>
#include <string>
#include "Photo.h"

using namespace std;

class Slide {

public:
    bool doesContainVimages;
    vector<string> tags;
    vector<Photo> photo;
    Slide(vector<Photo> phts, bool isV = false): doesContainVimages(isV) {
      for(Photo p : phts) {
        photo.pushback(p);
      }
    }

};


#endif //SLIDE_H
