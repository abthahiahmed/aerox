// Root component that holds HTML structure
@component MainRoot(string children){

    return <>
        <!DOCTYPE html>
        <html lang="en">
        {Head()}
        <body>
            <main id="root">
                {children}
            </main>
            {AScript()}
        </body>
        </html>
    <>;
}