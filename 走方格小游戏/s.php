<?php

header("content-type:text/html;charset=utf-8");
date_default_timezone_set("PRC");

$thisPage = "s.php";
$nextPage = "h.php";

if(!isset($_SESSION)){
    session_start();
}

function clearAll(){
    // 重置会话中的所有变量
    $_SESSION = array();

    // 如果要清理的更彻底，那么同时删除会话 cookie
    // 注意：这样不但销毁了会话中的数据，还同时销毁了会话本身
    if (ini_get("session.use_cookies")) {
        $params = session_get_cookie_params();
        setcookie(session_name(), '', time() - 42000,'/');
    }

    // 最后，销毁会话
    session_destroy();
}

if (isset($_GET['key'])){
    //存在get请求key，说明用户校验
    if(!isset($_SESSION['key'])){
        //session不存在校验结果，用户请求非法
        echo "<script>alert('请求非法，请刷新重试！');location.href=\"".$thisPage."\";</script>";
        clearAll();
        exit(0);
    }
    $key1 = $_GET['key'];
    $key2 = $_SESSION['key'];
    if ($key1 == $key2){
        //验证通过
        echo "<script>alert('恭喜你，验证通过，继续加油吧～');location.href=\"".$nextPage."\"</script>";
        clearAll();
        exit(0);
    }else{
        //验证失败
        echo "<script>alert('验证失败，继续努力吧～');location.href=\"".$thisPage."\";</script>";
        clearAll();
        exit(0);
    }

}else{
    //初次
    $lx = 3;
    $ly = 3;
    $arr = array();
    $ans = 0;
    $dp = array();

    for($i=0; $i<=$lx; $i++)
    {
        $arr[$i] = array();
        $arr[$i][0] = 0;
        $dp[$i] = array();
        $dp[$i][0] = 0;
    }

    for($j=0; $j<=$ly; $j++)
    {
        $arr[0][$j] = 0;
        $dp[0][$j] = 0;
    }

    for($i=1; $i<=$lx; $i++)
    {
        for($j=1; $j<=$ly; $j++)
        {
            $arr[$i][$j] = mt_rand(0,100);
            if($dp[$i][$j-1] > $dp[$i-1][$j])
                $dp[$i][$j] = $dp[$i][$j-1] + $arr[$i][$j];
            else
                $dp[$i][$j] = $dp[$i-1][$j] + $arr[$i][$j];
        }
    }

    $ans = $dp[$lx][$ly];
    $_SESSION['key'] = $ans;
}

?>
<html>
<head>
    <title>Level 1</title>
    <style>
        #canvas {
            background: lightskyblue;
            -webkit-box-shadow: 4px 4px 8px rgba(0,0,0,0.5);
            -moz-box-shadow: 4px 4px 8px rgba(0,0,0,0.5);
            box-shadow: 4px 4px 8px rgba(0,0,0,0.5);
        }
    </style>
    <script src="http://cdn.bootcss.com/jquery/3.0.0-beta1/jquery.js"></script>
    <meta charset="utf-8">
</head>
<body>
<canvas id='canvas' width='1200' height='660'>Canvas not supported</canvas>

<script>
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
    var side = 100;
    var kong = 20;
    var sy = 1996;
    var startX = 300;
    var startY = 150;
    var tArray = <?php
        echo "[";
        for($i=0; $i<=$lx; $i++)
        {
            echo "[";
            for($j=0; $j<=$ly; $j++)
            {
                echo $arr[$i][$j];
                if ($j != $ly)
                    echo ",";
            }
            echo "]";
            if ($i != $lx)
                echo ",";
        }
        echo "]";
        ?>;


    for(var i = 1; i <= lx; i++)
    {
        for(var j = 1; j <= ly; j++)
        {
            drawRoundedRect('blue', 'white', startX+(i-1)*(side+kong), startY+(j-1)*(side+kong), side, side, 10);
            context.font="40px Georgia";
            context.strokeText(tArray[i][j], startX+side/4+(i-1)*(side+kong), startY+side/2+(j-1)*(side+kong));
        }
    }

    function togo(i, j)
    {
        drawRoundedRect('blue', 'yellow', startX+(i-1)*(side+kong), startY+(j-1)*(side+kong), side, side, 10);
        context.font="40px Georgia";
        context.strokeText(tArray[i][j], startX+side/4+(i-1)*(side+kong), startY+side/2+(j-1)*(side+kong));
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

    var nowx = 1;
    var nowy = 1;
    var ans = tArray[1][1];
    context.font="100px Georgia";
    context.strokeStyle = "blue";
    context.fillStyle = "black";
    context.fillText(ans, 700, 300);

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

        context.clearRect(700, 200, 200, 200);
        context.font="100px Georgia";
        context.strokeStyle = "blue";
        context.fillStyle = "black";
        context.fillText(ans, 700, 300);

        if(nowx == lx && nowy == ly)
        {
            context.font="100px Georgia";
            context.strokeStyle = "blue";

            context.fillStyle = "black";
            context.fillText(ans, 700, 300);


            var putUrl = "./s.php?key="+ans;
            location.href=putUrl;
        }
    });

</script>
</body>
</html>

