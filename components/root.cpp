// Root component that holds HTML structure
@component MainRoot(string children){

    return <>
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>{__title__}</title>
            <meta name="description" content="{__description__}"/>
        </head>
        <body>
            {children}
        </body>
        </html>
    <>;
}