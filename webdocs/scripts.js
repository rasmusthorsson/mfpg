function dropGuidesMenu() {
  document.getElementById("guides").classList.toggle("show");
  document.getElementById("links").classList.remove("show");
  document.getElementById("info").classList.remove("show");
}
function dropLinksMenu() {
  document.getElementById("links").classList.toggle("show");
  document.getElementById("guides").classList.remove("show");
  document.getElementById("info").classList.remove("show");
}
function dropInfoMenu() {
  document.getElementById("info").classList.toggle("show");
  document.getElementById("links").classList.remove("show");
  document.getElementById("guides").classList.remove("show");
}
window.onclick = function(event) {
  if (!event.target.matches('.dropbtn')) {
    var dropdowns = document.getElementsByClassName("dropdown-menu");
    var i;
    for (i = 0; i < dropdowns.length; i++) {
      var openDropdown = dropdowns[i];
      if (openDropdown.classList.contains('show')) {
        openDropdown.classList.remove('show');
      }
    }
  }
}
