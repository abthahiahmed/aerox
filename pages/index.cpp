

@page Index(Request req){
    @title = "Aerox | Home Page";
    @description = "Welcome to Aerox web framework";


    return <>
		{Header()}
        <h1>Welcome to C++ Web Server</h1>
        <p>This is a alpha version of my C++ Web Server with a simple render Engine!</p>
        {Footer()}
    <>
}