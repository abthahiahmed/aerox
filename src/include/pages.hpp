#pragma once
#ifndef PAGES_HPP
#define PAGES_HPP
#include <iostream>
#include <unordered_map>
#include <functional>
#include "response.hpp"
#include "request.hpp"
using namespace std;

string Posts(Request req);

string Index(Request req);

string Contact(Request req);

string SinglePost(Request req);

string About(Request req);

#endif

