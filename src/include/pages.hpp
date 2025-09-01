#pragma once
#ifndef PAGES_HPP
#define PAGES_HPP
#include <iostream>
#include <unordered_map>
#include <functional>
#include "response.hpp"
#include "request.hpp"
using namespace std;
string Index(Request req);

string SinglePost(Request req);

#endif

