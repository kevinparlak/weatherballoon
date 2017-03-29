<!DOCTYPE html>
<html>
<head>

</head>
<body>
<!-- ///NEED SIMPLE BACKGROUND -->
<!-- ///NEED PHP call to FSW main exe -->
<!-- ///Or - Create button to do it. -->
<!-- ///Open UI page -->
<form action="UI.php">
	<input type="button" value="UI" />
</form>
<?php
	system("./mainexestub 2>&1");
?>
<?php
	system("./helloworld 2>&1");
?>
<h1>WELCOME </h1>
<p> This the the AERSP 440  BLUE TEAM Project Home page. </p>
<p> Otherwise: Please Standby.........</p>
<h2>THIS PAGE CURRENTLY UNDER CONSTRUCTION</h2>

<form name="login" action="GuestUI.php">
            Username<input type="text" name="userid"/>
            Password<input type="password" name="pswrd"/>
            <input type="button" onclick="check(this.form)" value="Login"/>
            <input type="reset" value="Cancel"/>
            <input type="submit" value="Guest" />
        </form>
        
        
        <script language="javascript">
            function check(form) {
                if(form.userid.value == "TeamBlue" && form.pswrd.value == "rosebowl") {
                    window.open('UI.php')
                }
                else {
                    alert("Error Password or Username.")
               }
            }
        </script>

</body>
<!html>
