<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Servo Release</title>
</head>
<body>
<!-- Html Display regardless of where in the process -->
<h1>Payload Release Confirmation</h1>
<hr>

<!-- ///Check if this is initial action call or 2nd confirmation -->
<?php if ('request' == $_POST['exec']) {
        // Ask user to confirm they want to release ribbon.
?>
<!-- ///Optional html display if previous condition met. -->

<p>Are you sure you want to release payload?</p>
<form action="payload.php" method="post">
        <!-- /// Handle confirm action by resubmitting this page -->
        <input type="hidden" value="run" name="exec" />
        <input type="submit" value="Yes" />
</form>
<form action="UI.php" method="post">
        <!-- ///Handle cancel action by returning to UI page -->
    <input type="hidden" value="cancel" name="exec" />
    <input type="submit" value="No" />
</form>
<?php

} elseif ('run' == $_POST['exec']) {
        // Command Confirmed, run payload script.
        system("./hotwirebutton 2>&1");
?>
<form action="UI.php" method="post">
	<input type="submit" value="Finished" />
</form>
<?php
} else {
       // Assume Command is not confirmed/rescinded, return to UI, or some other error.
        // TEMP FIX - header('Location: 192.168.1.131/UI.php');
        header('192.168.1.131/UI.php');
        exit;
}

?>

</body>
</html>
