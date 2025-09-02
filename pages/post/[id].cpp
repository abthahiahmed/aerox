#include "../../src/lib/data.hpp" // Data source for dummy posts

@page SinglePost(Request req){

	int id = stoi(req.params["id"]); // Converting string to integer

	Post post = posts[id - 1];

	@title = "Post : " + post.title;
	@description = "This is good post...";

	return <>
		{Header()}

		<h1>{post.title}</h1>
		<p>Published on {post.date}</p>
		<p>{post.content}</p>
		
		{Footer()}
	<>;
	
}