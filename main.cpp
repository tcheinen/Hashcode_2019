#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include "Photo.h"
#include "Slide.h"
#include <cmath>

using namespace std;

int roundUp(float n) {
    if (n - ((int) n) >= 0.5) {
        return ceil(n);
    } else {
        return floor(n);
    }
}

int intersectionCount(vector<string> a, vector<string> b) {
    struct counting_iterator {
        size_t count;
        counting_iterator &operator++() {
            ++count;
            return *this;
        }
    };
    size_t count = set_intersection(a.begin(), a.end(), b.begin(), b.end(), counting_iterator()).count;
    return count;
}

vector<Slide> createSlide(vector<Photo> in) {
    vector<Slide> slides;
    Photo temp(false, {}, 0);
    bool inProgress = false;
    for (int i = 0; i < in.size(); i++) {
        if (in.at(i).horizontal) {
            Slide slide({in.at(i)});
            slide.tags = in.at(i).tags;
            slides.push_back(slide);
            continue;
        }
        if (!inProgress) {
            temp = in.at(i);
            inProgress = true;
        } else {
            Slide slide({temp, in.at(i)}, true);
            std::set<string> u(temp.tags.begin(), temp.tags.end());
            std::copy(in.at(i).tags.begin(), in.at(i).tags.end(), std::inserter(u, u.end()));
            vector<string> tags(u.begin(), u.end());
            slide.tags = tags;
            slides.push_back(slide);
            temp = Photo(false, {}, 0);
            inProgress = false;
        }
    }
    std::sort(slides.begin(), slides.end(), [](Slide a, Slide b) { return a.tags.size() > b.tags.size(); });
    return slides;
}

string vectorToString(vector<Slide> in) {
    stringstream ss;
    ss << in.size() << endl;
    for (Slide s: in) {
        ss << s << endl;
    }
    return ss.str();
}

int main() {
    vector<string> input(
            {"a_example", "b_lovely_landscapes", "c_memorable_moments", "d_pet_pictures", "e_shiny_selfies"});
//    vector<string> input({"c_memorable_moments"});
    for (string file: input) {
        ifstream infile;
        infile.open("../input/" + file + ".txt");
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
                Photo p = Photo(isHorizontal, tags, i);
                photos.push_back(p);
            }
        }

        vector<Slide> output = createSlide(photos);
        ofstream outfile;
        outfile.open("../output/" + file + "_output.txt");
        outfile << vectorToString(output);
        outfile.close();
    }
    return 0;
}

