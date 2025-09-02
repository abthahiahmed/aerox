#include "../../src/lib/data.hpp" // Data source for dummy posts

@page Posts(Request req){

    @title = "All Posts"; // Setting Title
    @description = "These are all my posts"; // Setting meta description



    string content = "";

    for (int i = 0; i < posts.size(); i++){
        content += <>
            <h2>{to_string(i + 1)}. {posts[i].title}</h2>
            <p>Published on {posts[i].date}</p>
            <a href="/post/{to_string(i + 1)}">View</a>
        <>;
    }

    return <>
		{Header()}
        <h3>This is post Example</h3>
        <div>
            {content}
        </div>
        {Footer()}
    <>
}