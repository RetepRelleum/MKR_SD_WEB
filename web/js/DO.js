/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
var script = document.createElement('script');
script.type = 'text/javascript';
script.src = 'https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js';
document.getElementsByTagName('head')[0].appendChild(script);
var doArr = [];

function dOSetValue() {
  $.get("MKR/GETDIO()", function(data) {
    var d = data.split(",");
    d.forEach(function(item, index) {
      if (typeof doArr[index] !== "undefined") {
        var dO = doArr[index];
        if (item == 0) {
          dO.off();
        } else {
          dO.on();
        }
      }
    });
  });
}
class DO {
  constructor(object, io, imgOn, imgOff, imgSize = "100", update = function tes() {
    dOSetValue();
  }) {
    doArr[io] = this;
    this.imgSize = imgSize;
    this.io = io;
    this.imgOff = imgOff;
    this.imgOn = imgOn;
    this.object = object;
    this.update = update;
    this.object.title = "Do" + io;
    this.getStatus();
    this.object.onclick = this.onClick;

  }
  addImgOn() {
    var elem = document.createElement("img");
    elem.setAttribute("src", this.imgOn);
    elem.setAttribute("height", this.imgSize);
    elem.setAttribute("width", this.imgSize);
    elem.setAttribute("alt", "DoOn");
    elem.setAttribute("id", "DoOn" + this.io);
    document.getElementById(this.object.getAttributeNS(null, "id")).appendChild(elem);
  }
  addImgOff() {
    var elem = document.createElement("img");
    elem.setAttribute("src", this.imgOff);
    elem.setAttribute("height", this.imgSize);
    elem.setAttribute("width", this.imgSize);
    elem.setAttribute("alt", "DoOff");
    elem.setAttribute("id", "DoOff" + this.io);
    document.getElementById(this.object.getAttributeNS(null, "id")).appendChild(elem);
  }
  onClick() {
    var di = doArr[this.title.replace("Do", "")];
    if (di.isOn()) {
      di.setOff();
    } else {
      di.setOn();
    }
    di.update();
  }
  on() {
    var elem = document.getElementById("DoOn" + this.io);
    if (elem) {
      elem.parentNode.removeChild(elem);
    }
    elem = document.getElementById("DoOff" + this.io);
    if (elem) {
      elem.parentNode.removeChild(elem);
    }
    this.addImgOn();
  }
  off() {
    var elem = document.getElementById("DoOff" + this.io);
    if (elem) {
      elem.parentNode.removeChild(elem);
    }
    elem = document.getElementById("DoOn" + this.io);
    if (elem) {
      elem.parentNode.removeChild(elem);
    }
    this.addImgOff();
  }
  isOn() {
    var elem = document.getElementById("DoOn" + this.io);
    return (elem !== null);
  }
  setOn() {
    $.get("MKR/SETDIO(" + this.io + ",1)", function(data) {
      var nra = this.url.replace("MKR/SETDIO(", "");
      var nr = nra.replace(",1)", "");
      var di = doArr[nr];
      di.getStatus();
    });
  }
  setOff() {
    $.get("MKR/SETDIO(" + this.io + ",0)", function(data) {
      var nra = this.url.replace("MKR/SETDIO(", "");
      var nr = nra.replace(",0)", "");
      var di = doArr[nr];
      di.getStatus();
    });
  }
  getStatus() {
    $.get("MKR/GETDIO(" + this.io + ")", function(data) {
      var nra = this.url.replace("MKR/GETDIO(", "");
      var nr = nra.replace(")", "");
      var di = doArr[nr];
      if (data.startsWith("0")) {
        di.off();
      } else if (data.startsWith("1")) {
        di.on();
      }
    });
  }
}
