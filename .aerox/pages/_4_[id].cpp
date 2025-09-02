#include "../../src/include/pages.hpp"
#include "../../src/include/components.hpp"
#include "../../src/include/metadata.hpp"

string SinglePost(Request req){

	__title__ = "Post : " + req.params["id"];
	__description__ = "This is good post...";

	return ""
"	" + Header() + ""
"	<h1>This is single post! and the post id is : " + req.params["id"] + "</h1>"
"	" + Footer() + ""
"	";;
	
}

