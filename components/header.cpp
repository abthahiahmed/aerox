// Root component that holds HTML structure
@component Header(){
  return <>
  <div class="w-full p-3 bg-white shadow-lg sticky top-0">
    <div class="flex justify-between">
      <h3>This is header</h3>
      <div class="flex items-center gap-3">
        <a-link href="/" class="text-gray-500 hover:text-blue-500 font-bold">Home</a-link>
        <a-link href="/about" class="text-gray-500 hover:text-blue-500 font-bold">About</a-link>
        <a-link href="/contact" class="text-gray-500 hover:text-blue-500 font-bold">Contact</a-link>
        <a-link href="/posts" class="text-gray-500 hover:text-blue-500 font-bold">Posts</a-link>
      </div>
    </div>
  </div>
  <>
}
