<?php

$fen = $_GET['fen'];
$dificuldade = $_GET['dificuldade'];

if($dificuldade === "")
	$dificuldade = "0";

if((int)$dificuldade>15)
	$dificuldade = "15";

if($fen==""){
	echo "-";
	exit;
}

$descr = array(
    0 => array(
        'pipe',
        'r'
    ) ,
    1 => array(
        'pipe',
        'w'
    ) 
);
$pipes = array();
$process = proc_open("./stockfish", $descr, $pipes);
if (is_resource($process)){	
    fwrite($pipes[0], "position fen $fen\n");
    fwrite($pipes[0], "setoption name Threads value 8\n");
	fwrite($pipes[0], "go depth $dificuldade\n");
	while(true){
		$s = fgets($pipes[1]);
		$str .= $s;
		if(strpos(' '.$s,'bestmove')){
			break;
		}
	}
	echo  explode(" ", $s)[1];
	
    fclose($pipes[1]);
	proc_close($process);
}

?>
