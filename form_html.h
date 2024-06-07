static const char PROGMEM FORM_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html lang=en>
<head>
<meta charset="UTF-8">
<meta name = "viewport" content = "initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
<title>USB Touch keyboard</title>
<style type="text/css">
</style>
<script type="text/javascript">
var websock;
var connected = false;

function translate(evt){
  if(evt != undefined){
    evt.preventDefault();
  }
  str = document.getElementById("textinput").value;
  str2 = translit(str);
  transmit(str2);
  return false;
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function transmit(text){
  let rowcoldata = {
    '`': { row: 1, col: 0 },
    '1': { row: 1, col: 1 },
    '2': { row: 1, col: 2 },
    '3': { row: 1, col: 3 },
    '4': { row: 1, col: 4 },
    '5': { row: 1, col: 5 },
    '6': { row: 1, col: 6 },
    '7': { row: 1, col: 7 },
    '8': { row: 1, col: 8 },
    '9': { row: 1, col: 9 },
    '0': { row: 1, col: 10 },
    '-': { row: 1, col: 11 },
    '=': { row: 1, col: 12 },
    'q': { row: 2, col: 1 },
    'w': { row: 2, col: 2 },
    'e': { row: 2, col: 3 },
    'r': { row: 2, col: 4 },
    't': { row: 2, col: 5 },
    'y': { row: 2, col: 6 },
    'u': { row: 2, col: 7 },
    'i': { row: 2, col: 8 },
    'o': { row: 2, col: 9 },
    'p': { row: 2, col: 10 },
    '[': { row: 2, col: 11 },
    ']': { row: 2, col: 12 },
    '\\': { row: 2, col: 13 },
    'a': { row: 3, col: 1 },
    's': { row: 3, col: 2 },
    'd': { row: 3, col: 3 },
    'f': { row: 3, col: 4 },
    'g': { row: 3, col: 5 },
    'h': { row: 3, col: 6 },
    'j': { row: 3, col: 7 },
    'k': { row: 3, col: 8 },
    'l': { row: 3, col: 9 },
    ';': { row: 3, col: 10 },
    '\'': { row: 3, col: 11 },
    'z': { row: 4, col: 1 },
    'x': { row: 4, col: 2 },
    'c': { row: 4, col: 3 },
    'v': { row: 4, col: 4 },
    'b': { row: 4, col: 5 },
    'n': { row: 4, col: 6 },
    'm': { row: 4, col: 7 },
    ',': { row: 4, col: 8 },
    '.': { row: 4, col: 9 },
    '/': { row: 4, col: 10 },
    ' ': { row: 5, col: 3 }
  };
  for (var i = 0; i < text.length; ++i ) {
    if(text[i] === '>'){
      websock.send(JSON.stringify({event:'touch start', row: 4, col: 0}));
    }
    if(text[i] === '<'){
      websock.send(JSON.stringify({event:'touch end', row: 4, col: 0}));
    }
    if(' qwertyuiop[]\asdfghjkl;\'zxcvbnm,./`1234567890-='.includes(text[i])){
      tt = rowcoldata[text[i]];
      websock.send(JSON.stringify({event:'touch start', row:tt.row, col:tt.col}));
      await sleep(50);
      websock.send(JSON.stringify({event:'touch end', row: tt.row, col: tt.col}));
    }
    await sleep(100);
  }
  return false;
}

function translit(word){
  var answer = '';
  var converter = {
    'A': '>a<',  'B': '>b<',  'C': '>c<',  'D': '>d<',  'E':'>e<',
    'F': '>f<',  'G': '>g<',  'H': '>h<',  'I': '>i<',  'J':'>j<',
    'K': '>k<',  'L': '>l<',  'M': '>m<',  'N': '>n<',  'O':'>o<',
    'P': '>p<',  'Q': '>q<',  'R': '>r<',  'S': '>s<',  'T':'>t<',
    'U': '>u<',  'V': '>v<',  'W': '>w<',  'X': '>x<',  'Y':'>y<',
    'Z': '>z<',

    '~': '>`<',  '!': '>1<',  '@': '>2<',  '#': '>3<',  '$':'>4<',
    '%': '>5<',  '^': '>6<',  '&': '>7<',  '*': '>8<',  '(':'>9<',
    ')': '>0<',  '_': '>-<',  '+': '>=<', '|': '>\\<',

    'а': 'f',    'б': ',',    'в': 'd',    'г': 'u',    'д': 'l',
    'е': 't',    'ё': '`',    'ж': ';',    'з': 'p',    'и': 'b',
    'й': 'q',    'к': 'r',    'л': 'k',    'м': 'v',    'н': 'y',
    'о': 'j',    'п': 'g',    'р': 'h',    'с': 'c',    'т': 'n',
    'у': 'e',    'ф': 'a',    'х': '[',    'ц': 'w',    'ч': 'x',
    'ш': 'i',    'щ': 'o',    'ь': 'm',    'ы': 's',    'ъ': ']',
    'э': '\'',   'ю': '.',    'я': 'z',
 
    'А': '>f<',    'Б': '>,<',    'В': '>d<',   'Г': '>u<',    'Д': '>l<',
    'Е': '>t<',    'Ё': '>`<',    'Ж': '>;<',   'З': '>p<',    'И': '>b<',
    'Й': '>q<',    'К': '>r<',    'Л': '>k<',   'М': '>v<',    'Н': '>y<',
    'О': '>j<',    'П': '>g<',    'Р': '>h<',   'С': '>c<',    'Т': '>n<',
    'У': '>e<',    'Ф': '>a<',    'Х': '>[<',   'Ц': '>w<',    'Ч': '>x<',
    'Ш': '>i<',    'Щ': '>o<',    'Ь': '>m<',   'Ы': '>s<',    'Ъ': '>]<',
    'Э': '>\'<',   'Ю': '>.<',    'Я': '>z<'
  };
 
  for (var i = 0; i < word.length; ++i ) {
    if (converter[word[i]] == undefined){
      answer += word[i];
    } else {
      answer += converter[word[i]];
    }
  }
  return answer;
}

function start() {
  websock = new WebSocket('ws://' + window.location.hostname + ':81/');
  websock.onopen = function(evt) { console.log('websock onopen', evt); connected = true; };
  websock.onclose = function(evt) { console.log('websock onclose', evt); connected = false; };
  websock.onerror = function(evt) { console.log('websock onerror', evt); };
  websock.onmessage = function(evt) { console.log(evt); };
  document.getElementById("submitbut").onclick = translate;
}

</script>
</head>
<body onload="javascript:start();">
<input type="textarea" id="textinput" name="textinput">
<input type="submit" id="submitbut">
</body>
</html>
)rawliteral";
