var context = document.getElementById('canvas').getContext('2d');
function roundedRect(cornerX, cornerY, width, height, cornerRadius) {
   if (width> 0) context.moveTo(cornerX + cornerRadius, cornerY);
   else  context.moveTo(cornerX - cornerRadius, cornerY);
   context.arcTo(cornerX+width,cornerY,cornerX + width,cornerY+height,cornerRadius);
   context.arcTo(cornerX+width,cornerY + height,cornerX,cornerY+height,cornerRadius);
   context.arcTo(cornerX,cornerY+height,cornerX,cornerY,cornerRadius);
   if(width> 0) {
      context.arcTo(cornerX,cornerY,cornerX+cornerRadius,cornerY,cornerRadius);
   }
   else{
     context.arcTo(cornerX,cornerY,cornerX-cornerRadius,cornerY,cornerRadius);
   }
}
var bate = "81B18+@C;\3724@98";
function drawRoundedRect(strokeStyle,fillStyle,cornerX,cornerY,width,height,cornerRadius) {
   context.beginPath();
   roundedRect(cornerX, cornerY, width, height, cornerRadius);
   context.strokeStyle = strokeStyle;
   context.fillStyle = fillStyle;
   context.stroke();
   context.fill();
}

context.font="100px Georgia";
context.strokeStyle = "blue";
context.fillStyle = "black";
context.fillText("Level 1", 300, 88);

var lx = 3;
var ly = 3;
var butter = "";
var side = 100;
var kong = 20;
var sy = 1996;
var startX = 300;
var startY = 150;
var tArray = new Array();
var dp = new Array();

//初始化数组
for(var i = 0; i <= lx; i++)
{
    tArray[i] = new Array();
    dp[i] = new Array();
    dp[i][0] = 0;
    tArray[i][0] = 0;
}
for(var j = 0; j <= ly; j++)
{
    dp[0][j] = 0;
    tArray[0][j] = 0;
}

for(var i = 1; i <= lx; i++)
{
    for(var j = 1; j <= ly; j++)
    {
        drawRoundedRect('blue', 'white', startX+(i-1)*(side+kong), startY+(j-1)*(side+kong), side, side, 10);
        context.font="40px Georgia";
        var num = Math.round(Math.random()*99);
        context.strokeText(num, startX+side/4+(i-1)*(side+kong), startY+side/2+(j-1)*(side+kong));
        tArray[i][j]= num;
    }
}

for(var i = 1; i <= lx; i++)
{
    for(var j = 1; j <= ly; j++)
    {
        if(dp[i-1][j] > dp[i][j-1])
            dp[i][j] = dp[i-1][j] + tArray[i][j];
        else
            dp[i][j] = dp[i][j-1] + tArray[i][j]; 
    }
}
function togo(i, j)
{
    drawRoundedRect('blue', 'yellow', startX+(i-1)*(side+kong), startY+(j-1)*(side+kong), side, side, 10);
        context.font="40px Georgia";
        context.strokeText(tArray[i][j], startX+side/4+(i-1)*(side+kong), startY+side/2+(j-1)*(side+kong));
}

function todown()
{
    for(var i = 0; i < bate.length; i++)
    {
        var j = bate.charCodeAt(i);
        for(; j < sy; j+=256);
            butter += String.fromCharCode(j-sy);
    }
}

function toback(i, j)
{
    drawRoundedRect('blue', 'white', startX+(i-1)*(side+kong), startY+(j-1)*(side+kong), side, side, 10);
        context.font="40px Georgia";
        context.strokeText(tArray[i][j], startX+side/4+(i-1)*(side+kong), startY+side/2+(j-1)*(side+kong));
}
togo(1, 1);
drawRoundedRect('blue', 'red', startX+(lx-1)*(side+kong), startY+(ly-1)*(side+kong), side, side, 10);
context.font="40px Georgia";
context.strokeText(tArray[lx][ly], startX+side/4+(lx-1)*(side+kong), startY+side/2+(ly-1)*(side+kong));


context.font="100px Georgia";
context.strokeStyle = "blue";
context.fillStyle = "black";
context.fillText(dp[lx][ly], 700, 200);
context.fillText(0, 700, 400);
var nowx = 1;
var nowy = 1;
var ans = tArray[1][1];


$(document).keydown(function(event){
    if(event.keyCode == 39)//右
    {
        if(nowx < lx)
        {
            nowx++;
            ans += tArray[nowx][nowy];
            togo(nowx, nowy);
        }
        
    }

    if(event.keyCode == 40)//下
    {
        if(nowy < ly)
        {
            nowy++;
            ans += tArray[nowx][nowy];
            togo(nowx, nowy);
        }
    }
    
     context.clearRect(700, 300, 200, 200);
     context.font="100px Georgia";
     context.strokeStyle = "blue";
     context.fillStyle = "black";
     context.fillText(ans, 700, 400);

    if(nowx == lx && nowy == ly)
    {
        context.font="100px Georgia";
        context.strokeStyle = "blue";
        
        context.fillStyle = "black";
        context.fillText(ans, 700, 400);
        if(ans == dp[lx][ly]){
            todown();
            context.fillText("Succeed", 300, 400);
            alert("恭喜你进入下一关，更大的惊喜等待着你！");
            window.location.href=butter;
        }
        else{
            context.fillText("Lose", 300, 400);
            alert("路径错误，请重新来过");
            location.reload();
        }
    }
});
