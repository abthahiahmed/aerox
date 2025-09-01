#include "pages.hpp"
static unordered_map<string, function<void(Request, Response)>> pages;
static void initRenders(){
pages["/posts"] = [](Request req, Response res){ res.send(Posts(req)); };
pages["/"] = [](Request req, Response res){ res.send(Index(req)); };
pages["/contact"] = [](Request req, Response res){ res.send(Contact(req)); };
pages["/post/[id]"] = [](Request req, Response res){ res.send(SinglePost(req)); };
pages["/about"] = [](Request req, Response res){ res.send(About(req)); };
}

