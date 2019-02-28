#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include "Photo.h"
#include "Slide.h"
using namespace std;

vector<Slide> createSlide(vector<Photo> in) {
    vector<Slide> slides;
    Photo temp(false, {},0);
    bool inProgress = false;
    for(int i = 0; i < in.size(); i++) {
        if(in.at(i).horizontal) {
            Slide slide({in.at(i)});
            slide.tags = in.at(i).tags;
            slides.push_back(slide);
            continue;
        }
        if(!inProgress ) {
            temp = in.at(i);
            inProgress = true;
        } else {
            Slide slide({temp, in.at(i)}, true);
            std::set<string> u(temp.tags.begin(), temp.tags.end());
            std::copy( in.at(i).tags.begin(), in.at(i).tags.end(), std::inserter( u, u.end()));
            vector<string> tags(u.begin(), u.end());
            slide.tags = tags;
            slides.push_back(slide);
            Photo temp(false, {},0);
            bool inProgress = false;
        }
    }
    return slides;
}

//string vectorToString(vector<Slide> in) {
//    stringstream ss;
//    ss << "{";
//    for(Slide s: in) {
//        ss << s << ", "
//    }
//    ss << "}";
//}

int main() {
    ifstream infile;
    infile.open("../a_example.txt");
    vector<Photo> photos;
    if (infile.is_open()) {
        int count;
        infile >> count;
        for (int i = 0; i < count; i++) {
            string orientation;
            int tagcount;
            vector<string> tags;
            infile >> orientation >> tagcount;
            for (int j = 0; j < tagcount; j++) {
                string tag;
                infile >> tag;
                tags.push_back(tag);
            }
            bool isHorizontal = !orientation.compare("H");
            Photo p = Photo(isHorizontal, tags,i);
            photos.push_back(p);
        }
    }

    vector<Slide> output = createSlide(photos);

    return 0;
}

