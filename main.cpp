#include <iostream>
#include <vector>
#include <fstream>
#include "Photo.h"

using namespace std;

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
            Photo p = Photo(isHorizontal, tags);
            photos.push_back(p);
        }
    }
    return 0;
}

vector<Slide> createSlide(vector<Photo> in) {
    vector<Slide> slides;
    Photo temp(false,{});
    bool inProgress = false;
    for(int i = 0; i < in.size(); i++) {
        if(in.at(i).horizontal) {
            Slide slide(in.at(i));
        }
        if(!inProgress ) {
            temp = in.at(i);
            inProgress = true;
        } else {
            Slide slide({temp, in.at(i)});
        }
    }
}