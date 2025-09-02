#include "../../src/include/pages.hpp"
#include "../../src/include/components.hpp"
#include "../../src/include/metadata.hpp"



string About(Request req){
    __title__ = "About Us";
    __description__ = "This is all about me";

    return ""
"    " + Header() + ""
"        <h1>C++ Web Server framework by Abthahi Ahmed Rifat</h1>"
"    " + Footer() + ""
"    ";;
}

