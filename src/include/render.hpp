#include "pages.hpp"
static unordered_map<string, function<void(Request, Response)>> pages;
static vector<string> dynamicRoutes;

static void initRenders(){
pages["/"] = [](Request req, Response res){ res.send(Index(req)); };
pages["/post/[id]"] = [](Request req, Response res){ res.send(SinglePost(req)); };
}

