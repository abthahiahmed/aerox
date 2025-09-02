@page SinglePost(Request req){

	return <>
	{Header()}
	<h1>This is single post! and the post id is : {req.params["id"]}</h1>
	{Footer()}
	<>;
	
}