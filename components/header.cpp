// Root component that holds HTML structure
@component Header(){
  return <>
  <h3>This is header</h3>
  <div>
    <a-link href="/" style="background-color : black; color : white;">Home</a-link>
    <a-link href="/about">About</a-link>
    <a-link href="/contact">Contact</a-link>
    <a-link href="/posts">Posts</a-link>
  </div>
  <>
}
