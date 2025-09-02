
@page Contact(Request req){
    @title = "Contact Us";
    @description = "Contact with us";

    return <>
		{Header()}
        <h1>This is contact page</h1>
        <p>You can contact here</p>
        
        <form action="/contact" method="POST">
            <input type="email" name="email" placeholder="Enter your email" autocomplete="false"/><br/>
            <input type="text" name="name" placeholder="Enter your subject"/><br/>

            <textarea name="text"></textarea><br/>
            <button>Submit</button>
        </form>
        {Footer()}
    <>
}