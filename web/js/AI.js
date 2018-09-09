/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

var script = document.createElement('script');
script.src = 'https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js';
document.getElementsByTagName('head')[0].appendChild(script);
var aiArr = [];

function aISetValue() {
    $.get("MKR/GETAIO()", function (data) {
        var d = data.split(",");
        d.forEach(function (item, index) {
            if (typeof aiArr[index] !== "undefined") {
                var ai = aiArr[index];
                var x = item / 1023 * ai.size;
                var svg = document.getElementById("AI" + index);
                var elem = svg.getElementById("img");
                elem.setAttribute("height", x);
                elem.setAttribute("y", ai.size - x);
            }
        });
    });

}

class AI {
    constructor(object, io, intervall = "10000", size = "100") {
        aiArr[io] = this;
        this.io = io;
        this.object = object;
        this.object.title = "Ai" + io;
        this.size = size;
        this.addImg();


    }
    setValue(a) {



    }

    addImg() {
        var x = 25;
        var svgElem = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
        svgElem.setAttribute("height", 100 / 100 * this.size);
        svgElem.setAttribute("width", 100 / 100 * this.size);
        svgElem.setAttribute("id", "AI" + this.io);
        var recElem = document.createElementNS("http://www.w3.org/2000/svg", 'rect');
        recElem.setAttribute("width", this.size);
        recElem.setAttribute("height", this.size);
        recElem.setAttribute("stroke", 'gray');
        recElem.setAttribute("fill", "white");
        svgElem.appendChild(recElem);
        var i;
        for (i = 1; i < 5; i++) {
            var lineElem = document.createElementNS("http://www.w3.org/2000/svg", 'line');
            lineElem.setAttribute("x1", 0);
            lineElem.setAttribute("y1", i / 5 * this.size);
            lineElem.setAttribute("x2", this.size);
            lineElem.setAttribute("y2", i / 5 * this.size);
            lineElem.setAttribute("stroke", 'black');
            svgElem.appendChild(lineElem);
        }
        var recElem = document.createElementNS("http://www.w3.org/2000/svg", 'rect');
        recElem.setAttribute("width", 75 / 100 * this.size);
        recElem.setAttribute("height", x / 100 * this.size);
        recElem.setAttribute("y", 1 * this.size - x / 100 * this.size);
        recElem.setAttribute("x", (25 / 2) / 100 * this.size);
        recElem.setAttribute("fill", "blue");
        recElem.setAttribute("id", "img");
        svgElem.appendChild(recElem);

        this.object.appendChild(svgElem);
    }
}