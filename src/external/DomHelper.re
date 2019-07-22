type document;

[@bs.val] external document: document = "";

[@bs.val] [@bs.scope "document"]
external createElement: string => document = "createElement";

[@bs.val] [@bs.scope "document"]
external getElementById: string => Dom.element = "getElementById";

[@bs.val] [@bs.scope "document"]
external getElementsByClassName: string => array(Dom.element) =
  "getElementsByClassName";

let addEventListener = [%raw
  (element, event, handleFunc) => {|
   element.addEventListener(event, handleFunc, false)
  |}
];

let locationHref: string => unit = [%raw
  url => "
  window.location.href = url;
"
];

let locationSearch: (. unit) => Js.t({..}) = [%raw
  (.) => {|
    let query = window.location.search.substring(1);
    var paramArray = query.split("&");

    return paramArray.reduce((object, item) => {
      var objArr = item.split("=");
      object[objArr[0]] = objArr[1];

      return object
    }, {})

  |}
];

let getAttribute = [%raw (dom, prop) => "
  return dom.getAttribute(prop);
"];

let onresize = [%raw handleFunc => "
  window.onresize = handleFunc;
"];

let apply = [%bs.raw
  {|
    function(dataArray, func) {
      return func.apply(null, dataArray);
    }
  |}
];

let stopPropagation = e: unit => e##stopPropagation();

let preventDefault = e: unit => e##preventDefault();

let getRandomNumber = () => int_of_float(10000.0 *. Js.Math.random());

let getRandomKey = () => string_of_float(10000.0 *. Js.Math.random());

let intEl = n => ReasonReact.string(string_of_int(n));

let textEl = str => ReasonReact.string(str);