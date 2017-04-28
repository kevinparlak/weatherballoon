<!doctype html>
<html>
<head>
<!--Header (note: page refreshes every 5 sec) -->
<meta charset="utf-8">
<meta http-equiv="refresh" content="5" />
<title>User Interface</title>
<link rel="stylesheet" href="style.css">
</head>

<body style="background-color:navy;">

<!--************************ Column 1 ************************ -->


<div>
	<h1><center><u><font color="white">Surveillance Package Interface</font></u></center></h1>
</div>

<div class="content col-1-2">
<!-- /// Temp, Pres, and Alt reader block - start /// -->
<?php
	//Load DATA file
	$filename = "balloondata.txt";
	$fileContents = file_get_contents($filename);
	$data = explode("\n", $fileContents);
?>

<div>
  <ul><font color="white">
	<li>Temperature: <?php   echo $data[3]   ?> </li> <!-- temperature input from cpp code -->
  	<br>
	<li>Pressure: <?php echo $data[4]	?></li> <!-- pressure input from cpp code -->
	<br>
	<li>Altitude: <?php echo $data[2] ?></li> <!-- altitude input from cpp code -->
      </font>
  </ul>
</div>
<!--/// End /// -->


<!-- /// Ribbon buttons - start /// -->
<div>
	<form action="servo.php" method="post">
	<input type="hidden" name="color" value="red" />
	<input type="hidden" name="exec" value="request" />
	<input type="submit" id="button1" value="Release Red Ribbon" />
	</form>

	<form action="servo.php" method="post">
	<input type="hidden" name="color" value="black" />
	<input type="hidden" name="exec" value="request" />
	<input type="submit"  id="button2" value="Release Black Ribbon"/>
	</form>
</div>
<!--/// End /// -->

<br>
<br>
<br>
<h1><center>
  <font color="white">==========================</font>
</center></h1>

<!-- /// Payload Button - start /// -->
<div>
	<form action="payload.php" method="post">
	<input type="hidden" name="exec" value="request" />
	<input type="submit" id="button3" value="Release Payload"/>
	</form>
</div>
<!--/// End /// -->
</div>


<!--************************ Column 2 ************************ -->

<br>
<br>
<br>
<br>
<br>
<br>

<div>
<!-- /// Latitude and Longtitude block - start /// -->
<div class="wrapper" >
<font color="white">
	<div id="latitude">
		Latitude: <?php echo $data[0] ?> <!-- Latitude input from cpp code -->
	</div>
	<div id="longtitude">
		Longtitude: <?php echo $data[1] ?> <!-- Longtitude input from cpp code -->
	</div>
    </font>
</div>
<!--/// End /// -->

<br>
<br>
<br>

<!-- /// placeholder 1 - start /// -->

<div>
<img style="height:300px;width:300px;" src="image.jpg">
</div>
<!--/// End /// -->


<!-- /// Current Image - start /// -->
<!--
<div class="content">
<img style="height:300px;width:300px;" src="image.jpg">
</div> -->
<!--/// End /// -->
</div>




</body>


</html>
