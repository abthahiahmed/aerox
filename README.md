## Aerox 🇧🇩
### A C++ web framework with built-in view engine and file-system based routing.

This framework will simplify the implementation of web task for existing systems which is need to be host publicly. I'm currently working on it and has much more ideas to create a powerful web framework for C++ that can handle web task easily with easy syntax. Here is a quick documentation for quick intro about the framework. 

Currently this framework is build for linux. But I will also build for windows soon.

Current special Features:
- File-system based routing
- File-system based dynamic routing
- Components feature to split views and use globally
- Built-in view engine that supports JSX like syntax on C++ files.
- API route can be created
- Has Request and Response object (including query, params, body objects)
- Indicator to specify a function as a page or component using @page and @component.
- Support Client Side Routing using custom element <a-link>

On pages and components folder you need to use <><> literal to render your HTML content. Using '{}' you can pass C++ variables to your HTML content. 
Note: To pass variables inside '{}', you need to cast those variable to C++ string.

Example for '<><>';
```cpp
// Function start
return <>
    Your HTML content goes here...
<>
// Function end
```

Example for '{}'
```cpp
// Function start
string name = "Abthahi Ahmed";
return <>
    <h1>Hello! My name is {name}</h1>
<>
// Function end
```


A simple code snippet for routes (ExpressJS like syntax) : 
```cpp
#include <iostream>
#include "./src/include/server.hpp"

using namespace std;

int main(int argc, char **argv)
{
	
	Server server = Server(8080);
	
	server.setStaticDir("./public");
	
	server.get("/services", [](Request req, Response res){
		res.send("This is service page");
	});
	
	server.post("/submit", [](Request req, Response res){
		res.send("This is service page");
	});
	
	cout<<"C++ web server started..."<<endl;
	server.listen();
	
	return 0;
}
```

And this example is about a File-system based routing : 
```cpp
// pages/index.cpp
// This file will act as / route
@page Index(Request req){

    @title = "Home Page" // Set page title
    @description = "Some text..." // Set meta description

    return <>
        <h1>Welcome to C++ Web Server</h1>
        <p>This is a alpha version of my C++ Web Server with a simple render Engine!</p>
    <>
}
```

```cpp
// pages/contact.cpp
// This file will act as /contact route
@page Contact(Request req){

    @title = "Contact Page" // Set page title
    @description = "Some text..." // Set meta description

    return <>
        <h1>Contact Us</h1>
        <p>Contact us for more information.</p>
    <>
}
```
### An example of Dynamic routes
```cpp
// pages/post/[slug].cpp
// This file will act as /post/[slug] route
@page Post(Request req){

    @title = "Single Post" // Set page title
    @description = "Some text..." // Set meta description

    return <>
        <h1>This is a single post!</h1>
        <p>And the post slug is : {req.params["slug"]}</p>
    <>
}
```

I already mentioned that this is an initial push of the framework. More updates are coming. Star the repository for updates and support. You can also suggest feature idea for this on discussion.

Thank you so much...
