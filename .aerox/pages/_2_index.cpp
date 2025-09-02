#include "../../src/include/pages.hpp"
#include "../../src/include/components.hpp"
#include "../../src/include/metadata.hpp"



string Index(Request req){

    return ""
"		" + Header() + ""
"        <h1>Welcome to C++ Web Server</h1>"
"        <p>This is a alpha version of my C++ Web Server with a simple render Engine!</p>"
"        " + Footer() + ""
"    ";
}

