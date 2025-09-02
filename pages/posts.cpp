#include <vector>
@page Posts(Request req){

    @title = "All Posts"; // Setting Title
    @description = "These are all my posts"; // Setting meta description

    vector<string> posts = {
        "How to make apps in Flutter", 
        "How to solve problems on AlgoRux", 
        "Code optimization", 
        "Cheatsheet for React"
    };

    string content = "";

    for (int i = 0; i < posts.size(); i++){
        content += <>
            <h2>{to_string(i + 1)}. {posts[i]}</h2>
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