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
            Photo p = Photo(isHorizontal).withTags(tags);
            photos.push_back(p);
        }
    }
    return 0;
}