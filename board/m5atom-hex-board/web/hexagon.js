const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

const a = 2 * Math.PI / 6;
const r = 50;

board=["#000000","#000000","#000000","#000000","#000000","#000000",
       "#000000","#000000","#000000","#000000","#000000","#000000",
       "#000000","#000000","#000000","#000000","#000000","#000000",
       "#000000"
];

function drawGrid(width, height) {
    for (let y = r; y + r * Math.sin(a) < height; y += r * Math.sin(a)) {
        for (let x = r, j = 0; x + r * (1 + Math.cos(a)) < width; x += r * (1 + Math.cos(a)), y += (-1) ** j++ * r * Math.sin(a)) {
            drawHexagon(x, y);
        }
    }
}

function drawBoard() {
    size=5;
    for (let y = r,i=0; i < size; i++, y += r * Math.sin(a)) {
        for (let x = r, j = 0; j < size; x += r * (1 + Math.cos(a)), y += (-1) ** j++ * r * Math.sin(a)) {        
            if (
                ((i!=0)      || (j!=0)) &&
                ((i!=0)      || (j!=size-1)) &&
                ((i!=size-1) || (j>1)) &&                    
                ((i!=size-1) || (j<size-2))
                )
            {
                drawHexagon(x, y, i, j);
            }                
        }
    }
}    

function drawHexagon(x, y, i,j) {
    num=coordToNum(i,j);
    ctx.strokeStyle = "#FFFFFF";
    ctx.lineWidth = 4;
    ctx.beginPath();
    for (let i = 0; i < 6; i++) {
        ctx.lineTo(x + r * Math.cos(a * i), y + r * Math.sin(a * i));
    }
    ctx.closePath();
    ctx.stroke();
    ctx.fillStyle = board[num];
    ctx.fill();
    ctx.fillStyle = "white";
    ctx.font = "18px serif";    
    ctx.fillText(num, x-6, y+6);
}

function coordToNum(x,y) {
/* Clockwize
  const coord = [
    [-1,  3,  0,  1, -1],
    [ 7,  8,  4,  5,  2],
    [12, 13,  9, 10,  6],
    [16, 17, 14, 15, 11],
    [-1, -1, 18, -1, -1],  
];*/
// CounterClockwize
  const coord = [
    [-1,  1,  0,  3, -1],
    [ 2,  5,  4,  8,  7],
    [ 6, 10,  9, 13, 12],
    [11, 15, 14, 17, 16],
    [-1, -1, 18, -1, -1],  
];

  if (typeof coord[x][y] !== 'undefined') {
    return(coord[x][y]);
  }
  return -1;
}
/*
function numToCoord(num) {
  const coord = [
    [2,0],[3,0],[4,1],[1,0],[2,1],[3,1],[4,2],
    [0,1],[1,1],[2,2],[3,2],[4,4],[0,2],[1,2],
    [2,3],[3,3],[0,3],[1,3],[2,4]
];

  if (typeof coord[num] !== 'undefined') {
    return(coord[num]);
  }
  return [-1,-1];
}
*/
function buttonApply() {
    id=document.getElementById("id").value
    color=document.getElementById("color").value;
    colorFx=document.getElementById("color-fx").value;
    effect=document.getElementById("effect").value;
    board[id]=color;
    drawBoard();  
    var data = {
        "colors":
        [
            {
                "red": parseInt(color.substring(1,3),16), 
                "green": parseInt(color.substring(3,5),16), 
                "blue": parseInt(color.substring(5,7),16)
            }
        ],
        "effect": effect,
        "display": document.getElementById("display").value
    };
    if (effect=="border")
    {
        data.colors.push(
            {
                "red": parseInt(colorFx.substring(1,3),16), 
                "green": parseInt(colorFx.substring(3,5),16), 
                "blue": parseInt(colorFx.substring(5,7),16)
            }
        );    
    }
    fetch("http://hex-board.local/hexagons/"+id, {
        method: "PUT",
        body: JSON.stringify(data),
        headers: {
            "Content-type": "application/json; charset=UTF-8"
        }
    });

}

window.addEventListener('load', function(evt) {   
    drawBoard();

    select = document.getElementById('id');
    for (var i = 0; i<19; i++){
    var opt = document.createElement('option');
    opt.value = i;
    opt.innerHTML = i;
    select.appendChild(opt);


    document.getElementById("apply").onclick = function() {buttonApply()};


}
});