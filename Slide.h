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
        photo.push_back(p);
      }
    }

    friend ostream& operator<<(ostream& os, const Slide& s)
    {
      if (s.photo.size() == 1) 
        os << s.photo[0].id;
      else
        os << s.photo[0].id << " " << s.photo[1].id;
      return os;
    }
};


#endif //SLIDE_H
