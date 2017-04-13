<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Start UI</title>
</head>

<body>

<?php
if (empty($_POST)) {
?>
	<!-- ///Display Initial Options, i.e. start the FSW and Navigate to the UI. -->
	<form action="FswStart.php" method="POST">
		<input type="submit" name="FSW" value="Start FSW" />
	</form>
<?php
} elseif ('Start FSW' == $_POST['FSW']) {

//------Start FSW, then pause before retrieving output.------
system("nohup setsid ./weather_balloon > /var/www/html/log.txt 2>&1 &");
sleep(10);

//------Open File and display system checks-----------------
$filename = "log.txt";
$fileContents =  file_get_contents($filename);
echo $fileContents;
?>


<form action="UI.php">
	<input type="submit" name="UI" value="UI" />
</form>
<?php } ?>

</body>
