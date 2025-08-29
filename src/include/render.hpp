#include "pages.hpp"
static unordered_map<string, function<void(Request, Response)>> pages;
static void initRenders(){
pages["/"] = [](Request req, Response res){ res.send(Index(req)); };
}

