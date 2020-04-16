'use strict';

var React = require("react");

function App(Props) {
  return React.createElement("div", undefined, React.createElement("h1", undefined, "This is my cool app!"));
}

var make = App;

exports.make = make;
/* react Not a pure module */
