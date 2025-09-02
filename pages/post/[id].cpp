@page SinglePost(Request req){

	@title = "Post : " + req.params["id"];
	@description = "This is good post...";

	return <>
	{Header()}
	<h1>This is single post! and the post id is : {req.params["id"]}</h1>
	{Footer()}
	<>;
	
}