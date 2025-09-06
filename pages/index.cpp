@page Index(Request req){
    @title = "Aerox | Home Page";
    @description = "Welcome to Aerox web framework";

    return <>
		{Header()} 
        <h1 class="text-4xl text-center">Welcome to Aerox 1.3</h1>
        <p class="text-xl text-center">A C++ Web framework</p>
        <p class="text-sm text-gray-500">Development mode is really slow!!</p>
        {Footer()}
    <>
}