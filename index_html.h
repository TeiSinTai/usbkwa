static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html lang=en>
<head>
<meta charset="UTF-8">
<meta name = "viewport" content = "width=device-width, initial-scale = 1.0, user-scalable=0">
<title>USB Touch keyboard</title>
<style type="text/css">
    body {
      width: 90vw;
      height: 90vh;
    }
    table {
        position: absolute;
        top: 0;
        bottom: 0;
        left: 0;
        right: 0;
        height: 100%;
        width: 100%;
        border-collapse: collapse;
    }
    td {
        padding: 5px;
        width: 5.88%;
        border: 1px solid;
        font-size: 1.5vw;
        text-align: left;
    }

    td p {
        color: red;
        display: inline;
    }
</style>
<script type="text/javascript">
var websock;
var connected = false;
let gridData = [
  [ // Keyboard row 0 (top row)
    { cellLabel: "Esc", colSpan: 2},
    { cellLabel: "F1"},
    { cellLabel: "F2"},
    { cellLabel: "F3"},
    { cellLabel: "F4"},
    { cellLabel: "F5"},
    { cellLabel: "F6"},
    { cellLabel: "F7"},
    { cellLabel: "F8"},
    { cellLabel: "F9"},
    { cellLabel: "F10"},
    { cellLabel: "F11"},
    { cellLabel: "F12"},
    { cellLabel: ""},
    { cellLabel: "Prt<br>Scr"},
    { cellLabel: "Scroll<br>Lock"},
    { cellLabel: "Pause<br>Break"},
  ],
  [ // Keyboard row 1
    { cellLabel: "~<br>`&nbsp;<p>ё</p>"},
    { cellLabel: "!<br>1"},
    { cellLabel: "@<br>2&nbsp;<p>\"</p>"},
    { cellLabel: "#<br>3&nbsp;<p>№</p>"},
    { cellLabel: "$<br>4&nbsp;<p>;</p>"},
    { cellLabel: "%<br>5"},
    { cellLabel: "^<br>6&nbsp;<p>:</p>"},
    { cellLabel: "&<br>7&nbsp;<p>?</p>"},
    { cellLabel: "*<br>8"},
    { cellLabel: "(<br>9"},
    { cellLabel: ")<br>0"},
    { cellLabel: "_<br>-"},
    { cellLabel: "+<br>="},
    { cellLabel: "Backspace", colSpan: 2},
    { cellLabel: "Insert"},
    { cellLabel: "Home"},
    { cellLabel: "Page<br>Up"},
  ],
  [ // Keyboard row 2
    { cellLabel: "Tab", colSpan: 2},
    { cellLabel: "Q&nbsp;<p>Й</p>"},
    { cellLabel: "W&nbsp;<p>Ц</p>"},
    { cellLabel: "E&nbsp;<p>У</p>"},
    { cellLabel: "R&nbsp;<p>К</p>"},
    { cellLabel: "T&nbsp;<p>Е</p>"},
    { cellLabel: "Y&nbsp;<p>Н</p>"},
    { cellLabel: "U&nbsp;<p>Г</p>"},
    { cellLabel: "I&nbsp;<p>Ш</p>"},
    { cellLabel: "O&nbsp;<p>Щ</p>"},
    { cellLabel: "P&nbsp;<p>З</p>"},
    { cellLabel: "{<br>[&nbsp;<p>Х</p>"},
    { cellLabel: "}<br>]&nbsp;<p>Ъ</p>"},
    { cellLabel: "|<br>\\&nbsp;<p>/</p>"},
    { cellLabel: "Delete"},
    { cellLabel: "End"},
    { cellLabel: "Page<br>Down"},
  ],
  [ // Keyboard row 3
    { cellLabel: "Caps<br>Lock", colSpan: 2},
    { cellLabel: "A&nbsp;<p>Ф</p>"},
    { cellLabel: "S&nbsp;<p>Ы</p>"},
    { cellLabel: "D&nbsp;<p>В</p>"},
    { cellLabel: "F&nbsp;<p>А</p>"},
    { cellLabel: "G&nbsp;<p>П</p>"},
    { cellLabel: "H&nbsp;<p>Р</p>"},
    { cellLabel: "J&nbsp;<p>О</p>"},
    { cellLabel: "K&nbsp;<p>Л</p>"},
    { cellLabel: "L&nbsp;<p>Д</p>"},
    { cellLabel: ":<br>;&nbsp;<p>Ж</p>"},
    { cellLabel: "\"<br>\'&nbsp;<p>Э</p>"},
    { cellLabel: "Enter", colSpan: 2},
    { cellLabel: "<svg class=\"svg-icon\" viewBox=\"0 0 20 20\"><path d=\"M18.303,4.742l-1.454-1.455c-0.171-0.171-0.475-0.171-0.646,0l-3.061,3.064H2.019c-0.251,0-0.457,0.205-0.457,0.456v9.578c0,0.251,0.206,0.456,0.457,0.456h13.683c0.252,0,0.457-0.205,0.457-0.456V7.533l2.144-2.146C18.481,5.208,18.483,4.917,18.303,4.742 M15.258,15.929H2.476V7.263h9.754L9.695,9.792c-0.057,0.057-0.101,0.13-0.119,0.212L9.18,11.36h-3.98c-0.251,0-0.457,0.205-0.457,0.456c0,0.253,0.205,0.456,0.457,0.456h4.336c0.023,0,0.899,0.02,1.498-0.127c0.312-0.077,0.55-0.137,0.55-0.137c0.08-0.018,0.155-0.059,0.212-0.118l3.463-3.443V15.929z M11.241,11.156l-1.078,0.267l0.267-1.076l6.097-6.091l0.808,0.808L11.241,11.156z\"></path></svg>"},
    { cellLabel: ""},
    { cellLabel: ""},
  ],
  [ // Keyboard row 4
    { cellLabel: "Shift", colSpan: 2},
    { cellLabel: "Z&nbsp;<p>Я</p>"},
    { cellLabel: "X&nbsp;<p>Ч</p>"},
    { cellLabel: "C&nbsp;<p>С</p>"},
    { cellLabel: "V&nbsp;<p>М</p>"},
    { cellLabel: "B&nbsp;<p>И</p>"},
    { cellLabel: "N&nbsp;<p>Т</p>"},
    { cellLabel: "M&nbsp;<p>Ь</p>"},
    { cellLabel: "\<<br>,&nbsp;<p>Б</p>"},
    { cellLabel: "\><br>.&nbsp;<p>Ю</p>"},
    { cellLabel: "?&nbsp;<p>,</p><br>/&nbsp;<p>.</p>"},
    { cellLabel: "Shift", colSpan: 3},
    { cellLabel: ""},
    { cellLabel: "Up<br>Arrow"},
    { cellLabel: ""},
  ],
  [ // Keyboard row 5
    { cellLabel: "Ctrl", colSpan: 2},
    { cellLabel: "GUI<br>Alt<br>Option"},
    { cellLabel: "Alt<br>GUI<br>Clover"},
    { cellLabel: "Space", colSpan: 5},
    { cellLabel: "Alt<br>GUI<br>Clover", colSpan: 2},
    { cellLabel: "GUI<br>Alt<br>Option"},
    { cellLabel: "Context<br>Menu"},
    { cellLabel: "Ctrl", colSpan: 2},
    { cellLabel: "Left<br>Arrow"},
    { cellLabel: "Down<br>Arrow"},
    { cellLabel: "Right<br>Arrow"},
  ]
];

function touch_start(event) {
    event.preventDefault();
    e = document.getElementById(this.id);
    e.style.backgroundColor = "yellow";
    var json = JSON.stringify({event:'touch start', name:this.innerHTML, row:this.row, col:this.col});
    if(this.row === 3 && this.col === 13){
      window.location = "/form.html";
      return false;
    }
    if (!connected) {
        setTimeout(function(json) {
            websock.send(json);
        }, 200);
        window.location.reload();
    }
    else {
        websock.send(json);
    }
}
function touch_end(event) {
    event.preventDefault();
    e = document.getElementById(this.id);
    e.style.backgroundColor = "white";
    websock.send(JSON.stringify({event:'touch end', name:this.innerHTML, id:this.id, row:this.row, col:this.col}));
}
function touch_move(event) {
    event.preventDefault();
    var json = JSON.stringify({event:'touch move', name:this.innerHTML, row:this.row, col:this.col});
    if (!connected) {
        setTimeout(function(json) {
            websock.send(json);
        }, 200);
        window.location.reload();
    }
    else {
        websock.send(json);
    }
}
function touch_cancel(event) {
    event.preventDefault();
    document.getElementById(this.id).style.backgroundColor = "white";
    websock.send(JSON.stringify({event:'touch cancel', name:this.innerHTML, id:this.id, row:this.row, col:this.col}));
}
function button_click(event) {
    event.preventDefault()
    //document.getElementById(this.id).style.backgroundColor = "yellow";
}
function double_click(event) {
    event.preventDefault();
    if(this.row === 3 && this.col === 13){
      window.location = "/form.html";
      return false;
    }
    console.log('double click', this.id, this.innerHTML, event);
}
function context_menu(event) {
    event.preventDefault();
    console.log('right click', this.id, this.innerHTML, event);
}
function generateGrid(cols, rows, cellData, id) {
    let grid = document.getElementById(id);
    let r = 0;
    for (let rowElement of cellData) {
        let aRow = grid.insertRow();
        let c = 0;
        for (let colElement of rowElement) {
            let cell = aRow.insertCell();
            cell.id = 'r' + r + 'c' + c;
            cell['row'] = r;
            cell['col'] = c;
            cell.onclick = button_click;
            cell.ondblclick = double_click;
            cell.oncontextmenu = context_menu;
            cell.ontouchstart = touch_start;
            cell.onmousedown = touch_start;
            cell.ontouchmove = touch_move;
            cell.onmousemove = touch_move;
            cell.ontouchend = touch_end;
            cell.onmouseup = touch_end;
            cell.onmouseout = touch_end;
            cell.onmouseleave = touch_end;
            cell.ontouchcancel = touch_cancel;
            cell.innerHTML = colElement["cellLabel"];
            if (colElement["colSpan"] > 1) {
                cell.colSpan = colElement["colSpan"];
            }
            c++;
        }
        r++;
    }
}

function start() {
  generateGrid(17, 6, gridData, "my_table");
  websock = new WebSocket('ws://' + window.location.hostname + ':81/');
  websock.onopen = function(evt) { console.log('websock onopen', evt); connected = true; };
  websock.onclose = function(evt) { console.log('websock onclose', evt); connected = false; };
  websock.onerror = function(evt) { console.log('websock onerror', evt); };
  websock.onmessage = function(evt) { console.log(evt); };
}

</script>
</head>
<body onload="javascript:start();" onresize="window.location.reload();">
<table id="my_table">
<!-- Grid goes here -->
</table>
</body>
</html>
)rawliteral";
