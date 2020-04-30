<!doctype html>
<?php
	$myFile = "speedcontrol.txt";
	$strSpeed = file_get_contents($myFile, true);

	if ($_POST['increase']) {
		$speed = (int)$strSpeed;
		$speed = $speed + 10;
		if ($speed > 100){
			$speed = 100;
		} 
		$fh = fopen($myFile, 'w') or die("can't open file");
		fwrite($fh, $speed);
			
	} else if ($_POST['decrease']) {
		$speed = (int)$strSpeed;
		$speed = $speed - 10;
		if ($speed < -100){
			$speed = -100;
		} 

		$fh = fopen($myFile, 'w') or die("can't open file");
		fwrite($fh, $speed);
    }
        else if ($_POST['initialize']) {
		$fh = fopen($myFile, 'w') or die("can't open file");
		fwrite($fh, 0);
    }

    else {
        
    }
?>

<html>
<head>
<meta charset="utf-8">
<title>Motor Speed Control</title>
<link rel="stylesheet" type="text/css" href="speed1.css">
</head>
<body>
<center>
<form name="speedcontrol" method = "post" action="index.php">
<table>
	<tr><td><input class = "button" type="submit" name="increase" id="increase" value="INCREASE" /></td></tr>
	<tr><td>
	    <?php
	    	$speed = file_get_contents($myFile, true);
	    	if ($speed < 0) {
	    	    echo ("<p class='reverse'>REVERSE</br>");
	    	echo ($speed);
	    	echo ("</p>");
	    	}
	    	else if ($speed > 0) {
	    	    echo ("<p class='forward'>FORWARD</br>");
	    	echo ($speed);
	    	echo ("</p>");
	    	}
	    	else {
                echo ("<p class='neutral'>NEUTRAL</br>");
	    	echo ($speed);
	    	echo ("</p>");
        	}
	    ?>
	</td></tr>    
	<tr><td><input class = "button" type="submit" name="decrease" id="decrease" value="DECREASE" /></td></tr>
	<tr><td><input class = "redbutton" type="submit" name="initialize" id="initialize" value="STOP" /></td></tr>
</table>	
</form>
</center>
</body>
</html>
