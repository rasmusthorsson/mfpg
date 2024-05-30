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
function dropHiddenTextSol1() {
  document.getElementById("sol-1").classList.toggle("show");
}
function dropHiddenTextSol2() {
  document.getElementById("sol-2").classList.toggle("show");
}
function dropHiddenTextSol3() {
  document.getElementById("sol-3").classList.toggle("show");
}
window.onclick = function(event) {
  if (!event.target.matches('.dropbtn') && !event.target.matches(".hiddenbutton")) {
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
