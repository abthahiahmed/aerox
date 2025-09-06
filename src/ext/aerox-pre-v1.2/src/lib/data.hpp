#include <iostream>
#include <vector>

using namespace std;

struct Post{
    string title;
    string content;
    string date;
};

extern vector<Post> posts;