function nav(id) {
    var NAVS = [['index.html', 'Home'],
                ['https://github.com/cwru-eecs338', 'Code'],
                ['slides.html', 'Slides'],
                ['intro.html', 'Intro to Linux'],
                ['resources.html', 'Resources'],
                ['contact.html', 'Contact Info']
               ];
    var navElement = document.getElementById(id);
    for(var i = 0; i < NAVS.length; i++) {
        var p = document.createElement('p');
        var a = document.createElement('a');
	var t = document.createTextNode(NAVS[i][1]);
	a.setAttribute('href', NAVS[i][0]);
	a.appendChild(t);
        p.appendChild(a);
        navElement.appendChild(p)
    }
}
