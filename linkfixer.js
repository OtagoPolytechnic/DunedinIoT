//https://github.com/github/pages-gem/issues/69#issuecomment-243315870

var x = document.links.length; //check every link
  for (i = 0; i < x; i++) {
    var thisHREF = document.links[i].href;
    if (thisHREF.indexOf(window.location.hostname) > -1) 
      thisHREF = thisHREF.replace(".md",".html").replace("/index/","/"); //replace md extensions with html
    document.links[i].setAttribute('href', thisHREF);
  }
