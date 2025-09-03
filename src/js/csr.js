function clientSideRoute(path, push = true){
    if (path[0] == "/"){
        const root = document.getElementById("root");
        if (push) history.pushState({page : path}, "", `${path}`);
        const xhr = new XMLHttpRequest();
        xhr.open("GET", `${path}?navigate=true`);
        xhr.send();
        xhr.onreadystatechange = function () {
            if (xhr.readyState == 4 && xhr.status == 200){
                let data = JSON.parse(xhr.response);
                // Change the page content without refresh
                root.innerHTML = data.body;
                // Change meta data

                document.title = data.meta.title; // Setting title dynamically...
                document.head.querySelector("meta[name=\"description\"]").setAttribute("content", data.meta.description); // Setting meta description dynamically...
            }
            else if (xhr.status == 500){
                root.innerHTML = "<h2>Internal Server Error!</h2>";
            }
            else if (xhr.status == 404){
                root.innerHTML = "<h2>Page Not Found!</h2>";
            }
        }
    }
}
window.addEventListener("popstate", (event) => {
  clientSideRoute(event.state.page, false);
});
class AeroxLink extends HTMLElement{
    constructor(){
        super();
        this.addEventListener("click", this.handleClick);
    }

    handleClick(event){
        event.preventDefault();
        console.log(this.getAttribute("href"));
        const path = this.getAttribute("href");
        clientSideRoute(path);
    }

    connectedCallback(){
        const anchor = document.createElement("a");
        anchor.innerHTML = this.innerHTML;
        anchor.href = this.getAttribute("href");
        this.innerHTML = anchor.outerHTML;
    }
}
customElements.define("a-link", AeroxLink);