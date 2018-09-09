/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
var script = document.createElement('script');
script.src = 'https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js';
document.getElementsByTagName('head')[0].appendChild(script);
var diArr = [];

function dISetValue() {
    $.get("MKR/GETDIO()", function (data) {
        var d = data.split(",");
        d.forEach(function (item, index) {
            if (typeof diArr[index] !== "undefined") {
                var di = diArr[index];
                if (item == 0) {
                    di.off();
                } else {
                    di.on();
                }
            }
        });
    });

}

class DI {
    constructor(object, io, imgOn, imgOff, imgSize = "100", intervall = "10000") {
        diArr[io] = this;
        this.imgSize = imgSize;
        this.io = io;
        this.imgOff = imgOff;
        this.imgOn = imgOn;
        this.object = object;
        this.object.title = "Di" + io;
    }

    addImgOn() {
        var elem = document.createElement("img");
        elem.setAttribute("src", this.imgOn);
        elem.setAttribute("height", this.imgSize);
        elem.setAttribute("width", this.imgSize);
        elem.setAttribute("alt", "DiOn");
        elem.setAttribute("id", "DiOn" + this.io);
        document.getElementById(this.object.getAttributeNS(null, "id")).appendChild(elem);
    }
    addImgOff() {
        var elem = document.createElement("img");
        elem.setAttribute("src", this.imgOff);
        elem.setAttribute("height", this.imgSize);
        elem.setAttribute("width", this.imgSize);
        elem.setAttribute("alt", "DiOff");
        elem.setAttribute("id", "DiOff" + this.io);
        document.getElementById(this.object.getAttributeNS(null, "id")).appendChild(elem);
    }

    on() {
        var elem = document.getElementById("DiOn" + this.io);
        if (elem) {
            elem.parentNode.removeChild(elem);
        }
        elem = document.getElementById("DiOff" + this.io);
        if (elem) {
            elem.parentNode.removeChild(elem);
        }
        this.addImgOn();
    }
    off() {
        var elem = document.getElementById("DiOff" + this.io);
        if (elem) {
            elem.parentNode.removeChild(elem);
        }
        elem = document.getElementById("DiOn" + this.io);
        if (elem) {
            elem.parentNode.removeChild(elem);
        }
        this.addImgOff();
    }
    isOn() {
        var elem = document.getElementById("DiOn" + this.io);
        return  (elem !== null);
    }

   
}