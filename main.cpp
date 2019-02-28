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
    std::set<string> bs(b.begin(), b.end());
    std::set<string> out;
    for(int i = 0; i < a.size(); i++) {
        const bool is_in = bs.find(a.at(i)) != bs.end();
        if(is_in) out.insert(a.at(i));
    }
    return out.size();
}

int interest(Slide a, Slide b) {
    int intersection = intersectionCount(a.tags, b.tags);
    int slide1 = a.tags.size() - intersection;
    int slide2 = b.tags.size() - intersection;
    return std::min(intersection, std::min(slide1, slide2));
}

void sortSlides(vector<Slide>& slideshow) {

//    std::sort(slideshow.begin(), slideshow.end(), [](Slide a, Slide b) { return interest(b, a) > 2; });

    for (int i = 0; i < slideshow.size() - 1; i++) {
        if(i % 10000 == 0) cout << "i =" << i << endl;
        int maxInt = 0;
        int maxIndex = i + 1;
        int range = i + 20 < slideshow.size() ? i + 20 : slideshow.size();
        for (int j = i+1; j < range; j++) {
            int it = interest(slideshow.at(i), slideshow.at(j));
            if (it > maxInt) {
                maxIndex = j;
                maxInt = it;
            }
        }

            Slide temp = slideshow.at(maxIndex);
            slideshow.at(maxIndex) = slideshow.at(i + 1);
            slideshow.at(i + 1) = temp;
    }
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
        cout << file << endl;
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
        sortSlides(output);
        ofstream outfile;
        outfile.open("../output/" + file + "_output.txt");
        outfile << vectorToString(output);
        outfile.close();
    }
    return 0;
}

