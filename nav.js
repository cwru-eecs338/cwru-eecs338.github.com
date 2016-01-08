function nav(id) {
    var NAVS = [
        ['index.html', 'Home'],
        ['course-materials/eecs338-syllabus-spring-2016.pdf', 'Syllabus'],
        //['contact.html', 'Contacts'],
        ['https://github.com/cwru-eecs338', 'Code Examples'],
        ['slides.html', 'Recitation Slides'],
        ['intro.html', 'Intro to Linux'],
        ['resources.html', 'Resources'],
        //['index-spring2015.html','Spring 2015 Page'],
        //['index-spring2014.html','Spring 2014 Page'],
        //['index-spring2013.html','Spring 2013 Page'],
        //['index-spring2012.html',' Spring 2012 Page'],
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
